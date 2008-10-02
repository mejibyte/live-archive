/*
  Accepted
*/
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<limits.h>
#include<queue>
#include<vector>
#include<iostream>
#include<set>
using namespace std;
const int TAM=2*52, oo=INT_MAX/4;
int cap[TAM][TAM],res[TAM][TAM], prev[TAM];
set<int> g[TAM];
int flow(int n,int source,int sink){
  int ans=0;
  memcpy(res, cap, sizeof cap);
  for(;;){
    memset(prev,-1,sizeof prev);
    prev[source]=-2;
    queue<int> q;
    q.push(source);
    while(q.size() && prev[sink]==-1){
      int u=q.front();
      q.pop();
      for(set<int>::iterator i=g[u].begin();i!=g[u].end();++i){
	const int &v=*i;
	if(prev[v]==-1 && res[u][v]>0){
	  prev[v]=u;
	  q.push(v);
	}
      }
    }
    if(prev[sink]==-1)
      break;
    int bot=oo;
    for(int i=sink;  prev[i] >= 0; i = prev[i])
      bot=min(bot,res[prev[i]][i]);
    for(int i=sink; prev[i] >= 0 ; i= prev[i]){
      res[prev[i]][i]-=bot;
      res[i][prev[i]]+=bot;
    }
    ans+=bot;
  }
  return ans;
}
inline int in(const int &a){
  return 2*a;
}
inline int out(const int &a){
  return 2*a+1;
}
int main(){
  for(int n,m,f; scanf("%d%d",&n,&m)==2 ; printf("%d\n",f)){
    if(n==0)f=0;
    else if(n==1)f=1;
    else if(m==0)f=0;
    else{
      memset(cap,0,sizeof cap);
      for(int i=0;i<2*n;g[i++].clear());
      for(int i=0;i<n;++i){
	cap[in(i)][out(i)]=1;
	g[in(i)].insert(out(i)),g[out(i)].insert(in(i));
      }
      for(int u,v; m-- && scanf(" (%d,%d)",&u,&v)!=EOF ;){
	g[out(u)].insert(in(v)), g[in(v)].insert(out(u));
	g[out(v)].insert(in(u)), g[in(u)].insert(out(v));
	cap[out(u)][in(v)]=oo;
	cap[out(v)][in(u)]=oo;
      }
      f=oo;
      for(int s=0;s<n;++s)
	for(int t=s+1;t<n;++t){
	  int k = flow(2*n, out(s), in(t));
	  //	  cout<<s<<" "<<t<<" "<<k<<endl;
	  f=min(f,k);
	}

      if(f>=oo)f=n;
    }
  }
  return 0;
}
