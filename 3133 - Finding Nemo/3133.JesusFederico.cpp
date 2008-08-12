#include <cstdio>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include <cstdlib>
#include <stack>
#include <queue>
#define FOR(i,j,n) for (int i=j;i<n;i++)
#define FORI(i,j,n) for (int i=j;i<=n;++i)
#define FORN(i,n) FOR(i,0,n)
#define sz size()
#define foreach(i, c) for( __typeof( (c).begin() ) i = (c).begin(); i != (c).end(); ++i )
#define CPRESENT(container, element) (find(ALL(container),element) != container.end())
#define MIN(a,b) (a < b ? a : b)
#define MAX(a,b) (a > b ? a : b)
#define ALL(x) x.begin(), x.end()
#define PB push_back
#define INF 1<<30



using namespace std;
int n,m,c,e,b,c1,x,y,d,t;
string tmp;
int desx,desy;

struct nod{
    int x;
    int y;
    int llev;
};


bool operator<(const nod &a,const nod &b){
    return a.llev>b.llev;
}

int mv[4][2]={{2,0},{-2,0},{0,2},{0,-2}};
    
int S[500][500];


    
int V[500][500];
int MEM[500][500];

    


int djk(){

    nod t={1,1,0};
    priority_queue<nod>Q;
    Q.push(t);
    FORN(i,500)
            FORN(j,500)
            MEM[i][j]=INF;
     memset(V,0,sizeof(V));
    while (!Q.empty()){
        nod tt = Q.top();
        Q.pop();
        if (tt.x==desx && tt.y==desy)return tt.llev;
        if (V[tt.x][tt.y]) continue;
        V[tt.x][tt.y]=1;
        FORN(i,4){
             if (tt.x+mv[i][0]>=480 || tt.x+mv[i][0]<0 || tt.y+mv[i][1]>=480 ||tt.y+mv[i][1]<0 || S[tt.x+mv[i][0]/2][tt.y+mv[i][1]/2]==1 || V[tt.x+mv[i][0]][tt.y+mv[i][1]] || MEM[tt.x+mv[i][0]][tt.y+mv[i][1]]<(tt.llev+1)) continue;
             nod t1 = {tt.x+mv[i][0],tt.y+mv[i][1],S[tt.x+mv[i][0]/2][tt.y+mv[i][1]/2]==2?tt.llev+1:tt.llev};
             MEM[tt.x+mv[i][0]][tt.y+mv[i][1]]=t1.llev;
             Q.push(t1);
        }
    }
    return -1;
}

int main(){
  
  
    while ( cin>>n>>m){
       if (n<0 && m<0)break;
       
       memset(S,0,sizeof(S));
      int x1,y1;
        FORN(i,n){
            cin>>y1>>x1>>d>>t;
            t*=2;
             t++;
            x1*=2;
            y1*=2;   
            if (d){
                FORN(q,t){
                    S[x1+q][y1]=1;
                }
            }else {
                FORN(q,t){
                    S[x1][y1+q]=1;
                }
            }   
        }
        
        FORN(i,m){
            cin>>y1>>x1>>d;
           t=1;
           x1*=2;
           y1*=2;
           if (d){
               x1++;
               FORN(q,t){
                   S[x1+q][y1]=2;
               }
           }else {
               y1++;
               FORN(q,t){
                   S[x1][y1+q]=2;
               }
           }
        }
        double fx,fy;
        cin>>fx>>fy;
        desx=floor(fy);
        desy=floor(fx);
        desy*=2.0;
        desx*=2.0;
        desx++;
        desy++;
    if (desx>450 || desy>450)cout<<0<<endl;
   else cout<<djk()<<endl;
    }
    return 0;
}
