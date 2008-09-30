/*
  Problem: 3930 - Drop the Triples
  Author: Andrés Mejía-Posada
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

#define V(x) cout << #x " is: "; if (x.size() > 0 ) copy(x.begin(), x.end(), ostream_iterator<typeof(x[0])>(cout, " ")); cout << endl

int ans;
deque<int> so_far;

void backtrack(int used, const vector<int> &x){
  int m = so_far.size(), n = x.size();
  ans >?= m/3;

  for (int i=0; i<n; ++i){
    if (!(used & (1 << i))){
      if (m%3==0 || (x[i] >= so_far[m-1] && (m%3==1 || (m%3==2 && so_far[m-2] + so_far[m-1] > x[i])))){
	so_far.push_back(x[i]);
	backtrack(used | (1 << i), x);
	so_far.pop_back();
      }
    }
  }
  
}

int common(const vector<int> &x){
  so_far.clear();
  ans = 0;
  backtrack(0, x);
  return ans;
}


int main(){
  int n, C=1;
  while(cin>>n &&n){
    cerr << C++ << endl;
    vector<int> a(14, 0), b(14, 0);
    for (int i=0; i<n; ++i){
      int x;
      cin >> x;
      if (i%2) b[x]++;
      else a[x]++;
    }
    int pa = 0, pb = 0;
    for (int i=1; i<=13; ++i){
      while (a[i] >= 3) a[i]-=3, pa++;
      while (b[i] >= 3) b[i]-=3, pb++;
    }

    if (pa != pb){
      cout << (pa > pb ? "1" : "2") << endl;
    }else{
      int ca = 0, cb = 0;
      vector<int> xa, xb;
      for (int i=1; i<=13; ++i){
	while (a[i]--) xa.push_back(i);
	while (b[i]--) xb.push_back(i);
      }  

      //V(xa); V(xb);

      ca = common(xa), cb = common(xb);
      if (ca == cb) cout << "0\n";
      else cout << (ca > cb ? "1" : "2") << endl;
      
    }
  }
  return 0;
}
