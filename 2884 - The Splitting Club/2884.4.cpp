/*
  Accepted.
 */
#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <algorithm>
#include <string.h>
#include <assert.h>

using namespace std;

long long members[121];

int main(){
  int n;
  double r;
  while (cin >> n >> r && n){

    memset(members, 0, sizeof members);

    for (int i=0; i<n; ++i){
      int count, age;
      cin >> count >> age;
      members[age] += count;
    }

    vector<long long> v;
    for (int i=1; i<=120; ++i){
      if (members[i]) v.push_back(members[i]);
    }

    //cout << "v es: " << endl;
    //for (int i=0; i<v.size(); ++i) cout << v[i] << " ";
    //cout << endl;

    n = v.size();
    sort(v.begin(), v.end());
    int ans = 1, start = 0, end = 1;
    while (end < n){
      if (v[end] - 1e-9 > r*v[start]){
        ans++;
        start = end;
      }
      end++;
    }
    cout << ans << endl;
  }
  return 0;
}
