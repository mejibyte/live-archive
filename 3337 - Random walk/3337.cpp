/*
  Wrong answer
 */
#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

int main() {
  int n;
  cin >> n;
  while(n) {
    int x = 0;
    int y = 0;
    int tempx, tempy;
    double min_dis = 0;
    for(int i =0; i<n; ++i) {
      cin >> tempx;
      cin >> tempy;
      double dist = sqrt(pow(x+tempx,2) + pow(y+tempy,2));
      double dist2 = sqrt(pow(x-tempx,2) + pow(y-tempy,2));
      if(dist>=dist2) {
        x += tempx;
        y += tempy;
        min_dis = dist;
      }
      else {
        x -= tempx;
        y -= tempy;
        min_dis = dist2;
      }
    }
    printf("Maximum distance = %.3lf meters.\n",min_dis);
    cin >> n;
  }
  return 0;
}
