/*
  Accepted en el Live Archive.
  Wrong Answer en TJU y en PKU.
 */
#include <deque>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <iterator>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int M, N, T;
char buf[32];

typedef int state;

deque<state> q;
set<state> visited;
map<state, state> previous;
map<state, char> action; //Tells me what flip I did to reach state "first"

enum {None, Left, Right, Both}; //Possible flips

inline state encode(int m, int n, int t){ return m*10000000+n*10000+t; } //Encodes the state into a single integer

inline void decode(state mask, int &m, int &n, int &t)
{ t = mask % 10000; n = (mask % 10000000) / 10000;  m = (mask / 10000000); }


void enqueue(state prev, int m, int n, int t, int option = None){
  if (t > T) return;
  state u = encode(m, n, t);
  if (visited.count(u) > 0) return;

  previous[u] = prev;
  action[u] = option;
  if (option == None) q.push_front(u);
  else q.push_back(u);
}

void bfs(){
  previous.clear(), action.clear(), visited.clear(), q.clear();

  state initial = encode(M, N, 0);
  previous[initial] = -1, action[initial] = Both;
  q.push_front(initial);
  while (q.size()){
    state u = q.front();
    q.pop_front();

    //cout << "popped " << u << endl;

    if (visited.count(u)) continue;

    visited.insert(u);
    int m, n, t;
    decode(u, m, n, t);

    if (t > T) continue;

    if (t == T && (m == 0 || n == 0)){ //Print answer
      string ans = "----------\n";
      for (state p = previous[u]; u != -1; p = previous[u = p]){
        int option = action[u];
        decode(u, m, n, t);
        buf[0] = '\0';
        if (option == Left) sprintf(buf, "%d: %d\n", t, M);
        if (option == Right) sprintf(buf, "%d: %d\n", t, N);
        if (option == Both) sprintf(buf, "%d: %d,%d\n", t, M, N);
        ans = string(buf) + ans;
      }
      printf("%s", ans.c_str());
      return;
    }

    //Try to reach possible states
    if (m != 0 && n != 0){
      int z = m < n ? m : n;
      enqueue(u, m-z, n-z, t+z);
    }else if (m == 0 && n == 0){
      enqueue(u, M, N, t, Both);
      enqueue(u, M, 0, t, Left);
      enqueue(u, 0, N, t, Right);
    }else if (m == 0){
      enqueue(u, M, n, t, Left);
      enqueue(u, M, N-n, t, Both);
      enqueue(u, 0, 0, t+n);
      enqueue(u, 0, N-n, t, Right);
    }else{
      enqueue(u, m, N, t, Right);
      enqueue(u, M-m, N, t, Both);
      enqueue(u, 0, 0, t+m);
      enqueue(u, M-m, 0, t, Left);
    }
  }
  printf("Impossible!\n----------\n");
}

int main(){
  while (scanf("%d %d %d", &M, &N, &T) == 3 && (M+N+T)){
    bfs();
  }
  return 0;
}
