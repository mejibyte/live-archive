#include <map>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

int dist(string &s, string &t){
  map<char, int> m;
  sort(s.begin(), s.end());
  sort(t.begin(), t.end());
  for (char c = 'a'; c <= 'z'; ++c){
    m[c] = 0;
  }
  for (int i=0; i<s.size(); ++i){
    m[s[i]]++;
  }
  for (int i=0; i<t.size(); ++i){
    m[t[i]]--;
  }
  int r = 0;
  for (char c = 'a'; c <= 'z'; ++c){
    //if (m[c] != 0) cout << c << " aparece " << m[c] << " veces\n";
    r += abs(m[c]);
  }
  return r;
}

int main(){
  int n;
  string s,t;
  cin >> n;
  getline(cin, s);
  int k = 1;
  while (n--){
    getline(cin, s);
    getline(cin, t);
    cout << "Case #" << k++ << ":  " << dist(s, t) << endl;
  }
}
