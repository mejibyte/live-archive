/*
  March of the penguins
  Mathijs Vogelzang, April 2007

  Total +- 30 minutes. Can be improved by using Dijkstra to augment paths.

  Extra 15 minutes to find & fix stupidness in flow implementation.
*/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <vector>
using namespace std;
typedef vector<int> VI;

#define MAXN 100

struct Island
{
      int penguins;
      int maxjump;
      int X, Y;
};

double jump;
int totalPenguins;
vector<Island> islands;
int N;
int dest;
int flows[MAXN][MAXN], iflows[MAXN];
bool canjump[MAXN][MAXN];
bool visit[MAXN*2];

int augmentFlow(int src)
{
   if(src == dest)
      return 1;
   visit[src] = 1;
   if(src < N)
   {
      // entry of island      
      if(!visit[src+N] &&
         iflows[src] < islands[src].maxjump && augmentFlow(src+N))
      {
         iflows[src] ++;
         return 1;
      }
      for(int i=0;i<N;i++)
         if(canjump[i][src] && !visit[i+N] && flows[i][src] > 0 &&
            augmentFlow(i+N))
         {
            flows[i][src]--;
            return 1;
         }
   }
   else
   {
      // exit of island
      src -= N;
      if(!visit[src] &&
         iflows[src] > 0 && augmentFlow(src))
      {
         iflows[src] --;
         return 1;
      }
      for(int i=0;i<N;i++)
         if(!visit[i] && canjump[src][i] && augmentFlow(i))
         {
            flows[src][i] ++;
            return 1;
         }
   }

   return 0;
}

int possible(int _dest)
{
   dest = _dest;
   int n = 0;
   memset(flows, 0, sizeof(flows));
   memset(iflows, 0, sizeof(iflows));
   memset(visit, 0, sizeof(visit));   
   for(int i=0;i<N;i++)
   {
      int islandCount = islands[i].penguins;

      while(islandCount-- && augmentFlow(i))
      {
         n++;
         memset(visit, 0, sizeof(visit));
      }
      if(islandCount > 0) break;
   }
   return n == totalPenguins;
}

void initJumps()
{
   double d2 = jump * jump;
   for(int i=0;i<N;i++)
      for(int j=i;j<N;j++)
      {
         int distance = (islands[i].X - islands[j].X) * (islands[i].X- islands[j].X) + (islands[i].Y- islands[j].Y) * (islands[i].Y - islands[j].Y);
//         assert(fabs(distance - jump) > 1E-9);
         canjump[i][j] = canjump[j][i] = distance < d2;
      }
}

int main()
{
   int runs;
   scanf("%d", &runs);
   while(runs--)
   {
      scanf("%d %lf", &N, &jump);
      islands = vector<Island>(N);
      totalPenguins = 0;
      for(int i=0;i<N;i++)
      {
         int X, Y, penguins, maxjump;
         scanf("%d %d %d %d", &X, &Y, &penguins, &maxjump);
         islands[i] = (Island){penguins, maxjump, X, Y};
         totalPenguins += penguins;
      }

      vector<int> poss;
      initJumps();
      for(int i=0;i<N;i++)
         if(possible(i))
            poss.push_back(i);
      if(poss.size() == 0)
         printf("-1\n");
      else
         for(int i=0;i<poss.size();i++)
         {
            printf("%d", poss[i]);
            if(i == poss.size()-1) printf("\n");
            else printf(" ");
         }
   }
   
   return 0;
}
