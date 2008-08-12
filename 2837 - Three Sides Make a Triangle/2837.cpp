/*
  Código hecho por Arcila, pero da Wrong Answer :(
 */
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

const long double pi = acos(-1.0);

struct trian{
  long double la,lb,lc,aa,ab,ac;
  trian(long double x1,long double y1, long double x2, long double y2, long double x3,long double y3){
    la=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    lb=sqrt((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3));
    lc=sqrt((x3-x1)*(x3-x1)+(y3-y1)*(y3-y1));
    aa=acos(fabs((x1-x3)* (x3-x2)+(y1-y3)*(y3-y2))/(lb*lc));
    ab=acos(fabs((x3-x1)* (x1-x2)+(y3-y1)*(y1-y2))/(la*lc));
    ac=acos(fabs((x1-x2)* (x2-x3)+(y1-y2)*(y2-y3))/(la*lb));
    //ojo con el orden de los pnt
  }
};

struct point{
  long double x,y;
};

int main(){
  point a,b,c;
  while(cin>>a.x>>a.y>>b.x>>b.y>>c.x>>c.y){
    int l=0;
    trian tr(a.x ,a.y,b.x,b.y,c.x,c.y);

    //cout<<tr.la<<" "<<tr.lb<<" "<<tr.lc<<" "<<tr.aa<<" "<<tr.ab<<" "<<tr.ac<<"\n";

    vector<long double> v; v.push_back(tr.la); v.push_back(tr.lb); v.push_back(tr.lc);
    sort(v.begin(), v.end());
    if (fabs(v[0] + v[1] - v[2]) <= 0.01)
      printf("Not a Triangle\n");
    else{
      fabs(tr.la-tr.lb)<=0.01?++l:l;
      fabs(tr.lc-tr.lb)<=0.01?++l:l;
      fabs(tr.la-tr.lc)<=0.01?++l:l;
      switch (l){
      case 0:
        printf("Scalene ");
        break;
      case 1:
        printf("Isosceles ");
        break;
      default:
        printf("Equilateral ");
      }
      if(fabs(tr.aa)>pi/2.0||fabs(tr.ab)>pi/2.0||fabs(tr.ac)>pi/2.0)
        printf("Obtuse\n");
      else if(fabs(tr.aa-pi/2.0)<=pi/180.0||fabs(tr.ab-pi/2.0)<=pi/180.0||fabs(tr.ac-pi/2.0)<=pi/180.0)
        printf("Right\n");
      else
        printf("Acute\n");
      //cout<<tr.la<<" "<<tr.lb<<" "<<tr.lc<<" "<<tr.aa<<" "<<tr.ab<<" "<<tr.ac<<"\n";
      //cout<<"Pi = "<<pi<<" pi/2.0="<<pi/2.0<<endl;
    }

  }
  printf("End of Output\n");
  return 0;
}
