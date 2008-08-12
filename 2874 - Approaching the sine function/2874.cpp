/*
Wrong answer
 */
#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

inline long double round_to(long double x, long double d){
  long double powd = pow(10, d);
  return floor(x*powd+0.5)/powd;
}

int main(){
  long double x, d;
  while (cin >> x >> d){
    long double seno = round_to(sin(x), d), powd = pow(10, d);
    printf("sin(%.1llf) = %.12llf\n", x, seno);
    int k=0;
    long double sum=0, rounded;
    do{
      long double term = 1.0;
      for (int i=1; i<=2*k+1; ++i){
        term *= (x/i);
      }
      if (k%2)
        sum -= term;
      else
        sum += term;
      ++k;

      rounded = round_to(sum, d);
      printf("k=%d, sum=%.12llf, rounded=%.12llf\n", k, sum, rounded);
      char c; cin >> c;
    }while(floor(sum*powd+0.5) != floor(seno*powd+0.5));
    cout << k - 1 << endl;
  }
  return 0;
}
