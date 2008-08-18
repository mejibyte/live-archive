/*
  Accepted
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

    n = v.size();
    sort(v.begin(), v.end());


    /*
    cout << "v es: " << endl;
    for (int i=0; i<v.size(); ++i) cout << v[i] << " ";
    cout << endl;
    */

    int ans = 1, start = 0, end = 1;
    //printf("r es %.13lf\n", r);
    while (end < n){
      if (double(v[end])/double(v[start]) - 1e-9 > r){
        ans++;
        //printf("Contando grupo desde start=%d hasta end=%d [%lld, %lld)\n", start, end, v[start], v[end]);
        //printf("%lld / %lld = %.13lf\n", v[end], v[start], double(v[end])/double(v[start]));
        start = end;
      }
      end++;
    }
    cout << ans << endl;
  }
  return 0;
}
