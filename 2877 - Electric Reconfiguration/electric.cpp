#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct pnt{
       long long x, y;
       pnt(){}
       pnt(long long _x, long long _y) : x(_x), y(_y) {}
       bool operator < (const pnt &t) const{
           return x < t.x || (x == t.x && y < t.y);
       }
};

bool colineales(pnt a, pnt b, pnt c){
     return (b.x - a.x)*(c.y - a.y) - (c.x - a.x)*(b.y - a.y) == 0;
}

int main(){
    int n;
    while (cin >> n && n){
          vector<pnt> p(n);
          for (int i=0; i<n; ++i) cin >> p[i].x >> p[i].y;
          
          int ans = 0;
          for (int i=0; i<n; ++i){
              for (int j=i+1; j<n; ++j){
                  int t = 2;
                  for (int k=j+1; k<n; ++k){
                      t += colineales(p[i], p[j], p[k]);
                      //printf("i=%d, j=%d, k=%d, t=%d, ans=%d\n", i,j,k,t,ans);
                  }
                  if (t > ans) ans = t;
              }
          }
          cout << ans << endl;
    }
    return 0;
}
