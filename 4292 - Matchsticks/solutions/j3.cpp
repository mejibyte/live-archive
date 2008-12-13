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

    int S,N;
    cin>>S>>N;

    vector<int> s(N);
    for (int i=0; i<N; i++) { cin>>s[i]; s[i]--; }

    vector<int> last(S,-1);
    vector<pair<int,int> > x;
    
    for (int i=0; i<N; i++) {
      if (last[s[i]]!=-1 && i-last[s[i]]<S) {
	int fr = last[s[i]] % S;
	int to = i % S;
	
	if (fr<to) {
	  x.push_back(make_pair(0,fr));
	  x.push_back(make_pair(to,S));
	}
	if (fr>to) 
	  x.push_back(make_pair(to,fr));
      }
      
      last[s[i]]=i;
    }

    sort(x.begin(),x.end());
    
    int res=S;

    for (int i=0; i<x.size();) {
      int fr = x[i].first;
      int to = x[i].second;
      i++;
      
      while (i<x.size() && x[i].first>=fr && x[i].first<to)
	to >?= x[i++].second;

      res -= to-fr;
    }

    cout<<res<<endl;
  }
  
  return 0;
}
