/*
  [NWERC'07] WALK
  by: Jan Kuipers
*/

using namespace std;

#include <iostream>
#include <vector>
#include <stack>

const double eps = 1e-9;

int main () {

  int runs;
  cin>>runs;
  while (runs--) {
    int N;
    cin>>N;
    vector<int> h(N),n(N);
    vector<vector<pair<int,int> > > p(N);
    for (int i=0; i<N; i++) {
      cin>>h[i]>>n[i];
      p[i]=vector<pair<int,int> >(n[i]);
      for (int j=0; j<n[i]; j++)
	cin>>p[i][j].first>>p[i][j].second;
      p[i].push_back(p[i][0]);
    }

    vector<pair<double,int> > cross;
    for (int i=0; i<N; i++)
      for (int j=0; j<n[i]; j++) {
	if ((p[i][j].second-eps)*(p[i][j+1].second-eps) > 0) continue;
	double x = p[i][j].first + 1.0*(p[i][j+1].first-p[i][j].first)/(p[i][j+1].second-p[i][j].second) * -p[i][j].second;
	if (x>0 && x<100000) cross.push_back(make_pair(x,i));
      }
    sort(cross.begin(),cross.end());
    
    stack<int> s;
    for (int i=0; i<cross.size(); i++)
      if (s.size() && s.top()==cross[i].second)
	s.pop();
      else
	s.push(cross[i].second);

    int asc=0, desc=0, last=0;
    if (s.size()) { last=s.top(); s.pop(); }
    
    while (s.size()) {
      int diff=h[s.top()]-h[last];
      if (diff>0) desc+=diff; else asc-=diff;
      last=s.top();
      s.pop();
    }
    
    cout<<asc<<" "<<desc<<endl;
  }
  
  return 0;
}
