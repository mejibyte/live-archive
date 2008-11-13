/*
  Time limit exceeded

  Algorithm: Backtracking
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

enum { pop1, push1, pop2, push2 };
string name[] = { "pop 1", "push 1", "pop 2", "push 2" };

int n;
vector<int> solution;
deque<int> s1, s2, stock, ans;


int solve(int buscando){
  if (buscando == n) return true;
  else if (solution[buscando] == s1.back() || solution[buscando] == s2.back()){
    if (solution[buscando] == s1.back()){
      int t = s1.back();
      s1.pop_back();
      ans.push_back(pop1);
      if (solve(buscando+1)) return true;
      ans.pop_back();
      s1.push_back(t);
    }else if (solution[buscando] == s2.back()){
      int t = s2.back();
      s2.pop_back();
      ans.push_back(pop2);
      if (solve(buscando+1)) return true;
      ans.pop_back();
      s2.push_back(t);
    }
  }
  else{
    assert(stock.size() > 0);
    int x = stock.back();
    stock.pop_back();

    //Meterlo a uno de los stack
    if(x <= s1.back()){
      s1.push_back(x);
      ans.push_back(push1);
      if (solve(buscando)) return true;
      assert(x == s1.back());
      s1.pop_back();
      ans.pop_back();
    }


    if(x <= s2.back()){
      s2.push_back(x);
      ans.push_back(push2);

      if (solve(buscando)) return true;

      assert(x == s2.back());
      s2.pop_back();
      ans.pop_back();
    }
    stock.push_back(x);
  }
  return false;
}


int main(){
  for (int caso=1; cin>>n && n; ++caso){

    s1.clear(), s2.clear(), stock.clear(), solution.clear(), ans.clear();

    for(int i=0, t; i<n && cin >> t; ++i){
      solution.push_back(t);
      stock.push_back(t);
    }
    sort(solution.begin(), solution.end());

    s1.push_back(INT_MAX);
    s2.push_back(INT_MAX);

    cout << "#" << caso << endl;
    if (solve(0)){
      for (int i=0; i<ans.size(); ++i){
        cout << name[ans[i]] << endl;
      }
      cout << endl;
    }else{
      cout << "impossible\n";
    }
  }
  return 0;
}
