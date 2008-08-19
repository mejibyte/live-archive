#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define max(a,b) ((a)>(b)?(a):(b))
#define infinity 1<<30

char buf[512], t[512], z[512], keyboard[32][32];
int dp[512][512], rows, cols;

int distancia(char a, char b){
  int x0, y0, x1, y1, i, j;
  if (a == b) return 0;
  for (i=0; i<rows; ++i){
    for (j=0; j<cols; ++j){
      if (keyboard[i][j] == a){
        x0 = i, y0 = j;
      }
      if (keyboard[i][j] == b){
        x1 = i, y1 = j;
      }
    }
  }
  return max(abs(x0-x1), abs(y0-y1));
}

int main(){
  int i, j, _z, _t, top;
  while (fgets(buf, 512, stdin) != NULL){
    sscanf(buf, "%d", &rows);
    assert(rows > 0);

    fgets(keyboard[0], 32, stdin);
    cols = strlen(keyboard[0]);
    /* Borrar el fin de línea */
    keyboard[0][--cols] = '\0';
    for (i=1; i<rows; ++i){
      fgets(keyboard[i], 32, stdin);
      keyboard[i][cols] = '\0';
    }

    /*
    fprintf(stderr, "Mostrando keyboard (%d x %d):\n", rows, cols);
    for(i=0; i<rows; ++i){
      fprintf(stderr, "%s\n", keyboard[i]);
    }
    */

    t[0] = z[0] = ' ';
    fgets(&(z[1]), 511, stdin);
    fgets(&(t[1]), 511, stdin);

    _z = strlen(z);
    _t = strlen(t);
    z[--_z] = t[--_t] = '\0';

    /*
    fprintf(stderr, "Mostrando z (_z=%d) y t (_t=%d)\n", _z, _t);
    fprintf(stderr, "z = %s\n", z);
    fprintf(stderr, "t = %s\n", t);
    */

    top = max(rows, cols);

    dp[0][0] = 0;
    for (j=1; j<_z; ++j){
      dp[0][j] = dp[0][j-1] - top;
    }
    for (i=1; i<_t; ++i){
      for (j=0; j<_z; ++j){
        if (i > j) dp[i][j] = -infinity;
        else dp[i][j] = max(dp[i][j-1]-top, dp[i-1][j-1]+top-distancia(t[i], z[j]));
      }
    }

    sprintf(buf, "%d\n", dp[_t-1][_z-1]);
    fputs(buf, stdout);
  }
  return 0;
}

