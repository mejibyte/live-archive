/*
  Wrong answer, debido a un overflow en la línea ((z*z)%m*z)%m
 */
#include <iostream>
#include <stdio.h>
#include <assert.h>
using namespace std;

typedef unsigned long long llu;

llu f(llu pow10, llu x, llu y){
  llu m = pow10*10;
  for (llu d=0; d<10; ++d){
    llu z = ((pow10%m)*(d%m))%m;
    z = ((z%m) + (x%m))%m;
    //printf(" before bigmoding z = %llu\n", z);
    z = (((z*z)%m)*z)%m;
    //printf(" after  bigmoding z = %llu\n", z);
    //printf(" -                         z = %llu, d=%llu, x=%llu, pow10=%llu\n", z, d, x, pow10);
    if (z / pow10 == y) return d*pow10 + x;
  }
  //assert(false);
  return 0;
}

int main(){
  int m;
  scanf("%d", &m);
  while (m--){
    llu n;
    scanf("%llu", &n);

    llu x = 0, pow10 = 1;
    while (n){
      x = f(pow10, x, n%10);
      //printf(" ->OK. %llu\n", x);
      n /= 10;
      pow10 *= 10;
    }
    printf("%llu\n", x);
  }

  return 0;
}
