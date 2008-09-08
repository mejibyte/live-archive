#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cctype>

#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#define PB push_back
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) ((int)(x).size())
#define REP(i, n) for(int i=0; i<n; ++i)
#define REPD(i, n) for(int i=(n)-1; i>=0; --i)
#define FOR(i, b, e) for(typeof(e) i=b; i!=e; ++i)

using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef istringstream ISS;

int N;
VI x, y, npeng, mjumps;

double jdist;

const int INF=10000000;

VVI adj;

int find(int s, int t, VVI &cap) {
  int N=SZ(cap);

  VI prevnode(N,-1);
  vector<int> flow(N, 0);
  deque<int> q;
  q.PB(s);
  flow[s]=INF;

  while(!q.empty()) {
    int node=q.front();
    q.pop_front();

    if(node==t) break;

    REP(i, SZ(adj[node])) {
//    REP(i, N) {
      int next=adj[node][i];
      if(flow[next] || cap[node][next]==0) continue;
      flow[next]=min(flow[node], cap[node][next]);
      prevnode[next]=node;
      q.PB(next);
    }
  }
  //if(!visited[t]) return 0;

  int fl=flow[t];
  while(prevnode[t]!=-1) {
    cap[t][prevnode[t]]+=fl;
    cap[prevnode[t]][t]-=fl;
    t=prevnode[t];
  }
  return fl;
}

int maxflow(int s, int t, VVI cap) {
  int flow=0;
  int pathcap=0;
  do {
    pathcap=find(s, t, cap);
    flow+=pathcap;
  } while(pathcap);
  return flow;
}

bool isedge(int i ,int j) {
  double dx=x[i]-x[j], dy=y[i]-y[j];
  return dx*dx+dy*dy<jdist*jdist+1e-9;
}

void go() {
  scanf("%d %lf", &N, &jdist);
  x.resize(N); y.resize(N);
  npeng.resize(N); mjumps.resize(N);

  REP(i, N) scanf("%d %d %d %d", &x[i], &y[i], &npeng[i], &mjumps[i]);

  adj=VVI(2*N+1);
  VVI cap(2*N+1, VI(2*N+1, 0));

  int totpeng=0;
  REP(i, N) {
    totpeng+=npeng[i];
    // edges from source to in vertex ice cube (cap is num penguins)
    adj[2*N].PB(i); adj[i].PB(2*N);
    cap[2*N][i]=npeng[i];
    // edges from in vertex to out vertex (cap is max jumps)
    adj[i].PB(i+N); adj[i+N].PB(i);
    cap[i][i+N]=mjumps[i];
    REP(j, N) if(i!=j && isedge(i,j)) {
      // edges from out vertex to in vertex if jumpable (cap is infinite)
      adj[i+N].PB(j); adj[j].PB(i+N);
      cap[i+N][j]=INF;
    }
  }

  VI res;
  REP(i, N) if(maxflow(2*N, i, cap)==totpeng) res.PB(i);
  if(res.empty()) printf("-1\n");
  else {
    printf("%d", res[0]);
    FOR(i, 1, SZ(res)) printf(" %d", res[i]);
    printf("\n");
  }
}

int main() {
  int nruns;

  scanf("%d", &nruns);
  while(nruns--) go();

  return 0;
}
