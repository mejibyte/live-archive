/*
  Accepted
 */
#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
using namespace std;

long long area, ancho, alto, x, y, z;

const long long infinity = (1LL << 63) - 1;

int main(){
  int C;
  scanf("%d", &C);
  while (C--){
    long long n;
    scanf("%lld", &n);
    n = n/5 + (n%5 > 0); //numero de stacks

    area = ancho = alto = infinity;
    for (long long b = 1; b*b <= n; ++b){
      long long a = n/b + (n%b > 0);
      x = 44*b + 4;
      y = 10*a + 2;
      long long z = x*y;
      if (z < area || (z == area && abs(x-y) < abs(ancho-alto))){
        area = z;
        ancho = x;
        alto = y;
      }
    }
    x = alto, y = ancho;
    printf("%lld X %lld = %lld\n", x >? y, x <? y, area);
  }
  return 0;
}
