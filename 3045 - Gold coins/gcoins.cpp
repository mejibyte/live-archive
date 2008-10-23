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

//_for(i, a, b):  a <= i < b
#define _for(i, a, b) for (int i=a, _n = b; i<_n; ++i)
//_from(i, a, b): a > i >= b
#define _from(i, a, b) for (int i=a-1, _n = b; i>=_n; --i)

#define D(x) cout << #x " is " << x << endl

int sum[10001];

int main(){

 sum[0] = 0;
 for (int i=1, days=1; i<=10000; days++){
   int j = i+days;
   while (i<j && i <= 10000){
     sum[i] = sum[i-1] + days;
     ++i;
   }
 }

 int x;
 while (cin >> x && x)
   cout << x << " " << sum[x] << endl;

 return 0;
}

