#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <climits>

using namespace std;

int m[303][303], dp[303][303];

int main(){
  int r,c,seats;
  while(cin >> r >> c >> seats && (r | c | seats)){
    //memset(m, 0, sizeof(m));
    //memset(dp, 0, sizeof(dp));

    for (int i=1; i<=r; ++i)
      for (int j=1; j<=c; ++j){
	char d;
	cin >> d;
	m[i][j] = (d == '.' ? 1 : 0);
      
      }

  
    dp[1][1] = m[1][1];
    for (int i=1; i<=r; ++i)
      for (int j=1; j<=c; ++j)
	dp[i][j] = dp[i][j-1] + m[i][j] + dp[i-1][j] - dp[i-1][j-1];
 

    /*cerr << "m es:\n";
    for (int i=0; i<=r+1; ++i){
      for (int j=0; j<=c+1; ++j)
    	cerr << m[i][j] << " ";
      cerr << endl;
    }
    cerr << "\ndp es:\n";
    for (int i=0; i<=r+1; ++i){
      for (int j=0; j<=c+1; ++j)
    	cerr << dp[i][j] << " ";
      cerr << endl;
      }*/
    
    int mini = INT_MAX;
    for (int i=r; i>=1; --i)
      for (int j=c; j>=1; --j)
	for (int k=1; k<=i; ++k)
	  for (int l=1; l<=j; ++l){
	    int a = dp[i][j] - dp[i-k][j] - dp[i][j-l] + dp[i-k][j-l];
	    //cout << "(i,j)-(k,l)-a: ";
	    //printf("(%d,%d)-(%d,%d)-%d\n ", i, j, k, l, a);
	    if (a >= seats){
	      mini = min(mini, (k) * (l));
	    }
	  }
    cout << mini << endl;
	  
  } 
}
