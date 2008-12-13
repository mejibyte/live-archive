/*
  Problem: 4215 - Feynman
  Author: Andrés Mejía-Posada
  (http://blogaritmo.factorcomun.org)

 */

#include <stdio.h>
int d[101], i, x;

int main(){
  d[0] = 0;
  for (i=1; i<=100; d[i] = i*i + d[i-1], i++);
  for (; scanf("%d", &x)==1 && x; printf("%d\n", d[x]));
  return 0;
}
