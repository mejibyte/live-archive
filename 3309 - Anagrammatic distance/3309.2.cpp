#include <map>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

int m[26];

inline int dist(string &s, string &t){
  sort(s.begin(), s.end());
  sort(t.begin(), t.end());
  for (char c = 0; c < 26; ++c){
    m[c] = 0;
  }
  int n = s.size();
  for (int i=0; i<n; ++i){
    m[s[i]-'a']++;
  }
  n = t.size();
  for (int i=0; i<n; ++i){
    m[t[i]-'a']--;
  }
  int r = 0;
  for (char c = 0; c < 26; ++c){
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
