// DecT.cc
// sol to Decorations problem
// T Feil


#include <string>
#include <iostream>
using namespace std;

int n, l, m, board[600],newboard[600],matches[600][600];
string beads[600];

bool PreSuf(string s1, string s2, int s){
  bool OK = true;
  for(int i=0;i<s-1;i++)
    if(s1[i] != s2[1+i]) OK = false;
  return OK;
}

void initBoard(int m, int s){
  for(int i=0;i<m;i++)
    board[i]=1;
  //now find all patterns where suff==pref
  //store results in matches[][]
  for(int i=0;i<m;i++)
    for(int j=0;j<m;j++)
      matches[i][j]=0;
  for(int i=0;i<m;i++)
    for(int j=0;j<m;j++)
      if(PreSuf(beads[i],beads[j],s))
        matches[i][j]=1;
}

void FillIn(int i){
  int count=0;
  for(int k=0;k<m;k++)
    if(matches[i][k])
      count += board[k];
  newboard[i]=count;
}

int main(){

	int s, sum;

	cin>>n>>l>>m;
	while(n>0){
		cin>>beads[0];
		s = beads[0].length();
		for(int i=1;i<m;i++)
			cin>>beads[i];

		if (l < s)
			sum = 0;
		else if(s==1){
			sum=1;
			for(int i=0;i<l;i++) sum *= m;
		}
		else{
			initBoard(m,s);
			for(int j=s+1;j<=l;j++){
				for(int i=0;i<=m;i++)
					FillIn(i);  //board[i]<-?
				for(int i=0;i<m;i++) board[i]=newboard[i];
			}

			sum=0;
			for(int i=0;i<m;i++)
				sum += board[i];
		}

		cout<<sum<<endl;

		cin>>n>>l>>m;
	}
	
	return 0;
}
