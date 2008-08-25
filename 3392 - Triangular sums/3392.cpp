#include <stdio.h>

long long t(long long n){
  return n*(n+1)/2;
}

int main(){
  int n, m, c=1;
  scanf("%d", &m);
  while (m-- && scanf("%d",&n) == 1){
    long long ans = 0;
    for (int k=1; k<=n; ++k){
      ans += k*t(k+1);
    }
    printf("%d %d %lld\n", c++, n, ans);
  }
  return 0;
}
