/*
  Accepted.

  Idea: http://forums.topcoder.com/?module=Thread&threadID=627088&start=0
*/

using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>

#define D(x) cout << #x " is " << x << endl

int n;
vector<int> deck;
deque<int> sorted_deck;

bool conflict[208][208];
vector<int> min_until;

int color[208];

/*
  Use DFS to bicolor the graph of conflicts.
*/
bool shoot(int u, int c){
 if (color[u]) return color[u] == c;

 color[u] = c;
 for (int v=0; v<n; ++v)
   if (conflict[u][v]){
     if (!shoot(v, 3 - c)) return false;
   }
 return true;
}

int main(){
 int caso = 1;
 while (scanf("%d", &n)==1 && n){
   deck.clear(), sorted_deck.clear();

   for (int i=0, x; i<n && scanf("%d", &x)==1; ++i){
     deck.push_back(x), sorted_deck.push_back(x);
   }

   sort(sorted_deck.begin(), sorted_deck.end());

   min_until.resize(n);
   min_until[0] = deck[0];
   for (int i=1; i<n; ++i){
     min_until[i] = min(min_until[i-1], deck[i]);
   }



   memset(conflict, 0, sizeof conflict);
   for (int i=0; i<n; ++i){
     for (int j=i-1; j >= 1; --j){
       if (deck[i] < deck[j] && min_until[j-1] < deck[i]){
         conflict[i][j] = conflict[j][i] = true;
       }
     }
   }

   bool ok = true;
   memset(color, 0, sizeof color);
   for (int i=0; i<n; ++i){
     if (!color[i] && !shoot(i, 1)){
       ok = false;
       break;
     }
   }

   printf("#%d\n", caso++);
   if (!ok){
     printf("impossible\n");
   }else{
     stack<int> s[3];

     s[1].push(INT_MAX);
     s[2].push(INT_MAX);

     for (int i=n-1; i>=0; --i){
       s[color[i]].push(deck[i]);
       printf("push %d\n", color[i]);

       while (s[1].top() == sorted_deck.front() || s[2].top() == sorted_deck.front()){
         for (int k=1; k<=2; ++k){
           if (s[k].top() == sorted_deck.front()){
             printf("pop %d\n", k);
             s[k].pop();
             sorted_deck.pop_front();
             break;
           }
         }
       }
     }
   }
 }
 return 0;
}


