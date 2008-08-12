#include <iostream>
#include <queue>
#include <cassert>
#include <stdio.h>

using namespace std;

char g[101][101];
int e[101][101], r, c;

int di[] = {-1, -1, 0, 1,  1,  0};
int dj[] = { 0,  1, 1, 0, -1, -1};

const int FREE = 0x0000;
const int CW = 0x0001;
const int CCW = 0x0002;


int main(){
  while (cin >> r >> c && (r | c)){
    for (int i=0; i<r; ++i){
      for (int j=0; j<c; ++j){
	cin >> g[i][j];
	//assert(g[i][j] == '.' || g[i][j] == '*' || g[i][j] == 'I');
	e[i][j] = FREE;
      }
    }

    queue<pair<int,int> > q;
    for (int i=0; i<r; ++i){
      for (int j=0; j<c; ++j){
	if (g[i][j] == 'I'){
	  e[i][j] = CW;
	  q.push(make_pair(i,j));
	}
      }
    }

    while (!q.empty()){
      int i =q.front().first;
      int j =q.front().second;
      
      q.pop();
      
      for (int k=0; k<6; ++k){
	int ni = i + di[k];
	int nj = j + dj[k];
	if (0 <= ni && ni < r &&
	    0 <= nj && nj < c &&
	    g[ni][nj] != '.'){
	  if (e[i][j] & CW){
	    if (e[ni][nj] != (e[ni][nj] | CCW)){
	      e[ni][nj] |= CCW;
	      q.push(make_pair(ni, nj));
	    }
	  }
	  if (e[i][j] & CCW){
	    if (e[ni][nj] != (e[ni][nj] | CW)){
	      e[ni][nj] |= CW;
	      q.push(make_pair(ni, nj));
	    }
	  }
	}
      }
    }

    printf("\n");
    for (int i=0; i<r; ++i){
      for (int j=0; j<c; ++j){
	if (g[i][j] == '.')
	  printf(".");
	else if (e[i][j] == FREE)
	  printf("F");
	else if (e[i][j] == CW)
	  printf("(");
	else if (e[i][j] == CCW)
	  printf(")");
	else if (e[i][j] == (CW | CCW))
	  printf("B");
      }
      printf("\n");
    }

  }
  return 0;
}
