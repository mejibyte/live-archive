/* Catdog, NWERC 2007
   Mathijs Vogelzang

   Total coding time 19 minutes
*/
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

#define MAXVOTE 500
#define MAXCAT 100

char disagree[MAXVOTE][MAXVOTE];
char group[MAXVOTE];
int linked[MAXVOTE];
int N;
char used[MAXVOTE];

int augment(int x)
{
   if(used[x]) return 0;
   used[x] = 1;
   if(group[x] == 0) {
      for(int i=0;i<N;i++)
         if(disagree[i][x] && linked[i] != x && augment(i)) {
            linked[i] = x;
            return 1;
         }
   } else {
      if(linked[x] == -1 || augment(linked[x])) return 1;
   }
   return 0;
}

int maxflow() {
   int res = 0;
   for(int i=0;i<N;i++) {
      memset(used, 0, sizeof(used));
      if(group[i] == 0 && augment(i)) res++;
   }
   return res;
}

int main()
{
   int runs;
   scanf("%d", &runs);
   while(runs--) {
      memset(disagree,0,sizeof(disagree));
      memset(linked, -1, sizeof(linked));
      int a, b;
      scanf("%d %d %d", &a, &b, &N);
      vector<int> B1, B2;
      for(int i=0;i<N;i++) {
         char s1[10], s2[10];
         scanf("%s %s", s1, s2);
         B1.push_back((s1[0] == 'C' ? MAXCAT+10 : 0) + atoi(s1+1));
         B2.push_back((s2[0] == 'C' ? MAXCAT+10 : 0) + atoi(s2+1));
         group[i] = B1[i] < MAXCAT+10;
         for(int j=0;j<i;j++) {
            if(B1[i] == B2[j] || B2[i] == B1[j])
               disagree[i][j] = disagree[j][i] = 1;
         }
      }
      printf("%d\n", N - maxflow());
   }
   return 0;
}
