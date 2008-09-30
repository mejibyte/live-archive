/*
  Problem: 3173 - Wordfish
  Algorithm: Ad-hoc
  Author: Andrés Mejía-Posada
 */

#include <algorithm>
#include <iostream>
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

int dist(string s){
  int ans = INT_MAX;
  int n = s.size();
  for (int i=0; i<n-1; ++i) ans = min(ans, abs(s[i] - s[i+1]));
  return ans;
}

int main(){
  string s;
  while (cin >> s){
    assert(s.size() > 1);
    
    deque<string> p(1, s);
    string t;

    t = s;
    for (int i=0; i<10; ++i){
      next_permutation(t.begin(), t.end());
      p.push_back(t);
    }

    t = s;
    for (int i=0; i<10; ++i){
      prev_permutation(t.begin(), t.end());
      p.push_front(t);
    }

    sort(p.begin(), p.end()); //Useless?

    int score = -1; string ans;
    for (deque<string>::iterator k = p.begin(); k != p.end(); ++k){
      int t = dist(*k);
      if (t > score){
	score = t;
	ans = *k;
      }
    }
    cout << ans << score << endl;
     
  }
  return 0;
}
