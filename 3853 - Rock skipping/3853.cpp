/*
  Problema: Rock Skipping

  Equipo: Factor común (team18)
  Sebastián Arcila Valenzuela
  Daniel Restrepo Montoya
  Andrés Mejía Posada

*/
#include <iostream>
#include <cassert>
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <vector>
#include <string>
#include <string.h>
#include <set>
#include <map>
#include <stack>
#include <list>
#include <queue>
#include <sstream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <iterator>

using namespace std;
struct thr{
  int count,len,initial,skips;
  thr(){
    count=0;
    len=0;
    initial=0;
    skips=INT_MAX;
  }
  bool operator >(const thr &t)const{
    if(count>t.count) return true;
    else if(count==t.count && len>t.len) return true;
    else if(count==t.count && len==t.len && initial>t.initial) return true;
    else if(count==t.count && len==t.len && initial==t.initial && skips<t.skips) return true;
    return false;
  }
};
int main() {
  string lake;
  while(cin>>lake && lake!="END"){
    thr best;
    int count;
    bool entro = false;
    for(int i=0;i<lake.size();++i){
      for(int j=1;j<lake.size();++j){
        //cout << "Best " << best.count << "," << best.len << "," << best.initial << "," << best.skips << endl;
        count=0;
        int k = 0;
        entro = true;
        for(k=i+j;lake[i]=='.' && k<lake.size();k+=j){
          count++;

          if(lake[k]!='.')break;
        }
        if(k>=lake.size()) {
          k = k-j;
          if(lake[k]=='.') count++;
        }
        thr temp;
        temp.count=count;
        temp.initial=i;
        temp.skips=j;
        temp.len=k;
        //cout << "Temp " << temp.count << "," << temp.len << "," << temp.initial << "," << temp.skips << endl;
        if(temp>best)
          best=temp;
      }
    }
    if(entro)
      printf("%d %d\n",best.initial,best.skips);
    else
      printf("0 1\n");
  }
  return 0;
}
