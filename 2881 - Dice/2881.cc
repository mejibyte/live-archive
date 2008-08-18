#include<stdio.h>
#include<cstring>
int main(){
  int p,s;
  int trap[3];
  while(scanf("%d %d",&p,&s) &&!(p==0 && s==0)){
    int players[p];
    bool p_trap[p];
    memset(players,0,sizeof players);
    memset(p_trap,false,sizeof p_trap);
    scanf("%d %d %d",&trap[0],&trap[1],&trap[2]);
    int turn;
    scanf("%d",&turn);
    int d1,d2;
    int winner=-1;
    int turno=0;
    for(int i=0;turno<turn && scanf("%d %d",&d1,&d2);++i,++turno){
      if(!p_trap[i%p]){
        players[i%p]+=d1+d2;
        if(players[i%p]>s && winner<0) winner=(i%p)+1;
        if(players[i%p]==trap[0]||players[i%p]==trap[1]||players[i%p]==trap[2]){
          p_trap[i%p]=true;
        }
      }else{
        p_trap[i%p]=false;
        for(++i;;++i){
          if(!p_trap[i%p]){
            players[i%p]+=d1+d2;
            if(players[i%p]>s && winner<0) winner=(i%p)+1;
            if(players[i%p]==trap[0]||players[i%p]==trap[1]||players[i%p]==trap[2]){
              p_trap[i%p]=true;
            }
            break;
          }else{
            p_trap[i%p]=false;
          }
        }
      }
    }

    printf("%d\n",winner);
  }
  return 0;
}
