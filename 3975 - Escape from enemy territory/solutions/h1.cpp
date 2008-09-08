/*
  [NWERC'07] OBFUSCATION
  by: Jan Kuipers
*/

using namespace std;

#include <iostream>
#include <vector>
#include <string>
#include <map>

const int MAXWORDLEN = 100;

string mix (string w) {
  if (w.size()<=2) return w;
  sort(w.begin()+1, w.end()-1);
  return w;
}

int main () {
  int runs;
  cin>>runs;
  while (runs--) {
    string s;
    cin>>s;
    int L=s.size();
    
    int N;
    cin>>N;

    map<string,int> cntword;
    map<string,string> word;
    
    for (int i=0; i<N; i++) {
      string w;
      cin>>w;
      cntword[mix(w)]++;
      word[mix(w)]=w;
    }

    vector<int> cnt(L+1);
    cnt[0]=1;
    
    for (int i=1; i<=L; i++) {
      for (int j=i-1; j>=0 && j>=i-MAXWORDLEN; j--)	
	cnt[i] += cnt[j] * cntword[mix(s.substr(j, i-j))];
      cnt[i]<?=2;
    }

    if (cnt[L]==0) cout<<"impossible"<<endl;
    if (cnt[L]==2) cout<<"ambiguous"<<endl;

    if (cnt[L]==1) {
      string sol;
      for (int i=L,j=L-1; i>0; j--)
	if (cnt[j] && cntword[mix(s.substr(j,i-j))]) {
	  if (sol!="") sol=" "+sol;
	  sol=word[mix(s.substr(j,i-j))]+sol;
	  i=j;
	}

      cout<<sol<<endl;
    }
  }
  
  return 0;   
}
