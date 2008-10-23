#include<iostream>
#include<stdio.h>
#include<map>
#include<vector>
#include<list>
#include<math.h>
#include<string>
#include<string.h>
#include<algorithm>
#include<stack>
#include<queue>
#include<bitset>
#define D(x) cerr<<__LINE__<<" "#x" "<<x<<endl
using namespace std;

string out[]={"SELL ON DAY ","BUY ON DAY "};
double points[10001];

int main()
{
  int m,n,k;
  bool first_run = true;
  while( cin >> m >> n >> k ){
    if (!first_run) cout << endl;
    first_run = false;
    for(int i=1; i<=k; cin >> points[i++]);

    double acuM=0,acuN=0,avM,avN;
    for(int i=n-m+1; i<n; acuM+=points[i++]);
  
    for(int i=1; i<n ; acuN+=points[i++]);

    bool first=true,buy;
    for(int i=n; i<=k ;++i)
      {
	acuM+=points[i];
	acuN+=points[i];

	avM=acuM/(m);
	avN=acuN/(n);
	if(first)
	  {
	    first=false;
	    if(avM>avN)
	      buy=true;
	    else
	      buy=false;
	    cout<<out[buy]<<i<<endl;
	  }
	else if(buy && avM<avN)
	  {
	    buy=false;
	    cout<<out[buy]<<i<<endl;
	  }
	else if(!buy && avM>avN)
	  {
	    buy=true;
	    cout<<out[buy]<<i<<endl;
	  }
	//      D(avM),D(avN);
	acuM-=points[i-m+1];
	acuN-=points[i-n+1];
      }
  }
  return 0;
}

