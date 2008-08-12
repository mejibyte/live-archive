#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(){
  int n;
  cin >> n;
  while (n--){
    string s;
    cin >> s;
    int a[4];
    for (int i=0; i<4; i++){
      a[i] = 0;
      string t = s.substr(8*i, 8);
      reverse(t.begin(), t.end());
      for (int j=0; j<8; ++j){
        a[i] += (t[j] == '1'?(1<<j):0);
      }
    }
    for (int i=0; i<3; ++i){
      cout << a[i] << ".";
    }
    cout << a[3] << endl;
  }
  return 0;
}
