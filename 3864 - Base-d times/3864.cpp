#include <iostream>
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

int main(){
  int d;
  while (scanf("%d", &d) == 1 && d){
    int h0, m0, h1=0, m1;
    scanf("%d:%d %d:%d", &h0, &m0, &h1, &m1);

    //    printf("Leí d=%d, hora0 = %d:%d, hora1 = %d:%d\n", d, h0, m0, h1, m1);
    /*int base[d];
    for(int i=0;i<d;++i){
      base[i]=i;
      }*/
    /*
    //cota inferior
    int infH=h0;
    if(h0>((d-1)+10*(d-1))) inf=(d-1)+10*(d-1);
    int infM=m0;
    if(m0>((d-1)+10*(d-1))) inf=(d-1)+10*(d-1);
    //cota superior
    int supH=h1;
    if(h1>((d-1)+10*(d-1))) inf=(d-1)+10*(d-1);
    int supM=m1;

    if(m1>((d-1)+10*(d-1))) inf=(d-1)+10*(d-1);
    */
    printf("%d:%.2d to %d:%.2d:\n",h0, m0, h1, m1);
    int ans;
    for(int i=0;i<d;++i){
      for(int j=0;j<d;++j){
        for(int k=0;k<d && k < 6;++k){
          for(int p=0;p<d;++p){
            ans=i*1000+j*100+k*10+p;
            if(ans>=(h0*100 + m0) && ans<=(h1*100+m1)){
              // cerr<<ans;
              printf("   %d\n",d*d*d*i+d*d*j+d*k+p);

            }

          }
        }
      }
    }
    printf("\n");
  }
  return 0;
}
