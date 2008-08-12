#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <climits>

#define MIN(a,b) ((a)<(b)?(a):(b))

using namespace std;

int m[303][303], dp[303];

const long long infinity = 100000;

long long dist(int arr[], const int &n, const int &k){

  long long curr = 0;
  int i, j, minI, minJ;
  i = j = minI = 0;
  minJ = infinity;
  for (j=0; j<n; ++j){
    while (arr[i] == 0 && i++ < n);
    if (i == n) break;
    if (i > j){
      j = i;
    }
    curr += arr[j];
    while (curr >= k){
      if (j - i < minJ - minI){
	minJ = j; minI = i;
      }
      curr -= arr[i++];
    }
  }

  //cout << "La subsecuencia más corta que sume al menos " << k << " va desde " << minI << " hasta " << minJ << endl;
  if (minJ == infinity) return infinity;
  return (minJ - minI + 1);
  }

/*long long dist(int a[], const int &n, const int &k){
  long long best = infinity;
  int i = 0, sum = 0;
  for (int j = 0; j < n; j++) {
    sum += a[j];
    while (i < j && sum-a[i] >= k) {
      sum -= a[i];
      i++;
    }
    if (sum >= k) best = MIN(best, j-i+1);
  } 
  return best;
  }*/

int main(){
  int r,c,seats;

  /*  int n, k, z[100];
  cin >> n >> k;
  for (int i=0; i<n; ++i){
    cin >> z[i];
  }
  dist(z, n, k);
  */

  while(cin >> r >> c >> seats && (r | c | seats)){
    
    
    for (int i=1; i<=r; ++i){
      for (int j=1; j<=c; ++j){
	char d;
	cin >> d;
	m[i][j] = (d == '.' ? 1 : 0);
      }
    } 
    
    /*   for (int i=1; i<=r; ++i){
      for (int j=1; j<=c; ++j){
	cout << m[i][j] << " ";
      }
      cout << endl;
    
      dist(m[i], c, seats);
      }*/

    long long minArea = 1000000000;
    for (int i=1; i<=r; ++i){
      //copy(m[i], m[i] + c, arr);

      for (int k=1; k<= c; ++k){
	dp[k] = m[i][k];
      }

      /*cout << "arr es: ";
      for (int k=1; k<= c; ++k){
	cout << arr[k] << " ";
      }
      cout << endl;*/
      minArea = min(minArea, dist(dp+1, c, seats)); //Si la fila tiene suficientes sillas...
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
