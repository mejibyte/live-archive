/*
  Time Limit Exceeded
 */
#include <iostream>
#include <algorithm>

using namespace std;

/*
dp[i][j] = maxima cantidad de acorns que puedo recoger terminando
en la altura j del i-ésimo árbol.

g[i][j] = cantidad de acorns que hay en el arbol i-ésimo a una
altura j.
*/

int dp[2000][2001], g[2000][2001];

int main(){
  int c;
  cin >> c;
  while (c--){
    int t, h, f;
    cin >> t >> h >> f;
    for (int i=0; i<t; ++i){
      for (int j=0; j<=h; ++j){
        dp[i][j] = 0;
        g[i][j] = 0;
      }
      int a;
      cin >> a;
      while (a--){
        int n;
        cin >> n;
        g[i][n]++;
      }
    }

    int answer = 0;
    for (int i=0; i<t; ++i){
      dp[i][h] = g[i][h]; //En la rama más alta solo puedo recoger las que haya allí
    }


    for (int j=h-1; j>=0; --j){
      for (int i=0; i<t; ++i){
        /*
          para llegar a la rama i, en una altura j, tengo varias opciones:
          o llegue de la misma rama una unidad más arriba, o llegué de otra rama f unidades
          más arriba
        */
        dp[i][j] = dp[i][j+1];
        if (j + f <= h){
          for (int k=0; k<t; ++k){
            dp[i][j] = max(dp[i][j], dp[k][j+f]);
          }
        }
        dp[i][j] += g[i][j];
        answer = max(answer, dp[i][j]);
      }
    }
    cout << answer << endl;
  }
  return 0;
}
