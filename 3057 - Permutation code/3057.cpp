#include <iostream>
#include <cmath>
#include <climits>
#include <cassert>
#include <string>

#define V(x) cout << #x " is: "; copy(x.begin(), x.end(), ostream_iterator<int>(cout, " ")); cout << endl
#define D(x) cout << #x " is: " << x << endl

using namespace std;

int pos(char x, string s){
  for (int i=0; i<s.size(); ++i){
    if (x == s[i]) return i;
  }
  assert(false);
}

int main(){
  int x;
  while (cin >> x && x){
    string s, p, c;
    cin >> s >> p >> c;
    //D(s); D(p); D(c); D(x);
    int n = c.size();
    string m(n, '*');
    int d = ((int)(pow(n, 1.5) + x))%n;

    int i = pos(c[d], s);
    m[d] = p[i];

    int repetitions = 0;
    int j = (d+n-1)%n;
    while (repetitions < n-1){
      m[j] = p[(pos(c[j], s))^(pos(m[(j+1)%n], s))];

      j = (j+n-1)%n;
      repetitions++;
    }
    cout << m << endl;
  }
  return 0;
}
