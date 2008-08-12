#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <map>
#include <algorithm>

using namespace std;

char vowels[] = {'a', 'e', 'i', 'o', 'u'};

struct p{
  char c;
  int f;
  bool operator < (const p &that) const {
    return (f > that.f || (f == that.f && c < that.c));
  }
};

int main(){
  string s;
  while (getline(cin, s) && s != "#"){
    map<char, int> d;
    for (int i=0; i<s.size(); ++i){
      s[i] = tolower(s[i]);
      for (int j=0; j<5; ++j){
        if (s[i] == vowels[j]){
          d[s[i]]++;
          break;
        }
      }
    }
    p answer[5];
    for (int i=0; i<5; ++i){
      answer[i].c = vowels[i];
      answer[i].f = d[vowels[i]];
    }
    sort(answer, answer+5);
    for (int i=0; i<5; ++i){
      cout << answer[i].c << ":" << answer[i].f << (i < 4 ? " " : ".\n");
    }

  }
  return 0;
}
