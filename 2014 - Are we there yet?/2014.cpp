#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(){
  int cookie;
  bool first = true;
  while (cin >> cookie && cookie < 5280){
    if (!first) puts("");
    first = false;
    string line;
    getline(cin, line);
    stringstream sin(line);

    int prev = 0, next;
    while (sin >> next){
      printf("Moving from %d to %d: ", prev, next);
      if (next == cookie){
        puts("found it!");
      }
      else{
        int dif = abs(prev-cookie) - abs(next-cookie);
        if (dif < 0) puts("colder.");
        else if (dif > 0) puts("warmer.");
        else puts("same.");
      }
      prev = next;
    }
  }
  return 0;
}
