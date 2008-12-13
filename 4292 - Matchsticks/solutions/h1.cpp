/*
  [NWERC'08] MATCHSTICKS
  by: Jan Kuipers
*/

using namespace std;

#include <iostream>
#include <vector>

const int digits[10] = { 6,2,5,5,4,5,6,3,7,6 };

int main () {

  vector<int> best(22,INT_MAX);
  for (int i=1; i<1000; i++) {
    int j=i, x=0;
    while (j) x+=digits[j%10], j/=10;
    best[x] <?= i;
  }
  
  int runs;
  cin>>runs;
  while (runs--) {
    int n;
    cin>>n;
    
    if (n<21)
      cout<<best[n];
    else {
      int x = n%7+14;
      cout<<best[x]<<string((n-x)/7,'8');
    }
    
    cout<<" "<<(n%2==1?7:1)<<string(n/2-1,'1')<<endl;
  }
  return 0;   
}
