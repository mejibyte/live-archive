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

int ways[(1 << 15)+1][5];

int main(){
 vector<int> coins;
 for (int i=1; i*i < (1<<15); ++i){
   coins.push_back(i*i);
   //D(i*i);
 }

 int n = coins.size();
 //D(n);

 memset(ways, 0, sizeof ways);

 ways[0][0] = 1;
 for (int i=0; i<n; ++i){
   for (int j=coins[i]; j<=(1<<15); ++j){
     for (int k=1; k<=4; ++k){
       ways[j][k] += ways[j - coins[i]][k-1];
     }
   }
 }

 int x;
 while(cin >> x && x){
   cout << ways[x][1] + ways[x][2] + ways[x][3] + ways[x][4] << endl;
 }

 return 0;
}
