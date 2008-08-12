#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
  int a,d;
  cin >> a >> d;
  while (a + d){
    vector<int> b(a);
    vector<int> c(d);
    for (int i=0; i<a; i++){
      cin >> b[i];
    }
    for (int i=0; i<d; i++){
      cin >> c[i];
    }
    sort(c.begin(), c.end());
    sort(b.begin(), b.end());
    if (b[0] < c[1]) cout << "Y\n";
    else cout << "N\n";
    cin >> a >> d;
    
  }
  return 0;
}
