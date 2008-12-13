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

#define D(x) cout << #x " es " << x << endl

int dp[100010][2];
int best_row[100010];

int main(){
    //freopen("candy.in", "r", stdin);
    int rows, cols;
    while (cin >> rows >> cols && rows && cols){
       for (int i=0; i<rows; ++i){
           int x;
           cin >> x;
           dp[0][1] = x;
           dp[0][0] = 0;
           for (int j=1; j<cols; ++j){
               cin >> x;
               dp[j][1] = max(dp[j-1][0] + x, dp[j-1][1]);
               dp[j][0] = max(dp[j-1][1], dp[j-1][0]);
           }
           best_row[i] = max(dp[cols-1][0], dp[cols-1][1]);
       }
       
       dp[0][1] = best_row[0];
       dp[0][0] = 0;
       for (int i=1; i<rows; ++i){
           dp[i][1] = max(dp[i-1][0] + best_row[i], dp[i-1][1]);
           dp[i][0] = max(dp[i-1][1], dp[i-1][0]);
       }
       int ans = max(dp[rows-1][1], dp[rows-1][0]);
       cout << ans << endl;
    }
    
    return 0;
}
