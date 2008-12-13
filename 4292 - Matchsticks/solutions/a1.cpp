/*
  [NWERC'08] MOBILE
  by: Jan Kuipers
*/

using namespace std;

#include <iostream>
#include <map>

int main () {

  int runs;
  cin>>runs;

  while (runs--) {

    string s;
    cin>>s;

    int open=0, maxcnt=0, totalcnt=0;
    map<long long,int> cnt;

    for (int i=0; i<s.size();) {
      switch (s[i]) {
      case '[': i++; open++; break;
      case ']': i++; open--; break;
      case ',': i++; break;
      default:
	long long x=0;
	while (i<s.size() && isdigit(s[i])) x=10*x+s[i++]-'0';
	maxcnt >?= ++cnt[x<<open];
	totalcnt++;
      }
    }

    cout << totalcnt-maxcnt << endl;
  }

  return 0;
}
