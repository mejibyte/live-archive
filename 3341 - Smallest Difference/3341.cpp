/*
  Problem: 3341 - Smallest Difference
  Author: Andrés Mejía-Posada
  (http://blogaritmo.factorcomun.org)

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

int to_number(const vector<int> &x){
  int ans = 0;
  for (int i=0; i<x.size(); ++i){
    ans = 10*ans + x[i];
  }
  return ans;
}

void no_leading_zero(vector<int> &x){
  if (x[0] == 0 && x.size() > 1) swap(x[0], x[1]);
}

int score(vector<int> &a, vector<int> &b){
  if (a.size() == 1 && b.size() == 1) return abs(a[0] - b[0]);


  if (a.size() != b.size()){
    vector<int> &big = a, &small = b;
    if (a.size() < b.size()) swap(big, small);


    sort(big.begin(), big.end());
    sort(small.begin(), small.end(), greater<int>());

    no_leading_zero(big), no_leading_zero(small);

    return (to_number(big) - to_number(small));
  }else{
    //mismo tamaño
    int n = a.size();
    int ans = INT_MAX;
    for (int i=0; i<n; ++i){
      for (int j=0; j<n; ++j){
        vector<int> big = a, small = b;
        swap(big[0], big[i]);
        swap(small[0], small[j]);
        if (big[0] == 0 || small[0] == 0) continue;

        if (big[0] < small[0]) swap(big, small);

        sort(big.begin()+1, big.end());
        sort(small.begin()+1, small.end(), greater<int>());

        int t = to_number(big) - to_number(small);
        if (t < 0){
          D(to_number(big));
          D(to_number(small));
        }

        ans <?= t;
      }
    }
    return ans;
  }
}

int solve(vector<int> &numbers){
  int n = numbers.size();
  int best = INT_MAX;
  for (int mask=1; mask<(1<<n)-1; ++mask){
    vector<int> a, b;
    for (int i=0; i<n; ++i){
      if (mask & (1 << i)) a.push_back(numbers[i]);
      else b.push_back(numbers[i]);
    }
    best <?= score(a, b);
  }
  return best;
}

int main(){
  int cases;
  cin >> cases;
  string line;
  getline(cin, line);
  while (cases--){
    getline(cin, line);
    stringstream sin(line);
    vector<int> numbers;
    for (int x; sin >> x; ){
      numbers.push_back(x);
    }
    cout << solve(numbers) << endl;
  }
  return 0;
}
