/*
  Problem: 3930 - Drop the Triples
  Author: Andrés Mejía-Posada

  Version 4 but cleaner
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

int ans, n;
map<int, int> memo;

#define bit(i, n) ((1 << i) & n)

/*
  Returns the maximum amount of common triples that can be formed using the 
  cards set on bitwise mask avail.
 */
int best(int avail, const vector<int> &x){
  /*
    X must be sorted in non-decreasing order! (x0 <= x1 <= x2 <= ...)
   */
  map<int, int>::iterator z = memo.find(avail);
  if (z != memo.end()) return z->second;
  int ans = 0;
  for (int i=0; i<n; ++i)
    if (bit(i, avail))
      for (int j=i+1; j<n; ++j)
	if (bit(j, avail))
	  for (int k=0; k<i; ++k)
	    if (bit(k, avail))
	      if (x[k] + x[i] > x[j]){
		int mask = avail & ~(1 << i) & ~(1 << j) & ~(1 << k);
		int t = 1 + best(mask, x);
		if (t > ans) ans = t;
		break;
	      }
			 
  return memo[avail] = ans;
 
}

int common(const vector<int> &x){
  n = x.size();
  memo.clear();
  return best( (1 << n) - 1, x );
}


int main(){
  int n;
  while(cin>>n &&n){
    vector<int> a(14, 0), b(14, 0);
    for (int i=0; i<n; ++i){
      int x;
      cin >> x;
      if (i%2) b[x]++;
      else a[x]++;
    }
    /*
      Perfect triples number
     */
    int pa = 0, pb = 0;
    for (int i=1; i<=13; ++i){
      pa += a[i] / 3, a[i] %= 3;
      pb += b[i] / 3, b[i] %= 3;
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

      /*
	Common triples number
       */
      ca = common(xa), cb = common(xb);
      if (ca == cb) cout << "0\n";
      else cout << (ca > cb ? "1" : "2") << endl;
      
    }
  }
  return 0;
}

