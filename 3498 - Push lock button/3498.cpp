/*
  Accepted
 */
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

long long memo[(1<<11)+1];
int max_moves;

/*
  dp(mask) = Cantidad de maneras en que puedo formar secuencias
  si inicialmente he usado los numeros indicados en mask.
 */
long long dp(int used){
  if (used == max_moves - 1) return 0; //all used
  long long &ans = memo[used];
  if (ans == -1){
    ans = 0;
    for (int move=1; move<max_moves; ++move){
      if ((used & move) == 0){
        ans += 1 + dp(used | move);
        //Puedo hacer el movimiento y parar ahí (+1)
        //Puedo hacer el movimiento y seguir haciendo (+dp(used | move))
      }
    }
  }
  return ans;
}

int main(){
  int n, m;
  scanf("%d", &n);
  for (int i=1; i<=n; ++i){
    scanf("%d", &m);
    max_moves = 1 << m;
    memset(memo, -1, sizeof memo);
    printf("%d %d %lld\n", i, m, dp(0));
  }
  return 0;
}

