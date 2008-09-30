/*
  Problem: 3930 - Drop the Triples
  Author: Andrés Mejía-Posada

  Wrong Answe
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

int common(vector<int> x){
  //V(x);
  int n = x.size();
  if (n < 3) return 0;
  int r = 0;
  bool erased = false;
  for (int i=0; i+2<n; ){
    if (x[i] + x[i+1] > x[i+2]){
      x.erase(x.begin()+i, x.begin()+i+3);
      r++;
      n -= 3;
      erased = true;
    }
    else ++i;
  }
  return r + (erased ? common(x) : 0);
  
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
