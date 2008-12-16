/*
  Precomputed program generator
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

  printf("#include<stdio.h>\n"
         "char * s[101];\n"
         "int main(){\n");
  for (int i=2; i<=100; ++i){
    const string &small = dp[i];
    string big;
    big = "";
    int x = i;
    while (x > 3) big += "1", x -= 2;
    big = (x == 2 ? "1" : "7") + big;

    printf("s[%d]=\"%s %s\";\n", i, small.c_str(), big.c_str());

  }
  printf("int c,d; for (scanf(\"%%d\", &c); c-- && scanf(\"%%d\", &d); ){\n"
         "puts(s[d]);}"
         "return 0;\n}\n");
  return 0;
}
