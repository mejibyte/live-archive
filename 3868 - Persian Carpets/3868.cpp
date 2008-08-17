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
struct carpet{
  int h,w;
  carpet(int a,int b){
    h=a>b?a:b;
    w=a>b?b:a;
  }
  bool operator <(const carpet &t)const{
    return (h<t.h||(h==t.h && w<t.w));
  }
};
int main(){
  int q,b,cont=1;
  while(cin>>q>>b && !(q==0 &&b==0)){
    carpet one(q,b);
    vector<carpet> room;
    room.push_back(one);
    for(int i=1;i<=2;++i){
      cin>>q>>b;
      carpet temp(q,b);
      room.push_back(temp);
    }
    sort(room.begin(),room.end());
    int a=room[2].h;//(room[0].w+room[1].h)>room[2].h?(room[0].w+room[1].h):room[2].h;
    int l;//=room[2].w+(room[0].h>room[1].w?room[0].h:room[1].w);
    if(room[2].w+room[1].h<=room[2].h){
      if(a<room[1].w+room[0].w){
        a=room[1].w+room[0].w;
      }
      l=room[2].w+room[1].h;
    }else{
      if(a<room[1].h+room[0].w){
        a=room[1].h+room[0].w;
      }
      l=room[2].w+(room[0].h>room[1].w?room[0].h:room[1].w);
    }
    if(a> room[0].w+room[1].w+room[2].w){
      a=room[2].h;
      l=room[0].w+room[1].w+room[2].w;
    }
    //cerr<<a<<" "<<l<<" ";
    printf("Set %d: minimum dimension = %d\n",cont++,a>l?a:l);

  }
  return 0;
}
