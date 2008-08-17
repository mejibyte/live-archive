#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

using namespace std;

int main(){
  int maxi, S=1;
  while (cin >> maxi && maxi > 0){
    int ans[maxi+1][maxi+1];
    memset(ans, 0, sizeof ans);

    char c;
    int dog, score;
    map<int, int> h_votes, w_votes;
    while (cin >> c >> dog >> score && c != 'E'){
      if (c == 'H'){
        //Puede un tipo votar dos veces por el mismo perro?
        h_votes[dog] = score;
      }else{
        w_votes[dog] = score;
      }
    }

    for (map<int,int>::iterator i = h_votes.begin(); i != h_votes.end(); ++i){
      if (w_votes.count(i->first)){ //ambos votaron por el mismo perro
        ans[i->second][w_votes[i->first]]++;
      }
    }

    cout << "Show " << S++ << ":" << endl;
    for (int i=0; i<=maxi; ++i){
      for (int j=0; j<=maxi; ++j){
        cout << ans[i][j] << (j < maxi ? " " : "\n");
      }
    }
    cout << endl;

  }
  return 0;
}
