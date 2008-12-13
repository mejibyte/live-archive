/*
  Problem: 4215 - Pole position
  Author: Andrés Mejía-Posada
 */

using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>

#define D(x) cout << #x " is " << x << endl

int n;
void race(){
  vector<int> a(n), b(n, -1), delta(n);
  for (int i=0; i<n; ++i){
    scanf("%d %d", &a[i], &delta[i]);
  }

  for (int i=0; i<n; ++i){
    int d = delta[i];
    if (i + d <= -1 || i + d >= n || b[i + d] != -1){
      printf("-1\n");
      return;
    }
    b[i + d] = a[i];
  }
  printf("%d", b[0]);
  for (int i=1; i<n; ++i){
    printf(" %d", b[i]);
  }
  printf("\n");
}

int main(){
  while (scanf("%d", &n) && n){
    race();
  }
  return 0;
}
