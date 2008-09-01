#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

vector<string> board;

typedef vector<vector<int> > matrix;

bool compare(const matrix &a, const matrix &b){
  set<int> _a, _b;
  for (int i=0; i<5; ++i){
    for (int j=0; j<5; ++j){
      if (board[i][j] == 'X'){
        _a.insert(a[i][j]);
        _b.insert(b[i][j]);
      }
    }
  }
  return _a == _b;
}

int main(){
  int C=1;
  for(;;){
    board = vector<string>(5);
    for (int i=0; i<5; ++i){
      cin >> board[i];
    }
    int n;
    cin >> n;
    if (!n) break;

    set<int> numbers[n];
    vector<matrix> cards(n);
    for (int i=0; i<n; ++i){
      for (int j=0; j<5; ++j){
        cards[i].push_back(vector<int>());
        for (int k=0; k<5; ++k){
          int x; cin >> x;
          cards[i][j].push_back(x);
          if (board[j][k] == 'X') numbers[i].insert(x);
        }
      }
    }

    if (C > 1) cout << endl;
    cout << "Game " << C++ << endl;
    for (int i=1; i<n; ++i){
      for (int j=0; j<i; ++j){
        if (numbers[i] == numbers[j]){
          cout << "Card " << i + 1 << " is equivalent to card " << j+1 << endl;
          break;
        }
      }
    }

  }
  return 0;
}

