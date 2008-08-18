#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int dgr[1010];
bool borrado[1010];


int dfs(int u, vector<int> * g){
  if (borrado[u]) return 0;
  borrado[u] = true;
  int ans = 1;
  vector<int> & veci = g[u];
  for (int i=0; i<veci.size(); ++i){
    if (!borrado[veci[i]]){
      ans += dfs(veci[i], g);
    }
  }
  return ans;
}

int main(){
  int n, p, k;
  while (cin >> n && n){
    cin >> p >> k;


    for (int i=0; i<n; ++i){
      dgr[i] = borrado[i] = false;
    }

    vector<int> g[n];

    while (p--){
      int u, v;
      cin >> u >> v;
      --u, --v;
      g[u].push_back(v);
      g[v].push_back(u);
      dgr[u]++, dgr[v]++;
    }


    bool cambio = true;
    while (cambio){
      cambio = false;
      for (int i=0; i<n; ++i){
        if (dgr[i] < k && !borrado[i]){
          borrado[i] = true;
          vector<int> &veci = g[i];
          for (int j=0; j<veci.size(); ++j){
            dgr[veci[j]]--;
          }
          cambio = true;
        }
      }
    }
    int ans = 0;
    //buscar componente conexa con mas nodos
    for (int i=0; i<n; ++i){
      if (!borrado[i]){
        int nodos = dfs(i, g);
        if (nodos > ans) ans = nodos;
      }
    }
    cout << ans << endl;
  }

  return 0;
}
