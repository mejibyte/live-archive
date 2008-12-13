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
    string small = "", big = "";

    int x = n;
    while (x > 3){
      big += "1";
      x -= 2;
    }
    if (x == 2) big += "1";
    else big = "7" + big;

    x = n;
    char m[] = {-1, -1, '1', '7', '4', '2', '6'};
    while (x >= 7){
      small += "8";
      x -= 7;
    }
    if (x > 1) small = m[x] + small;
    else if (x == 1){
      small.erase(small.begin());
      small = "10" + small;
    }

    printf("%s %s\n", small.c_str(), big.c_str());
  }
  return 0;
}
