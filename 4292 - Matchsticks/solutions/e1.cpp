/*
  [NWERC'08] EASY CLIMB
  by: Jan Kuipers
*/

using namespace std;

#include <iostream>
#include <vector>

long long N,D;
vector<long long> h;

int main () {
  int runs;
  cin>>runs;
  while (runs--) {
    
    cin>>N>>D;
    h = vector<long long>(N);
    for (int i=0; i<N; i++) cin>>h[i];

    if (abs(h[0]-h[N-1]) > (N-1)*D) {
      cout<<"impossible"<<endl;
      continue;
    }

    vector<long long> posh(N);

    for (int i=0; i<N; i++)
      for (int j=-N+1; j<=N-1; j++) 
	posh.push_back(h[i] + j*D);
    
    sort(posh.begin(),posh.end());
    posh.erase(unique(posh.begin(),posh.end()),posh.end());
    int H=posh.size();
    
    vector<long long> best(H, LONG_LONG_MAX/2);
    for (int i=0; i<H; i++)
      if (posh[i]==h[0]) best[i]=0;

    for (int n=1; n<N; n++) {
      vector<long long> next(H, LONG_LONG_MAX/2);
      int j=0;
      
      for (int i=0; i<H; i++) {
	while (j<H && posh[j]<posh[i]-D) j++;
	while (j+1<H && posh[j+1]<=posh[i]+D && best[j+1]<=best[j]) j++;
	next[i] <?= best[j] + abs(posh[i]-h[n]);
      }

      best=next;
    }
    
    for (int i=0; i<H; i++)
      if (posh[i]==h[N-1])
	cout<<best[i]<<endl;
  }
  
  return 0;   
}
  
