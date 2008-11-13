#include<utility>
#include<bitset>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<cmath>
#include <map>
#include <stack>
#include <queue>
#include <cstdio>
#define PB push_back
#define MIN(a,b) (a < b ? a : b)
#define MAX(a,b) (a > b ? a : b)
#define FORN(i,N) for (int (i)=0;(i)<(N);(i)++)
#define mini(a,b,c,d)   MIN(MIN(a,b),MIN(c,d))
#define maxi(a,b,c,d)   MAX(MAX(a,b),MAX(c,d))


using namespace std;
int n,N,K;
char T[1101][1101];

struct lineas{
       short x1;
       short y1;
       short x2;
       short y2;
       short alt;
};


lineas vec1[2100];


char VERT[1100][1100] ;
char HORT[1100][1100] ;

inline bool puedo(short i, short j,char type){

       if (i<0 || j<0 || i>=K || j>=K || T[i][j]==2) return false;

       switch (type){
               case 0: {
                               if (VERT[i][j])
                                       return false;
                               return true;
                       }

               case 1:{
                              if (HORT[j][i])
                                      return false;
                              return true;
                      }

               case 2:{
                              if (VERT[i+1][j])
                                      return false;
                              return true;
                      }

               default:{
                               if (HORT[j+1][i])
                                       return false;
                               return true;
                       }
       }
}

struct point{
       short x;
       short y;
};
char present [1101][1101];
point Q[1101*1101];
void doit(){
   
       point tmp={0,0};
       int ini=0;
       int final=0;
       Q[final++]=tmp;
   
       memset(present,0,sizeof(present));
       present[0][0]=1;

       while (ini!=final){
               point tmp1=Q[ini++];
               int i= tmp1.x;
               int j= tmp1.y;

               if (i<0 || j<0 || i>=K || j>=K || T[i][j]==2) continue;

               T[i][j]=2;

               if ( !present[i][j-1] && puedo(i,j-1,3)){
                       point g={i,j-1};
                        Q[final++]=g;
                       present[i][j-1]=1;
               }

               if ( !present[i-1][j]  && puedo(i-1,j,2)){
                       point g={i-1,j};
                         Q[final++]=g;
                       present[i-1][j]=1;
               }

               if ( !present[i][j+1] && puedo(i,j+1,1)  ){
                       point g={i,j+1};
                         Q[final++]=g;
                       present[i][j+1]=1;
               }

               if ( !present[i+1][j] && puedo(i+1,j,0)   ){
                       point g={i+1,j};
                        Q[final++]=g;
                       present[i+1][j]=1;
               }
       }
}
lineas vec[2100];

int main()

{
	
       while (1){
               scanf("%d",&n );
               if (!n)break;

               memset(VERT,0,sizeof(VERT));
               memset(HORT,0,sizeof(HORT));
               memset(T,0,sizeof(T));

        


               int x1,y1,x2,y2,cost;
               int minn=100000;
               int maxx=-100004;

               FORN(i,n)
               {
		       scanf("%d %d %d %d %d",&x1,&y1,&x2,&y2,&cost );
                       lineas tmp={x1,y1,x2,y2,cost};
                       vec[i]=tmp;

               }

               scanf("%d",&cost );
	       int voy=0;
               FORN(i,n)
                       if (vec[i].alt>=cost){
                               vec1[voy++]=vec[i];
                               x1=vec[i].x1,x2=vec[i].x2,y1=vec[i].y1,y2=vec[i].y2;
                               minn=MIN(minn,mini(x1,y1,x2,y2));
                               maxx=MAX(maxx,maxi(x1,y1,x2,y2));
                       }


               N=voy;

               if (minn>0)goto g;
               if (minn==0)minn=1;
               else {
                       minn*=-1;
                       minn+=2;
               }

               FORN(i,N) {
                       vec1[i].x1+=minn;
                       vec1[i].x2+=minn;
                       vec1[i].y1+=minn;
                       vec1[i].y2+=minn;
               }


            g:

               FORN(i,N){
                       if (vec1[i].x1==vec1[i].x2)
                               for (int j=min(vec1[i].y1,vec1[i].y2);j<max(vec1[i].y1,vec1[i].y2); j++)
                                       VERT[vec1[i].x1][j]=1;
                       else
                               for (int j=min(vec1[i].x1,vec1[i].x2);j<max(vec1[i].x1,vec1[i].x2); j++)
                                       HORT[vec1[i].y1][j]=1;

               }

               K=maxx+minn+3;
               doit();
               int count=0;
               FORN(i,K)
                    FORN(j,K)
                       if (!T[i][j]) count++;
	       printf("%d\n",count);

       }

       return 0;
}



