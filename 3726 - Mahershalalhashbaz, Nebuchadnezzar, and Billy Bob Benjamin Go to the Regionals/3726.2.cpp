/*
  Accepted.
 */
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

string w[1000];

bool comparar(const string &a, const string &b){
  return (a.size() < b.size());
}

int main(){
  int n, k, C=1;
  while (cin >> n >> k && n+k){
    for (int i=0; i<n; ++i){
      cin >> w[i];
    }

    sort(w, w+n, comparar);
    bool ok = true;
    for (int i=0; i<n && ok; i += k){
      int avg = 0;
      for (int j=i; j<i+k; ++j){
	avg += w[j].size();
      }
      avg /= k;
      for (int j=i; j<i+k; ++j){
	if (abs(int(w[j].size() - avg)) > 2){
	  ok = false;
	  break;
	}
      }
    }
    if (C > 1) cout << endl;
    cout << "Case " << C++ << ": " << (ok?"yes":"no") << endl;
  }
  return 0;
}
