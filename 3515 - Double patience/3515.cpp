/*
  Problem: 2331. Double Patience
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

typedef int state[9];
int piles[9][5];


int getKey(state s){
  int r = 0;
  for (int i=0; i<9; ++i){
    r = 5*r + s[i];
  }
  return r;
}

bool   been[1953125];
double memo[1953125];

double f(state s){
  int key = getKey(s);

  //for (int i=0; i<9; ++i) printf("%d ", s[i]); printf("\n");

  if (key == 0) return 1.0;
  if (been[key]) return memo[key];

  double ans = 0.0;
  int cnt = 0;
  for (int i=0; i<9; ++i){
    for (int j=i+1; j<9; ++j){
      if (piles[i][s[i]] == piles[j][s[j]] && s[i] > 0 && s[j] > 0){
        s[i]--, s[j]--;
        cnt++;
        ans += f(s);
        s[i]++, s[j]++;
      }
    }
  }
  if (cnt) ans /= cnt;

  been[key] = true;
  return memo[key] = ans;
}


int rank(const string &s){
  if ('0' <= s[0] && s[0] <= '9') return s[0] - '0';
  char r[] = { 'T', 'J', 'Q', 'K', 'A' };
  for (int i=0; i<5; ++i){
    if (s[0] == r[i]) return i + 10;
  }
  return -1;
}

int main(){

  while (1){
    for (int i=0; i<9; ++i){
      piles[i][0] = -1;
      for (int j=1; j<=4; ++j){
        string s;
        if (!(cin >> s)) return 0;
        piles[i][j] = rank(s);
      }
    }

    state initial;
    for (int i=0; i<9; ++i) initial[i] = 4;

    memset(been, 0, sizeof been);
    double ans = f(initial);

    cout << ans << endl;

  }
  return 0;
}
