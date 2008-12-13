/*
  team6
  maquina 27
*/

#include<iostream>
#include<stdio.h>
#include<math.h>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
#include<stdlib.h>
#include<assert.h>
#include<sstream>
#include<stack>
#include<queue>
using namespace std;

int main(){
    freopen("feynman.in","r",stdin);
    for(long long n,ans;cin>>n && n;cout<<ans<<endl){
         ans=0;
         for(long long i=1;i<=n;++i)ans+=(i*i);
    }
    return 0;
}
