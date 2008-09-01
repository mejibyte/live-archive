#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

int main(){
  int C=1;
  string s;
  while (cin >> s && s != "STOP"){
    int n;
    cin >> n;
    if (C > 1) printf("\n");
    printf("Dataset #%d:  The initial order is %s.\n", C++, s.c_str());
    while (n--){
      char c;
      cin >> c;
      int pos = s.find(c);
      string before, after;
      before = s.substr(0, pos);
      after = s.substr(pos+1, s.length());
      if (before.length() <= after.length()) reverse(before.begin(), before.end());
      else reverse(after.begin(), after.end());
      s = before + after;
      printf("After %c leaves, the order is %s.\n", c, s.c_str());
    }


  }
  return 0;
}
