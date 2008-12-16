/*
  Accepted
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

int main(){
  int cases;
  for (scanf("%d", &cases); cases--; ){
    int n;
    scanf("%d", &n);
    string small, big, s[18];

    s[2] = "1";
    s[3] = "7";
    s[4] = "4";
    s[5] = "2";
    s[6] = "6";
    s[7] = "8";
    s[8] = "10";
    s[9] = "18";
    s[10] = "22";
    s[11] = "20";
    s[12] = "28";
    s[13] = "68";
    s[14] = "88";
    s[15] = "108";
    s[16] = "188";
    s[17] = "200";

    small = "";
    int x = n;
    while (x > 17) small += "8", x -= 7;
    small = s[x] + small;

    big = "";
    x = n;
    while (x > 3) big += "1", x -= 2;
    big = s[x] + big;

    printf("%s %s\n", small.c_str(), big.c_str());
  }
  return 0;
}
