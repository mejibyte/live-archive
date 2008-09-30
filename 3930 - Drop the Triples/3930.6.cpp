/*
  Problem: 3930 - Drop the Triples
  Author: Andrés Mejía-Posada

  Algorithm: DP proposed by jbernadas 
  http://forums.topcoder.com/?module=Thread&threadID=624028&start=0

  Accepted
*/

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
using namespace std;

int memo[1594324]; //3**13 + 1

int GetKey(vector<int>& V) {
  int key = 0;
  for (int k = 0; k < V.size(); ++k)
    key = key * 3 + V[k];
  return key;
}
 
bool IsTriangle(int k1, int k2, int k3) {
  vector<int> V(3);
  V[0] = k1, V[1] = k2, V[2] = k3;
  sort(V.begin(), V.end());
  return V[0] + V[1] > V[2];
}
 
int GetImperfect(vector<int>& V) {
  const int key = GetKey(V);
  //if (memo.count(key) == 0){
  if (memo[key] == -1) {
    memo[key] = 0; int k1;
    for (k1 = 0; k1 < V.size(); ++k1)
      if (V[k1] > 0) break;
    if (k1 < V.size()) {
      const int k1Bak = V[k1]; V[k1] = 0;
      memo[key] = max(memo[key], GetImperfect(V));
      V[k1] = k1Bak;
      V[k1]--;
      for (int k2 = k1; k2 < V.size(); ++k2) if (V[k2] > 0) {
        V[k2]--;
        for (int k3 = k2; k3 < V.size(); ++k3) if (V[k3] > 0) {
          if (k1 + 1 + k2 + 1 <= k3 + 1) continue;
          V[k3]--;
          memo[key] = max(memo[key], GetImperfect(V) + 1);
          V[k3]++;
        }
        V[k2]++;
      }
      V[k1]++;
    }
  }
  return memo[key];
}


int common(vector<int> &x){
  memset(memo, -1, sizeof(int)*GetKey(x));
  return GetImperfect(x);
}


int main(){
  int n;
  while(scanf("%d", &n) == 1 &&n){
    vector<int> a(13, 0), b(13, 0);
    for (int i=0; i<n; ++i){
      int x;
      scanf("%d", &x);
      x--;
      if (i%2) b[x]++;
      else a[x]++;
    }
    /*
      Perfect triples number
     */
    int pa = 0, pb = 0;
    for (int i=0; i<13; ++i){
      pa += a[i] / 3, a[i] %= 3;
      pb += b[i] / 3, b[i] %= 3;
    }

    if (pa != pb){
      puts((pa > pb ? "1" : "2"));
    }else{
      int ca = 0, cb = 0;
      /*
	Common triples number
       */
      //a.erase(a.begin()), b.erase(b.begin());
      ca = common(a), cb = common(b);
      if (ca == cb) puts("0");
      else puts(ca > cb ? "1" : "2");
      
    }
  }
  return 0;
}

