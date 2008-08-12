#include <iostream>
#include <stdio.h>
using namespace std;

int main(){
  int n;
  while (scanf("%d", &n) == 1 && n){
    bool post[n];
    int firstPost = -1;
    for (int i=0; i<n; ++i){
      scanf("%d", &post[i]);
      if (post[i] && firstPost == -1){
        firstPost = i;
      }
    }

    if (firstPost == -1){ //Todos son ceros
      printf("%d\n", n/2 + (n&1));
    }else{
      int count = 0;
      int i = firstPost;
      do{
        if (!post[i] && !post[(i+1)%n]){
          post[(i+1)%n] = true;
          count++;
        }
        i = (i+1)%n;
      }while (i != firstPost);
      printf("%d\n", count);
    }
  }
  return 0;
}
