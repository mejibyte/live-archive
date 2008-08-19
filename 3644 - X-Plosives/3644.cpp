/*
  Accepted
 */
#include<iostream>
#include<string>
#include<cstring>
#include<math.h>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<stack>
#include<queue>
#include<list>
#include<sstream>
#include<assert.h>
using namespace std;

const int maxn = 100001;

int p[maxn+1], rank[maxn+1];

void make_set(int x){ p[x] = x; rank[x] = 0; }
void link(int x, int y){
  if (rank[x] > rank[y]) p[y] = x;
  else{
    p[x] = y;
    rank[y] += (rank[x] == rank[y]);
  }
}
int find_set(int x){
  if (x != p[x]) p[x] = find_set(p[x]);
  return p[x];
}
bool same_set(int x, int y){ return find_set(x) == find_set(y); }
void merge(int x, int y){ link(find_set(x), find_set(y)); }

/*
  Con entrada así:
  1 2
  2 3
  -1

  1 2
  2 3
  -1
 */

int main(){
  string s;

  for (int i=0; i<=maxn; ++i){
    make_set(i);
  }
  int ans = 0;

  while (true){
    if (!getline(cin, s)) return 0;

    if (s == "-1"){
      //cout << "terminando casito\n";
      for (int i=0; i<=maxn; ++i){
        make_set(i);
      }
      cout << ans << endl;
      getline(cin, s); //Linea en blanco o nada
      ans = 0;
    }
    //cout << "leí linea s = " << s << endl;
    int u, v;
    stringstream sin(s);
    if (sin >> u >> v){
      assert(0 <= u && u <= 100000);
      assert(0 <= v && v <= 100000);

      if (same_set(u, v)){
        ans++;
      }else{
        merge(u, v);
      }
    }
  }
  return 0;
}

