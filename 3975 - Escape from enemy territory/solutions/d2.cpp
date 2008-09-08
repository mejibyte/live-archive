#include <cstdio>
#include <cctype>
#include <string>
#include <map>
#include <vector>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n) FOR(i,0,n)
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n) FORE(i,0,n)

int h,w; bool swapped;

void norm(string &s) {
	char to[10]; memset(to,'?',sizeof(to)); char next='0';
	REP(i,w) if(isdigit(s[i])) {
		if(to[s[i]-'0']=='?') to[s[i]-'0']=next++;
		s[i]=to[s[i]-'0'];
	}
}

void run() {
	scanf("%d%d",&h,&w); if(w<=h) swapped=false; else swapped=true,swap(w,h);
	
	vector<map<string,int> > best(h*w+1);
	vector<map<string,string> > prev(h*w+1);
	best[0][string(w,'-')+"N"]=0;
	REP(i,h*w) {
		int row=i/w,col=i%w;
		for(map<string,int>::iterator j=best[i].begin();j!=best[i].end();++j) {
			int nrspace=0; REP(k,w) if(isdigit(j->first[k])) ++nrspace;
			int nrcur=0; REP(k,w) if(j->first[k]==j->first[col]) ++nrcur;
			//space
			if(nrspace>0||j->first[w]=='N') {
				string next=j->first; int nval=j->second;
				if(next[col]=='+') next[col]='*',++nval; if(col-1>=0&&next[col-1]=='+') next[col-1]='*',++nval;
				if(col-1>=0&&isdigit(next[col-1])) {
					if(isdigit(next[col])) REP(k,w) if(k!=col&&next[k]==next[col]) next[k]=next[col-1];
					next[col]=next[col-1];
				} else if(!isdigit(next[col])) {
					next[col]='9';
				}
				if((row==0||row==h-1||col==0||col==w-1)&&next[w]=='N') next[w]='Y';
				norm(next);
				if(!best[i+1].count(next)||nval>best[i+1][next]) best[i+1][next]=nval,prev[i+1][next]=j->first;
			}
			//bed
			if(!isdigit(j->first[col])||nrcur>1||nrspace==1&&j->first[w]=='Y') {
				string next=j->first; int nval=j->second;
				if(next[col]=='+'||row+1>=h&&col-1>=0&&next[col-1]=='+') continue;
				if(isdigit(next[col])||col-1>=0&&isdigit(next[col-1])) next[col]='*',++nval; else next[col]='+';
				norm(next);
				if(!best[i+1].count(next)||nval>best[i+1][next]) best[i+1][next]=nval,prev[i+1][next]=j->first;
			}
		}
	}

	vector<string> ret(h,string(w,'?'));
	string bestend; int bestval=-1;
	for(map<string,int>::iterator j=best[h*w].begin();j!=best[h*w].end();++j) if(j->first[w]!='N') {
		bool ok=true; REP(k,w) if(j->first[k]=='1') ok=false; if(!ok) continue;
		if(j->second>bestval) bestend=j->first,bestval=j->second;
	}

	string cur=bestend;
	for(int i=h-1;i>=0;--i) {
		REP(j,w) ret[i][j]=cur[j];
		for(int j=w-1;j>=0;--j) cur=prev[i*w+j+1][cur];
	}

	bool haveentry=false; REP(i,h) REP(j,w) {
		if(isdigit(ret[i][j])) if((i==0||i==h-1||j==0||j==w-1)&&!haveentry) ret[i][j]='E',haveentry=true; else ret[i][j]='.'; else ret[i][j]='B';
	}
	
	if(swapped) { vector<string> tmp=ret; ret=vector<string>(w,string(h,'?')); REP(i,h) REP(j,w) ret[j][i]=tmp[i][j]; swap(h,w); }
	
	REP(i,h) printf("%s\n",ret[i].c_str());
}

int main() {
	int n; scanf("%d",&n); FORE(i,1,n) run();
	return 0;
}
