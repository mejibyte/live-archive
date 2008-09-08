#include <iostream>
#include <string>
using namespace std;

string v[15];

int main(){
  int n, Set = 1;
  while (cin >> n && n){
    for (int i=0; i<n; ++i) cin >> v[i];

    cout << "SET " << Set++ << endl;
    for (int i=0; i<n; i += 2) cout << v[i] << endl;
    for (int i=(n & 1 ? n-2 : n-1); i>=0; i -= 2) cout << v[i] << endl;
  }
  return 0;
}
