/*
  Problem: 3986 - The Bridges of Kölsberg (Live Archive)
  Author: Andrés Mejía-Posada

  Accepted
 */

#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>
using namespace std;

const int MAXN = 1001;

int dp[MAXN+1][MAXN+1], b[MAXN+1][MAXN+1];


/*

  dp[i][j] = Máximo puntaje que puedo alcanzar habiendo creado
   puentes válidos entre las primeros i ciudades del norte y las
   primeras j ciudades del sur.

   b[i][j] = Mínima cantidad de puentes que necesito para obtener un
   puntaje de dp[i][j].

   Notar que dp[i][j] es el máximo entre tres posibles opciones:

   * dp[i-1][j-1] + valor_norte[i] + valor_sur[j], siempre y cuando la
   ciudad norte-i y la ciudad sur-j tengan el mismo sistema
   operativo. Representa la opción de conectar los dos puentes.

   * dp[i][j-1]. Representa la opción de lograr un mejor puntaje
   ignorando la ciudad actual del sur.

   * dp[i-1][j]. Representa la opción de lograr un mejor puntaje
   ignorando la ciudad actual del norte.

*/


int w_north[MAXN+1], w_south[MAXN+1];
int id_north[MAXN+1], id_south[MAXN+1];
char buffer[32];

int main(){
  int cases;
  scanf("%d", &cases);
  while (cases--){
    int n, s, currentID = 1;
    map<string, int> id;
    string os;
    scanf("%d", &n);
    for (int i=1; i<=n; ++i){
      scanf("%11s %11s %d", buffer, buffer, &w_north[i]);
      os = string(buffer);
      if (id[os] > 0) id_north[i] = id[os];
      else id_north[i] = id[os] = currentID++;
    }
    cin >> s;
    for (int j=1; j<=s; ++j){
      scanf("%11s %11s %d", buffer, buffer, &w_south[j]);
      os = string(buffer);
      if (id[os] > 0) id_south[j] = id[os];
      else id_south[j] = id[os] = currentID++;
    }

    for (int i=0; i<=n; ++i) dp[i][0] = b[i][0] = 0;
    for (int j=0; j<=s; ++j) dp[0][j] = b[0][j] = 0;

    for (int i=1; i<=n; ++i){
      for (int j=1; j<=s; ++j){
        dp[i][j] = 0;

        if (dp[i-1][j] > dp[i][j] || (dp[i-1][j] == dp[i][j] && b[i-1][j] < b[i][j])){
          dp[i][j] = dp[i-1][j];
          b[i][j] = b[i-1][j];
        }

        if (dp[i][j-1] > dp[i][j] || (dp[i][j-1] == dp[i][j] && b[i][j-1] < b[i][j])){
          dp[i][j] = dp[i][j-1];
          b[i][j] = b[i][j-1];
        }

        if (id_north[i] == id_south[j]){
          int new_w = dp[i-1][j-1] + w_north[i] + w_south[j];
          if (new_w > dp[i][j] || (new_w == dp[i][j] && b[i-1][j-1] + 1 < b[i][j])){
            dp[i][j] = new_w;
            b[i][j] = b[i-1][j-1] + 1;
          }
        }

      }
    }
    printf("%d %d\n", dp[n][s], b[n][s]);

  }
  return 0;
}
