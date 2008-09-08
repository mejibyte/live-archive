#include <iostream>
using namespace std;

int main(){
  int n;
  while (cin >> n && n != -1){
    long long ans = 0;
    int prev = 0;
    for (int i=0; i<n; ++i){
      int speed, elapsed;
      cin >> speed >> elapsed;
      ans += speed * (elapsed - prev);
      prev = elapsed;
    }
    cout << ans << " miles" << endl;
  }
  return 0;
}
