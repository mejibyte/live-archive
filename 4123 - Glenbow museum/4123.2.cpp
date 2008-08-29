/*
  Accepted.
 */
#include <iostream>
#include <string.h>
#include <assert.h>

using namespace std;

/*
  Después de rayar un rato, se observa lo siguiente: todo polígono cerrado tiene al menos 4 R's.
  Si hay dos O's juntas, entonces la cadena deja de ser válida. Por cada O que haya, hay exactamente
  una R. Luego, la solución es la cantidad de cadenas diferentes que no tengan dos O juntas y tengan
  una longitud L, usando (L+4)/2 R's y el resto de O's.

  dp[i][j][k] = cantidad de cadenas de longitud i que tienen j erres (y i - j oes).
  Si k == 1, estas cadenas terminan en O. Si k == 0, terminan en r.
 */
long long dp[1001][1001][2];

int main(){
  memset(dp, 0, sizeof dp);
  /*
    Decimos que solo podemos empezar las cadenas con una R, con el fin
    de evitar contar cadenas inválidas que empiezan y terminan en O, por
    ejemplo ORRRRO. La observación es que por cada cadena que empiece
    estrictamente en R y termine en O, podemos formar otra que empiece
    en O y termine en R (entonces sumamos dos veces la cantidad de
    cadenas que empiezan en R y terminan en O al resultado final).
   */
  dp[1][1][0] = 1;
  for (int i=2; i<=1000; ++i){
    for (int j=0; j<=1000; ++j){
      for (int k=0; k<2; ++k){
        if (k == 0){
          if (j > 0){
            dp[i][j][k] = dp[i-1][j-1][0] + dp[i-1][j-1][1];
          }
        }else{
          dp[i][j][k] = dp[i-1][j][0];
        }
      }
    }
  }
  int n, C=1;
  while (cin >> n && n){
    cout << "Case " << C++ << ": ";
    if (n % 2) cout << "0";
    else{
      long long t = dp[n][(n+4)/2][0] + 2*dp[n][(n+4)/2][1];
      cout << t;
    }
    cout << endl;
  }
  return 0;
}
