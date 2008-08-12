#include <cmath>
#include <iostream>
#include <stdio.h>

using namespace std;

int main(){
  double k, conc;
  int m, n;
  while (cin >> k >> conc >> m >> n && (k+conc+m+n>0.0)){
    double a = m*n;
    double b = k;
    double c = -b*conc;
    double x = (-b + sqrt(b*b - 4*a*c)) / 2.0*a;
    //printf("%.3lf\n", x);
    printf("%.3lf\n", -log10(x/(m*n*n)));

  }
  return 0;
}
