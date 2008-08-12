#include <queue>
#include <iostream>
using namespace std;

char g[21][21];
int  d[21][21];

int di[] = { 0, 1, 0, -1};
int dj[] = {-1, 0, 1,  0};

int main(){
  int x;
  cin >> x;
  while(x--){
    int r,c;
    cin >> r >> c;
    for (int i=0; i<r; ++i){
      for (int j=0; j<c; ++j){
	cin >> g[i][j];
	d[i][j] = INT_MAX;
      }
    }
    
    queue<pair<int,int> > q;
    for (int j=0; j<c; ++j){
      d[0][j] = 1;
      q.push(make_pair(0, j));
    }

    while (!q.empty()){
      int i = q.front().first;
      int j = q.front().second;
      q.pop();
      for (int k=0; k<4; ++k){
	int ni = i + di[k];
	int nj = j + dj[k];
	if (0 <= ni && ni < r &&
	    0 <= nj && nj < c){
	  if (g[ni][nj] == g[i][j] && d[i][j] < d[ni][nj]){
	    d[ni][nj] = d[i][j];
	    q.push(make_pair(ni, nj));
	  }
	  if (g[ni][nj] != g[i][j] && d[i][j] + 1 < d[ni][nj]){
	    d[ni][nj] = d[i][j] + 1;
	    q.push(make_pair(ni, nj));
	  }
	}
      }
    }
    int mini = d[r-1][0];
    for (int j = 1; j<c; ++j){
     if (d[r-1][j] < mini)
       mini = d[r-1][j];
    }
    cout << mini << endl;
  }
  return 0;
}
