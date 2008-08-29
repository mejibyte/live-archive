#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct pos{
  int i, j;
};

struct state{
  pos me;
  int w;
  vector<pos> robots;
};

vector<string> g;

int main(){
  int rows, cols;
  while (cin >> cols >> rows && cols >= 3 && rows >= 3){
    string s;
    getline(cin, s);
    g = vector<string>(rows);
    for (int i=0; i<rows; ++i){
      getline(cin, g[i]);
    }

  }

  return 0;
}
