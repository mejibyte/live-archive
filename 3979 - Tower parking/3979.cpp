/*
  Accepted
 */
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>
using namespace std;
int park[50][50];
int main(){
  int n;
  scanf("%d",&n);
  while(n--){
    int h,l;
    scanf("%d %d",&h,&l);
    int pos[h];
    memset(pos,0,sizeof pos);
    int max=0;
    for(int i=0;i<h;++i) for(int j=0;j<l;++j){
        scanf("%d",&park[i][j]);
        if(max<park[i][j]) max=park[i][j];
      }
    //cout<<"lei todo"<<endl;
    int i=0,j=0,car,time=0;
    for(car=1;car<=max;++car){
      for(i=0;i<h;++i){
        bool q=false;
        for(j=0;j<l;++j){
          if(park[i][j]==car) {
            time = time + (2*i*10);
            int t,t1;
            t=abs(pos[i]-j);
            if(pos[i]<j)
              t1=pos[i]+l-j;
            else
              t1=j+l-pos[i];
            time=time+ (5*(t<?t1));
            pos[i]=j;
            q=true;
            break;
          }
        }
        if(q)break;
      }

    }
    printf("%d\n",time);
  }
  return 0;
}
