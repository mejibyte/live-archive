#include <iostream>
#include <set>
#include <queue>
#include <string.h>

using namespace std;

struct state{
  bool board[8][8];
  int horse_row, horse_col;
  state(){
    memset(board, 0, sizeof board);
  }
  state * operator = (const state &that){
    for (int i=0; i<8; ++i) for (int j=0; j<8; ++j)
                              board[i][j] = that.board[i][j];
    horse_row = that.horse_row;
    horse_col = that.horse_col;
  }
  bool operator == (const state &that) const{
    for (int i=0; i<8; ++i) for (int j=0; j<8; ++j)
                              if (board[i][j] != that.board[i][j]) return false;
    return (horse_row == that.horse_row && horse_col == that.horse_col);
  }
  bool operator < (const state &that) const{
    for (int i=0; i<8; ++i) for (int j=0; j<8; ++j){
        if (board[i][j] != that.board[i][j]){
          return (board[i][j] == 0);
        }
      }

    return (horse_row < that.horse_row || (horse_row == that.horse_row && horse_col < that.horse_col));

  }
};

bool ganador(const state &s){
  for (int i=0; i<8; ++i) for (int j=0; j<8; ++j)
                            if (s.board[i][j]) return false;
  return true;
}

bool perdedor(const state &s){
  for (int j=0; j<8; ++j)
    if (s.board[7][j]) return true;
  return false;
}

int di[] = {-1, -1, +1, +1, -2, -2, +2, +2};
int dj[] = {-2, +2, -2, +2, +1, -1, +1, -1};

void bfs(const state &initial){
  set<state> visited;
  queue<pair<int, state> > q;
  q.push(make_pair(0, initial));
  while (q.size()){
    state u = q.front().second;
    int w = q.front().first;

    q.pop();

    if (ganador(u)){
      cout << w << endl;
      return;
    }

    if (visited.count(u)) continue;
    visited.insert(u);

    for (int k=0; k<8; ++k){
      state v = u;
      v.horse_row += di[k];
      v.horse_col += dj[k];

      if (0 <= v.horse_row && v.horse_row < 8 && 0 <= v.horse_col && v.horse_col < 8){
        v.board[v.horse_row][v.horse_col] = false; //Eat

        if (!perdedor(v)){ //Algun peón todavía puede moverse
          for (int i=7; i>0; --i)
            for (int j=0; j<8; ++j)
              if (!v.board[i][j] && v.board[i-1][j]){
                swap(v.board[i-1][j], v.board[i][j]);
              }

          if (visited.count(v) == 0){
            q.push(make_pair(w+1, v));
          }
        }
      }
    }
  }
  cout << "impossible" << endl;
}
int main(){
  int p;
  while (cin >> p && p){
    state initial;
    for (int i=0; i<p; ++i){
      int pawn;
      cin >> pawn;
      pawn--;
      initial.board[pawn/8][pawn%8] = true;
    }
    int horse;
    cin >> horse;
    horse--;
    initial.horse_row = horse/8;
    initial.horse_col = horse%8;
    bfs(initial);

  }
  return 0;
}
