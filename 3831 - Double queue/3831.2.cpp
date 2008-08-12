/*
  Problem: 3831 - Double queue (ACM-ICPC Live archive)

  Andrés Mejía-Posada

  Accepted, a little faster
 */
#include <iostream>
#include <set>
#include <stdio.h>


using namespace std;

int main(){
  int x, k, p;
  set<pair<int, int> > q; //first - priority, second - client
  while (scanf("%d", &x) == 1 && x){
    if ((x == 2 || x == 3) && q.size() == 0){
      puts("0");
    }else if (x == 1){
      scanf("%d %d", &k, &p);
      q.insert(make_pair(p, k));
    }else if (x == 2){
      set<pair<int, int> >::iterator i = q.end();
      --i;
      printf("%d\n", i->second);
      q.erase(i);
    }else if (x == 3){
      set<pair<int, int> >::iterator i = q.begin();
      printf("%d\n", i->second);
      q.erase(i);
    }else while (true) puts("error");
  }
  return 0;
}
