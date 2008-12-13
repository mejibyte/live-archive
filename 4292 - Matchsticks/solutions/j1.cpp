/*
  [NWERC'08] SHUFFLE
  by: Jan Kuipers
*/

using namespace std;

#include <iostream>
#include <vector>

int main () {

  int runs;
  cin>>runs;

  while (runs--) {
    int N,K;
    cin>>K>>N;
    vector<int> x(N+2*K,-1);
    for (int i=0; i<N; i++) { cin>>x[i+K]; x[i+K]--; }

    int ncnt=0;
    vector<int> cnt(K,0);
    vector<int> ok(N+K+1,0);

    for (int i=0; i<N+K+1; i++) {
      if (ncnt==K) ok[i]=1;
      if (i<K && ncnt==i) ok[i]=1;
      if (i>N && ncnt==N+K-i) ok[i]=1;
      if (i==N+K) break;
      if (x[i]!=-1 && --cnt[x[i]]==0) ncnt--;
      if (x[i+K]!=-1 && cnt[x[i+K]]++==0) ncnt++;
    }
        
    int res=0;
    for (int i=0; i<K; i++) {
      int tmp=1;
      for (int j=i; j<N+K+1; j+=K) if (!ok[j]) tmp=0;
      res += tmp;
    }

    if (res==N+1) res=K;
				       
    cout<<res<<endl;
  }

  return 0;
}

  
