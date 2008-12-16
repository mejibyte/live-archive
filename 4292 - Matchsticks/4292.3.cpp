/*
  Accepted
  Dynamic programming
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

const string oo = string(100, '9');
string dp[101];

bool operator < (const string &a, const string &b){
  if (a.size() != b.size()) return a.size() < b.size();
  return lexicographical_compare(a.begin(), a.end(),
                                 b.begin(), b.end());
}

int sticks[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int main(){
  dp[0] = "";
  dp[1] = oo;

  for (int s=2; s<=100; ++s){
    string &ans = dp[s];
    ans = oo;
    //add digit at left
    for (int d=1; d<=9; ++d){
      if (s - sticks[d] >= 0){
        string t = static_cast<char>('0' + d) + dp[s - sticks[d]];
        if (t < ans) ans = t;
      }
    }
    //add digit at right
    for (int d=0; d<=9; ++d){
      if (d == 0 && s - sticks[d] == 0) continue; //Adding 0 as a first digit
      if (s - sticks[d] >= 0){
        string t = dp[s - sticks[d]] + static_cast<char>('0' + d);
        if (t < ans) ans = t;
      }
    }
  }


  int cases;
  for (scanf("%d", &cases); cases--; ){
    int n, x;
    scanf("%d", &n);
    const string &small = dp[n];
    string big;

    big = "";
    x = n;
    while (x > 3) big += "1", x -= 2;
    big = (x == 2 ? "1" : "7") + big;

    printf("%s %s\n", small.c_str(), big.c_str());
  }
  return 0;
}
