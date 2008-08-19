#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char buf[512], t[512], z[512], keyboard[32][32];

int dp[512][512];

const int infinity = 1<<30;

int main(){
  int i, j, rows, cols;
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


    fprintf(stderr, "Mostrando keyboard (%d x %d):\n", rows, cols);
    for(i=0; i<rows; ++i){
      fprintf(stderr, "%s\n", keyboard[i]);
    }

    t[0] = z[0] = ' ';
    fgets(&(z[1]), 511, stdin);
    fgets(&(t[1]), 511, stdin);

    int _z = strlen(z);
    int _t = strlen(t);
    z[--_z] = t[--_t] = '\0';

    fprintf(stderr, "Mostrando z (_z=%d) y t (_t=%d)\n", _z, _t);
    fprintf(stderr, "z = %s\n", z);
    fprintf(stderr, "t = %s\n", t);

    dp[0][0] = 0;
    for (j=1; j<_z; ++j){
    }

  }
  return 0;
}
