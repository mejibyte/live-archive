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

struct times{
  int hh,mm,ss;
  times(int h,int m,int s){
    hh=h;
    mm=m;
    s=ss;
  }
  times(int m,int s){
    m=mm;
    s=ss;
    hh=0;
  }
  bool operator <(const times & p)const{
    return (hh<p.hh ||(hh==p.hh && mm<p.mm)||(hh==p.hh && mm==p.mm ||ss<p.ss));
  }

};
struct points{
  string name;
  string type;
  times time;
  int point;
  points(string names,string tipo,times temp,int pnt){
    name=names;
    type=tipo;

    if(type=="TIMED"){
      time=temp;
      point=0;
    }else{
      point=pnt;
    }
  }
};
int main(){
  string nameContest;
  int even;
  while(cin>>nameContest>>even){
    while(even--){
      string name,type;
      int players;
      cin>>name>>type>>players;
      vector<points> contest(players)
      while(players--){

        if(type=="TIMED"){
          cin>>contest[i].name;
          scan
        }else{
        }
      }
    }
  }
  return 0;
}
