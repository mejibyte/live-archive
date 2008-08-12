#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <climits>

#define MIN(a,b) ((a)<(b)?(a):(b))

using namespace std;

int m[303][303], dp[303];

const int infinity = 100000;

inline int dist(int arr[], const int &n, const int &k){

  int curr = 0, best = infinity;
  int i, j;
  i = j = 0;
  for (j=0; j<n; ++j){
    while (arr[i] == 0 && i++ < n);

    if (i == n) break;
    if (i > j){
      j = i;
    }
    curr += arr[j];
    while (curr >= k){
      best = MIN(best, j-i);
      curr -= arr[i++];
    }
  }
  return (best+1);
}



int main(){
  int r,c,seats;

  while(cin >> r >> c >> seats && (r | c | seats)){
    
    
    for (int i=1; i<=r; ++i){
      for (int j=1; j<=c; ++j){
	char d;
	cin >> d;
	m[i][j] = (d == '.' ? 1 : 0);
      }
    } 
    

    int minArea = 1000000000;
    for (int i=1; i<=r; ++i){
      
      for (int k=1; k<= c; ++k){
	dp[k] = m[i][k];
      }

      /*cout << "arr es: ";
      for (int k=1; k<= c; ++k){
	cout << arr[k] << " ";
      }
      cout << endl;*/
      minArea = MIN(minArea, dist(dp+1, c, seats)); //Si la fila tiene suficientes sillas...
      //      cout << "minArea es: " << minArea << endl;
      for (int j=i+1; j<=r; ++j){

	for (int k=1; k<=c; ++k){
	  dp[k] += m[j][k];
	}

	minArea = MIN(minArea, (j-i+1)*dist(dp+1, c, seats));
      }
    }
    cout << minArea << endl;
  }
  return 0;
}
