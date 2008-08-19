/*
  Wrong answer
 */
#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

int main(){
  int n;
  double r;
  while (cin >> n >> r && n){
    vector<int> v(n);
    for (int i=0; i<n; ++i){
      int age;
      cin >> v[i] >> age;
    }

    sort(v.begin(), v.end());
    int ans = 1, start = 0, end = 1;
    while (end < n){
      if (v[end] > r*v[start]){
        ans++;
        start = end;
      }
      end++;
    }
    cout << ans << endl;
  }
  return 0;
}
