/*
  [NWERC'07] DORM
  by: Jan Kuipers
*/

using namespace std;

#include <iostream>
#include <vector>
#include <string>

vector<string> m;

void go (int Y, int X, int flip, int dep) {

  for (int x=0; x<X-2; x++)
    m[flip? x : Y-1][flip? Y-1 : x] = 'B';

  for (int y=0; y<Y; y++)
    m[flip? X-1 : y][flip? y : X-1] = 'B';
  
  for (int x=0; x<X; x++)
    for (int y=0; y<Y-2; y++)
      m[flip? x : y][flip? y : x] = (X-x)%3!=2 ? 'B' : '.';

  if (X%3 && (X>5 || Y>5)) go(3+X%3, Y, !flip, dep+1);

  if (dep==0) {
    m[flip? X-2 : Y-1][flip? Y-1 : X-2]='E';
    
    if (m[0][0]=='B' && m[1][0]=='B' && m[0][1]=='B') m[0][0]='.';
    if (m[1][0]=='B' && m[2][0]=='B' && m[0][1]=='B') m[1][0]='.';
    if (m[0][1]=='B' && m[0][2]=='B' && m[1][0]=='B') m[0][1]='.';
  }
}

int cnt () {
  int res=0;
  for (int y=0; y<m.size(); y++)
    for (int x=0; x<m[0].size(); x++)
      if (m[y][x]=='B') res++;

  return res;
}

int main () {

  int runs;
  cin>>runs;
  
  while (runs--) {

    int Y,X;
    cin>>Y>>X;

    m = vector<string>(Y, string(X, '.'));

    if (X==1 && Y==1) {
      m[0][0]='E';
    }
    else if (X==1) {
      m[0][0]='B';
      m[Y-1][0]='B';
      m[1][0]='E';      
    }
    else if (Y==1) {
      m[0][0]='B';
      m[0][X-1]='B';
      m[0][1]='E';      
    }
    else if ((X==2 && Y!=3) || X==3) {
      m[0][1]='E';      
      for (int y=0; y<Y; y++) {
	m[y][0]='B';
	if (X==3) m[y][2]='B';
      }
    }
    else if (Y==2 || Y==3) {
      m[1][0]='E';      
      for (int x=0; x<X; x++) {
	m[0][x]='B';
	if (Y==3) m[2][x]='B';
      }
    }
    else {
      go(Y,X,0,0);
      vector<string> old=m;
      int cnt1 = cnt();
      
      m = vector<string>(Y, string(X, '.'));
      go(X,Y,1,0);
      int cnt2 = cnt();

      if (cnt1>cnt2) m=old;
    }
    
    for (int y=0; y<Y; y++) cout<<m[y]<<endl;
  }
  
  return 0;
}
