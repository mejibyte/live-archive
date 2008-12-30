/*
  Andrés Mejía-Posada (andmej@gmail.com)
  Algorithm: DP (Works for n <= 10)
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
#include <list>
#include <map>
#include <set>
#define D(x) cout << #x " is " << x << endl

const int MAXN = 15;
/*
  dp[used][last][side] = True if I can finish the path
  having visited the nodes told on "used" and the last
  node is "last" on side "side" (0 || 1).
*/
int dp[1 << MAXN][MAXN][2];
vector<int> conf[MAXN];
int n, c;

bool f(int used, int last, int side){
  if (side >= conf[last].size()) return false;
  if (used == (1 << n) - 1) return true; //Got everything!

  int &ans = dp[used][last][side];
  if (ans != -1) return ans;

  ans = false;
  int my_conf = conf[last][side];
  for (int j=0; j<n; ++j){
    if (j != last && !(used & (1 << j))){
      if (my_conf == conf[j][0]){
        ans |= f(used | (1 << j), j, (conf[j].size() == 1 ? 0 : 1));
      }
      if (conf[j].size() > 1 && my_conf == conf[j][1]){
        ans |= f(used | (1 << j), j, 0);
      }
    }
  }
  return ans;
}

int main(){
  while (scanf("%d %d", &n, &c)==2 && n && c){
    if (n > MAXN){
      printf("This algorithm works only for n <= %d\n", MAXN);
      printf("An error will occur.\n");
    }

    for (int last=0; last<n; ++last){
      for (int used=0; used<(1<<n); ++used){
        dp[used][last][0] = dp[used][last][1] = -1;
      }
      conf[last].clear();
    }

    for (int i=0; i<c; ++i){
      int k;
      scanf("%d", &k);
      for (int j=0; j<k; ++j){
        int x;
        scanf("%d", &x);
        conf[x].push_back(i);
      }
    }

    bool solved = false;
    for (int i=0; i<n; ++i){
      if (f(1 << i, i, 0) || f(1 << i, i, 1)){
        printf("%d\n", i);
        solved = true;
        break;
      }
    }
    if (!solved) printf("-1\n");
  }
  return 0;
}
