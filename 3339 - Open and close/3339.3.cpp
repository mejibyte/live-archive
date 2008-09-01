/*
  Accepted, a little faster (5.5 seconds of 10 allowed)
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

using namespace std;

int N, M, S;

char  a[300][300], b[300][300], c[300][300], d[300][300];

void dilation(char a[][300], char b[][300], char c[][300]){
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

void erosion(char a[][300], char b[][300], char c[][300]){
  for (int i=1; i<=M; ++i) for (int j=1; j<=N; ++j) c[i][j] = '.';
  for (int ic=1; ic<=M; ++ic){
    for (int jc=1; jc<=N; ++jc){
      bool valid = true;
      for (int ib=-S; ib<=S; ++ib){
        for (int jb=-S; jb<=S; ++jb){
          if (b[ib+S+1][jb+S+1] == '*'){
            int ia = ic + ib, ja = jc + jb;
            if (1 > ia || ia > M || 1 > ja || ja > N || a[ia][ja] != '*'){
              valid = false;
              ib = S+1; //Break both loops
              jb = S+1;
            }
          }
        }
      }
      if (valid) c[ic][jc] = '*';
    }
  }
}

void print(char d[][300]){
  for (int i=1; i<=M; ++i){
    for (int j=1; j<=N; ++j){
      putchar(d[i][j]);
    }
    putchar('\n');
  }
}

int main(){
  int run = 1;
  while (scanf("%d %d %d", &M, &N, &S) && (N+M+S)){
    if (run > 1) puts("===========================================================================");
    getchar(); //\n
    for (int i=1; i<=M; ++i){
      for (int j=1; j<=N; ++j) a[i][j] = getchar();
      getchar(); //\n
    }
    for (int i=1; i<=2*S+1; ++i){
      for (int j=1; j<=2*S+1; ++j) b[i][j] = getchar();
      getchar(); //\n
    }

    printf("Case %d\n\n", run++);
    erosion(a,b,c);
    dilation(c,b,d);
    print(d);

    putchar('\n');

    dilation(a,b,c);
    erosion(c,b,d);
    print(d);
  }
  return 0;
}

