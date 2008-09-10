/*
  Accepted
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
map<state, char> action;

inline state encode(int m, int n, int t){ return m*10000000+n*10000+t; }

inline void decode(state mask, int &m, int &n, int &t)
{ t = mask % 10000; n = (mask % 10000000) / 10000;  m = (mask / 10000000); }

/*
  option = 0 si no se movio ningun reloj, 1 si se movio M, 2 si se movio N, 3 si se movio N,M
 */
void enqueue(state prev, int m, int n, int t, int option = 0){
  if (t > T) return;
  state u = encode(m, n, t);
  if (visited.count(u) > 0) return;
  if (previous.count(u) > 0) return;

  previous[u] = prev;
  action[u] = option;
  if (option == 0) q.push_front(u);
  else q.push_back(u);
}

void bfs(){
  previous.clear();
  action.clear();
  visited.clear();
  q.clear();

  state initial = encode(M, N, 0);
  previous[initial] = -1;
  action[initial] = 3;


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

    if (t == T && (m == 0 || n == 0)){
      //Print answer
      string ans = "----------\n";

      // vector<state> path(1, u);

      for (state p = previous[u]; u != -1; p = previous[u = p]){


//         path.insert(path.begin(), u);


        int option = action[u];
        decode(u, m, n, t);
        buf[0] = '\0';
        if (option == 1) sprintf(buf, "%d: %d\n", t, M);
        if (option == 2) sprintf(buf, "%d: %d\n", t, N);
        if (option == 3) sprintf(buf, "%d: %d,%d\n", t, M, N);
        ans = string(buf) + ans;
      }

//       cout << "path es: " << endl;
//       for (int i=0; i<path.size(); ++i){
//         decode(path[i], m, n, t);
//         printf("%d %d %d, previous[path[i]] = %d, action[path[i]] = %d\n", m, n, t, previous[path[i]], action[path[i]]);
//       }

      printf("%s", ans.c_str());
      return;
    }

    if (m != 0 && n != 0){
      int z = m < n ? m : n;
      enqueue(u, m-z, n-z, t+z);
    }else if (m == 0 && n == 0){
      enqueue(u, M, 0, t, 1);
      enqueue(u, 0, N, t, 2);
      enqueue(u, M, N, t, 3);
    }else if (m == 0){
      enqueue(u, M, n, t, 1);
      enqueue(u, 0, N-n, t, 2);
      enqueue(u, M, N-n, t, 3);
      enqueue(u, 0, 0, t+n);
    }else{
      enqueue(u, m, N, t, 2);
      enqueue(u, M-m, 0, t, 1);
      enqueue(u, M-m, N, t, 3);
      enqueue(u, 0, 0, t+m);
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
