#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n) FOR(i,0,n)
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n) FORE(i,0,n)
#define REPSZ(i,v) REP(i,SZ(v))
#define FORSZ(i,a,v) FOR(i,a,SZ(v))
typedef pair<int,int> PII;
const int DX[]={-1,0,+1,0},DY[]={0,+1,0,-1};

int h,w,d;
int g[1000][1000];

int done[1000][1000];

typedef struct heightcomp { bool operator()(const PII &a,const PII &b) { return g[a.first][a.second]>g[b.first][b.second]; } } heightcomp;

void run() {
	scanf("%d%d%d",&h,&w,&d);
	REP(i,h) REP(j,w) scanf("%d",&g[i][j]);
	vector<PII> p; REP(i,h) REP(j,w) p.PB(MP(i,j)); sort(p.begin(),p.end(),heightcomp());
	memset(done,-1,sizeof(done));
	vector<PII> ret;
	REPSZ(i,p) {
		int sx=p[i].first,sy=p[i].second;
		if(done[sx][sy]!=-1) continue;
		bool ok=true; vector<PII> cur; queue<PII> q;
		q.push(MP(sx,sy)); done[sx][sy]=i;
		while(!q.empty()) {
			int x=q.front().first,y=q.front().second; q.pop();
			if(g[x][y]==g[sx][sy]) cur.PB(MP(y,x));
			REP(k,4) {
				int nx=x+DX[k],ny=y+DY[k];
				if(nx<0||nx>=h||ny<0||ny>=w) continue;
				if(g[nx][ny]<=g[sx][sy]-d) continue;
				if(done[nx][ny]==i) continue;
				if(done[nx][ny]!=-1) { ok=false; continue; }
				q.push(MP(nx,ny)); done[nx][ny]=i;
			}
		}
		if(ok) ret.insert(ret.end(),cur.begin(),cur.end());
	}
//	REP(i,h) REP(j,w) printf("%2d%c",done[i][j],j==w-1?'\n':' ');
	
	sort(ret.begin(),ret.end());
	printf("%d\n",SZ(ret));
	// commented out by Jan
	//	REPSZ(i,ret) printf("%d %d\n",ret[i].first,ret[i].second);
}

int main() {
	int n; scanf("%d",&n); FORE(i,1,n) run();
	return 0;
}
