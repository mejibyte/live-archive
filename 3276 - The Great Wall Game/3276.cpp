#include <vector>
#include <set>
#include <queue>
#include <iostream>

using namespace std;

typedef vector< vector<bool> > matrix;

int di[] = {-1, +1, +0, +0};
int dj[] = {+0, +0, -1, +1};

bool isSolution(const matrix &u, const int &n){
  for (int i=0; i<n; ++i){
    bool good = true;
    for (int j=0; j<n; ++j){
      good &= u[i][j];
    }
    if (good) return true;
  }

  for (int j=0; j<n; ++j){
    bool good = true;
    for (int i=0; i<n; ++i){
      good &= u[i][j];
    }
    if (good) return true;
  }
  //diagonals
  bool left = true, right = true; //left is \, right is /
  for (int i=0; i<n; ++i){
    left &= u[i][i];
    right &= u[i][n-i-1];
  }
  return (left || right);
}

int main(){
  int n, C = 1;
  while (scanf("%d", &n) == 1 && n){
    matrix s(n, vector<bool>(n, false));
    int x, y;
    for (int i=0; i<n; ++i){
      scanf("%d %d", &x, &y);
      s[--x][--y] = true;
    }

    int answer = -1;
    queue< pair< matrix, int > > q;
    q.push(make_pair(s, 0));
    set<matrix> visited;
    while (q.size()){
      //printf("q.size() = %d\n", q.size());
      matrix u = q.front().first;
      int w = q.front().second;
      q.pop();

      if (visited.count(u)) continue;

      visited.insert(u);
      if (isSolution(u, n)){
        answer = w;
        break;
      }

      for (int i=0; i<n; ++i){
        for (int j=0; j<n; ++j){
          if (u[i][j]){
            for (int k=0; k<4; ++k){
              int ni = i + di[k];
              int nj = j + dj[k];
              if (0 <= ni && ni < n && 0 <= nj && nj < n && u[ni][nj] == false){
                matrix v = u;
                v[i][j] = false;
                v[ni][nj] = true;
                if (visited.count(v) == 0){
                  q.push(make_pair(v, w+1));
                  //visited.insert(v);
                }
              }
            }
          }
        }
      }
    }
    printf("Board %d: %d moves required.\n\n", C++, answer);
  }
  return 0;
}
