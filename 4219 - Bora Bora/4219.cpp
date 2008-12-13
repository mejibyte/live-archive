/*
  Problem: 4219 - Bora Bora
  Author: Andrés Mejía-Posada
  (http://blogaritmo.factorcomun.org)

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

struct card{
  int rank;
  char suit;
  bool operator < (const card &that) const {
    if (rank != that.rank) return rank > that.rank;
    return suit > that.suit;
  }
};


int p, m, n, d;

int play(vector<vector<card> > &hands, stack<card> &discard, queue<card> &stock){
  d = (discard.top().rank == 12 ? -1 : 1);

  int turn = 0;
  //First thrown card to the discard pile
  bool jumpFirstPlayer = false;
  if (discard.top().rank != 12){
    const card &top = discard.top();
    if (top.rank == 7 || top.rank == 1 || top.rank == 11){
      if (top.rank == 7 || top.rank == 1){
        hands[turn].push_back(stock.front()), stock.pop();
        if (top.rank == 7){
          hands[turn].push_back(stock.front()), stock.pop();
        }
        sort(hands[turn].begin(), hands[turn].end());
      }
      jumpFirstPlayer = true;
    }
  }
  if (jumpFirstPlayer) turn = (turn + p + d) % p;


  while (true){
    //Start of turn.
    bool threwCard = false;
    sort(hands[turn].begin(), hands[turn].end());
    for (int i=0; i<hands[turn].size() && !threwCard; ++i){
      const card &a = hands[turn][i], &b = discard.top();
      if (a.rank == b.rank || a.suit == b.suit){
        discard.push(a);
        hands[turn].erase(hands[turn].begin() + i);
        threwCard = true;
      }
    }
    if (hands[turn].size() == 0) return turn + 1; //Ganó

    if (!threwCard){
      //Robo
      hands[turn].push_back(stock.front());
      stock.pop();
      const card &a = hands[turn].back(), &b = discard.top();
      if (a.rank == b.rank || a.suit == b.suit){
        discard.push(a);
        hands[turn].erase(hands[turn].end()-1);
        threwCard = true;
      }
      sort(hands[turn].begin(), hands[turn].end());
    }



    if (threwCard && discard.top().rank == 12) d *= -1;
    turn = (turn + p + d) % p;
    bool jumpNextPlayer = false;
    if (threwCard && discard.top().rank != 12){
      const card &top = discard.top();
      if (top.rank == 7 || top.rank == 1 || top.rank == 11){
        if (top.rank == 7 || top.rank == 1){
          hands[turn].push_back(stock.front()), stock.pop();
          if (top.rank == 7){
            hands[turn].push_back(stock.front()), stock.pop();
          }
          sort(hands[turn].begin(), hands[turn].end());
        }
        jumpNextPlayer = true;
      }
    }

    if (jumpNextPlayer) turn = (turn + p + d) % p;

  }

}
  /*
    Orden del turno:
    Intentar tirar.
    Robar si no tiró.
    Intentar tirar si robó.

    Aumentar turno.
    Si tiró, aplicar efecto al próximo turno.

    Aumentar una unidad adicional si la carta tirada lo requiere.
   */



int main(){
  while (cin >> p >> m >> n && p && m && n){
    vector<vector<card> > hands(p, vector<card>(m));

    for (int i=0; i<p; ++i){
      for (int j=0; j<m; ++j){
        cin >> hands[i][j].rank >> hands[i][j].suit;
      }
      sort(hands[i].begin(), hands[i].end());
    }

    stack<card> discard;
    card c; cin >> c.rank >> c.suit;
    discard.push(c);

    queue<card> stock;
    for (int i=p*m+1; i<n; ++i){
      cin >> c.rank >> c.suit;
      stock.push(c);
    }
    cout << play(hands, discard, stock) << endl;
  }
  return 0;
}
