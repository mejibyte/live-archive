/*
Wrong answer

Usando asserts descubrí que:
0 < d <= 12
0 <= |x| <= 7
 */
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;

const double pi = acos(-1.0);

int main(){
  double x, d;
  while (cin >> x >> d){
    assert(0.0 < d && d <= 12.0);
    assert(0.0 <= fabs(x) && fabs(x) <= 7.0);
    double seno = sin(x), powd = pow(10, d);
    int k=0;
    double sum=0;
    do{
      double term = 1.0;
      for (int i=1; i<=2*k+1; ++i){
        term *= (x/i);
      }
      if (k%2)
        sum -= term;
      else
        sum += term;
      ++k;
    }while(floor(sum*powd+0.5) != floor(seno*powd+0.5));
    assert(k - 1 <= 15);
    cout << k - 1 << endl;
  }
  return 0;
}
