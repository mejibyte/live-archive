/*
  team6
  maquina 27
*/

#include<iostream>
#include<stdio.h>
#include<math.h>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
#include<stdlib.h>
#include<assert.h>
#include<sstream>
#include<stack>
#include<queue>
using namespace std;

#define D(x) cout << #x " es " << x << endl;

struct lectura{
   int dias, watts;
};

bool isLeap(int y){ return ((y % 400 == 0) || (y%4 == 0 && y%100!=0)); }

int dameDias(int d, int m, int y){
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeap(y)) days[1]++;
    
    m--;
    int sum = 0;
    for (int i=0; i<m; ++i){
        sum += days[i];
    }
    
    for (int i=1899; i<y; ++i){
        sum += 365 + isLeap(i);
    }
    sum += d;
    return sum;
}

int main(){
    //freopen("electricity.in", "r", stdin);    
    int n;
    while (cin >> n && n){
       vector<lectura> v(n);
       for (int i=0; i<n; ++i){
          int d, m, y, c;
          cin >> d >> m >> y >> c;
          v[i].dias = dameDias(d, m, y);
          v[i].watts = c;       }
       
       int cnt = 0, sum = 0;
       for (int i=1; i<n; ++i){
           if (v[i-1].dias == v[i].dias - 1){
               cnt++;
               sum += v[i].watts - v[i-1].watts;
           }
       }
       
       cout << cnt << " " << sum << endl;
    }
    return 0;
}
