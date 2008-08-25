#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

enum{ Down, Right };

vector<int> merge(const vector<int> &p, const vector<int> &q){
  /*
    Retorna un vector que contiene el mejor orden posible para
    tomar un elemento a la vez de la izquierda de p o la izquierda de
    q. Estos elementos forman una secuencia A_1, A_2, ..., A_n que
    debe cumplir que Sumatoria desde i = 1 hasta n de i*A_i sea
    mínimo. El vector retornado contiene la secuencia A_1, A_2, ...

    Por ejemplo, si p = <2,1,3> y q =<1,4> entonces ans = <1,4,2,1,3>
    pues 1*1+4*2+2*3+1*4+3*5=34, que es mínimo.
   */
  vector<int> ans;
  int _p = p.size(), _q = q.size();

  int dp[_p+1][_q+1], decision[_p+1][_q+1];

  dp[_p][_q] = 0;
  for (int i=_p; i>=0; --i){
    for (int j=_q; j>=0; --j){
      if (i != _p || j != _q){ //no es la esquina
        dp[i][j] = INT_MAX;
        if (i < _p){
          int t = (i+j+1)*p[i] + dp[i+1][j];
          if (t < dp[i][j]){
            dp[i][j] = t;
            decision[i][j] = Down;
          }
        }
        if (j < _q){
          int t = (i+j+1)*q[j] + dp[i][j+1];
          if (t < dp[i][j]){
            dp[i][j] = t;
            decision[i][j] = Right;
          }
        }
      }
    }
  }

  int i = 0, j = 0;
  while (i != _p || j != _q){
    if (decision[i][j] == Down){
      ans.push_back(p[i++]);
    }else if (decision[i][j] == Right){
      ans.push_back(q[j++]);
    }
  }
  return ans;
}


int cost[1001];
vector<int> g[1001];


vector<int> solve(int u){
  vector<int> ans;
  for (int i=0; i<g[u].size(); ++i){
    ans = merge(ans, solve(g[u][i]));
  }
  ans.insert(ans.begin(), cost[u]);
  /*cout << "solve(" << u << ") = ";
  copy(ans.begin(), ans.end(), ostream_iterator<int>(cout, " "));
  cout << endl;*/
  return ans;
}


int main(){

  /*vector<int> a, b, c;

  a.push_back(2); a.push_back(2);

  b.push_back(1); b.push_back(4);

  c = merge(a, b);
  copy(c.begin(), c.end(), ostream_iterator<int>(cout, " "));
  cout << endl;*/

  int n, r;
  while (cin >> n >> r && n && r){
    --r;
    for (int i=0; i<n; ++i){
      cin >> cost[i];
      g[i].clear();
    }
    for (int i=1; i<n; ++i){
      int u, v;
      cin >> u >> v;
      --u, --v;
      g[u].push_back(v);
    }

    vector<int> v = solve(r);
    /*
    cout << " v es: ";
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    */
    int ans = 0;
    for (int i=1; i<=n; ++i){
      ans += v[i-1]*i;
    }
    cout << ans << endl;
  }

  return 0;
}
