/*
  Accepted.
 */
#include <deque>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

using namespace std;

#define V(x) copy(x.begin(), x.end(), ostream_iterator<string>(cout, " ")); cout << endl

string s; int n;

int memo[1005];

map<char, vector<string> > dict;

deque<string> so_far, ans;

bool match(string p, int i, int j){
  if (p.size() == 1) return (i == j && p[0] == s[i]);
  if (p[0] != s[i] || p[p.size()-1] != s[j]) return false;
  if (p.size() == 2) return true;
  string t = s.substr(i, j-i+1);
  sort(t.begin()+1, t.end()-1);
  sort(p.begin()+1, p.end()-1);
  return (t == p);
}

int backtrack(int i){
  if (i >= n){
    ans = so_far;
    return 1;
  }
  if (memo[i] != -1) return memo[i];
  int count = 0;
  vector<string> &possible = dict[s[i]];
  //V(possible);
  int m = possible.size();
  for (int j=0; j<m; ++j){
    string &p = possible[j];
    if (match(p, i, i + p.size() - 1)){
      so_far.push_back(p);
      count += backtrack(i + p.size());
      so_far.pop_back();
    }
  }
  //cout << "backtrack("<<i<<") = " << count << endl;
  return memo[i] = count;
}


int main(){
  int cases;
  cin >> cases;
  while (cases--){
    cin >> s;
    n = s.size();
    assert(n <= 1000);
    dict.clear();
    int m;
    cin >> m;
    assert(m <= 10000);
    while (m--){
      string t;
      cin >> t;
      dict[t[0]].push_back(t);
    }
    memset(memo, -1, sizeof memo);
    so_far.clear();
    int count = backtrack(0);
    if (count == 0) cout << "impossible" << endl;
    else if (count > 1) cout << "ambiguous" << endl;
    else{
      cout << ans[0];
      for (int i=1; i<ans.size(); ++i){
        cout << " " << ans[i];
      }
      cout << endl;
    }

  }
  return 0;
}
