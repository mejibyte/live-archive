/*
  Time limit exceeded
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define V(x) copy(x.begin(), x.end(), ostream_iterator<int>(cout, " ")); cout << endl
using namespace std;

int N, M, S;

typedef vector<vector<char> > matrix;
matrix a,b,c,d;

void dilation(matrix &a, matrix &b, matrix &c){
  for (int i=1; i<=M; ++i) for (int j=1; j<=N; ++j) c[i][j] = '.';
  for (int ia=1; ia<=M; ++ia){
    for (int ja=1; ja<=N; ++ja){
      if (a[ia][ja] == '*'){
        for (int ib=-S; ib<=S; ++ib){
          for (int jb=-S; jb<=S; ++jb){
            if (b[ib+S+1][jb+S+1] == '*'){
              int ic = ia + ib, jc = ja + jb;
              if (1 <= ic && ic <= M && 1 <= jc && jc <= N){
                c[ic][jc] = '*';
              }
            }
          }
        }
      }
    }
  }
}

void erosion(matrix &a, matrix &b, matrix &c){
  for (int i=1; i<=M; ++i) for (int j=1; j<=N; ++j) c[i][j] = '.';
  for (int ic=1; ic<=M; ++ic){
    for (int jc=1; jc<=N; ++jc){
      bool valid = true;
      for (int ib=-S; ib<=S; ++ib){
        for (int jb=-S; jb<=S; ++jb){
          //printf("ib=%d, jb=%d, s=%d, b=%d\n", ib, jb, S, b);
          if (b[ib+S+1][jb+S+1] == '*'){
            int ia = ic + ib, ja = jc + jb;
            if (1 > ia || ia > M || 1 > ja || ja > N || a[ia][ja] != '*'){
              valid = false;
              ib = S+1; //Break both 2 inner-loops
              jb = S+1;
            }
          }
        }
      }
      if (valid) c[ic][jc] = '*';
    }
  }
}

void print(matrix &d){
  for (int i=1; i<=M; ++i){
    for (int j=1; j<=N; ++j){
      cout << d[i][j];
    }
    cout << endl;
  }
}

int main(){
  int run = 1;
  a = vector<vector<char> >(512, vector<char>(512));
  b = vector<vector<char> >(512, vector<char>(512));
  c = vector<vector<char> >(512, vector<char>(512));
  d = vector<vector<char> >(512, vector<char>(512));
  while (cin >> M >> N >> S && (N+M+S)){
    if (run > 1){ for (int i=0; i<75; ++i) cout << "="; cout << endl; }
    for (int i=1; i<=M; ++i) for (int j=1; j<=N; ++j) cin >> a[i][j];
    for (int i=1; i<=2*S+1; ++i) for (int j=1; j<=2*S+1; ++j) cin >> b[i][j];

    cout << "Case " << run++ << endl << endl;
    erosion(a,b,c);
    dilation(c,b,d);
    print(d);

    cout << endl;

    dilation(a,b,c);
    erosion(c,b,d);
    print(d);
  }
  return 0;
}

