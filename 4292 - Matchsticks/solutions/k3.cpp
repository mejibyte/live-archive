// in the order of one millions ops per query
// took about 1.5 hour and has become bit of a mess
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

#define MP make_pair
#define PB push_back
#define SZ(v) ((int)(v).size())
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n) FOR(i,0,n)
#define REPSZ(i,v) REP(i,SZ(v))
#define ALL(v) (v).begin(),(v).end()
#define SORT(v) sort(ALL(v))

typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<PII> VPII;



const int aNONE=0;
const int aONEPAIR=1;
const int aTWOPAIR=2;
const int aTHREEKIND=3;
const int aSTRAIGHT=4;
const int aFLUSH=5;
const int aFULLHOUSE=6;
const int aFOURKIND=7;
const int aSTRAIGHTFLUSH=8;
const int aROYALFLUSH=9;

const int bNONE=1;
const int bSTRAIGHT=2;
const int bROYALSTRAIGHT=3;
const int bONEPAIR=4;
const int bTWOPAIR=5;
const int bTHREEKIND=6;
const int bFULLHOUSE=7;
const int bFOURKIND=8;




int pay[10];

int nq;
int startrank[5],startsuit[5];

int memcalc[14][14][14][14][14][9];
int mem[14][14][14][14][9];
int* go(int runnr,VI ranks,VI &rankleft) {
	SORT(ranks);
	if(SZ(ranks)<5) {
		int* ret=mem[SZ(ranks)>=1?ranks[0]:13][SZ(ranks)>=2?ranks[1]:13][SZ(ranks)>=3?ranks[2]:13][SZ(ranks)>=4?ranks[3]:13];
		if(ret[0]!=runnr) {
			ret[0]=runnr; FOR(i,1,9) ret[i]=0;
			REPSZ(i,rankleft) if(rankleft[i]>0) {
				rankleft[i]--; ranks.PB(i);
				int* cur=go(runnr,ranks,rankleft);
				rankleft[i]++; ranks.pop_back();
				FOR(j,1,9) ret[j]+=rankleft[i]*cur[j];
			}
		}
		return ret;
	} else {
		int* ret=memcalc[SZ(ranks)>=1?ranks[0]:13][SZ(ranks)>=2?ranks[1]:13][SZ(ranks)>=3?ranks[2]:13][SZ(ranks)>=4?ranks[3]:13][SZ(ranks)>=5?ranks[4]:13];
		if(ret[0]==0) {
			ret[0]=1; FOR(i,1,9) ret[i]=0;
			VPII cnt; REP(i,5) if(SZ(cnt)==0||ranks[i]!=cnt.back().second) cnt.PB(MP(1,ranks[i])); else cnt.back().first++; SORT(cnt); reverse(ALL(cnt));
			switch(cnt[0].first) {
				case 1: ret[ranks[0]==0&&ranks[1]==9?bROYALSTRAIGHT:ranks[4]==ranks[0]+4?bSTRAIGHT:bNONE]++; break;
				case 2: ret[cnt[1].first==2?bTWOPAIR:bONEPAIR]++; break;
				case 3: ret[cnt[1].first==2?bFULLHOUSE:bTHREEKIND]++; break;
				case 4: ret[bFOURKIND]++; break;
			}
		}
		return ret;
/*		printf("gone:");REPSZ(i,ranks) printf(" %d",ranks[i]);
		printf(" (left "); REPSZ(i,rankleft) printf("%d%c",rankleft[i],i==SZ(rankleft)-1?')':',');
		printf(" =>"); FOR(i,1,9) printf(" %d",ret[i]);
		puts(""); */
	}
}

int readRank() { char c; scanf(" %c",&c); return string("A23456789TJQK").find(c); }
int readSuit() { char c; scanf(" %c",&c); return string("cdhs").find(c); }


int runnr;
void run() {
	pay[0]=0; FOR(i,1,10) scanf("%d",&pay[i]);
	scanf("%d",&nq);
	REP(q,nq) {
		REP(i,5) { startrank[i]=readRank(); startsuit[i]=readSuit(); }
		double ret=0;
		REP(keep,1<<5) {
			VI res(10,0);
			FOR(suit,-1,4) {
				VI ranks(0),rankleft(13,suit==-1?4:1);
				bool ok=true; REP(i,5) if(keep&(1<<i)) if(suit!=-1&&startsuit[i]!=suit) { ok=false; break; } else ranks.PB(startrank[i]); if(!ok) continue;
				REP(i,5) if(suit==-1||startsuit[i]==suit) --rankleft[startrank[i]];
				int *cnt=go(runnr++,ranks,rankleft);
//				printf("\t\t%x,%d:",keep,suit); FOR(i,1,9) printf(" %d",cnt[i]); puts("");
				FOR(i,1,9) if(cnt[i]>0) switch(i) {
					case bNONE: res[aNONE]+=(suit!=-1?-1:+1)*cnt[i]; if(suit!=-1) res[aFLUSH]+=cnt[i]; break;
					case bSTRAIGHT: res[aSTRAIGHT]+=(suit!=-1?-1:+1)*cnt[i]; if(suit!=-1) res[aSTRAIGHTFLUSH]+=cnt[i]; break;
					case bROYALSTRAIGHT: res[aSTRAIGHT]+=(suit!=-1?-1:+1)*cnt[i]; if(suit!=-1) res[aROYALFLUSH]+=cnt[i]; break;
					case bONEPAIR: assert(suit==-1); res[aONEPAIR]+=cnt[i]; break;
					case bTWOPAIR: assert(suit==-1); res[aTWOPAIR]+=cnt[i]; break;
					case bTHREEKIND: assert(suit==-1); res[aTHREEKIND]+=cnt[i]; break;
					case bFULLHOUSE: assert(suit==-1); res[aFULLHOUSE]+=cnt[i]; break;
					case bFOURKIND: assert(suit==-1); res[aFOURKIND]+=cnt[i]; break;
				}
			}
			ll num=0,den=0; REP(i,10) num+=((ll)pay[i])*res[i],den+=res[i];
//			printf("\t %x => %lf (%lld/%lld)",keep,1.0*num/den,num,den); puts(""); //REP(i,10) printf(" %d",res[i]); puts("");
			ret>?=1.0*num/den;
		}
		printf("%.14lf\n",ret);
	}
}

int main() {
	memset(memcalc,0,sizeof(memcalc));
	memset(mem,-1,sizeof(mem)); runnr=0;
	int n; scanf("%d",&n); REP(i,n) run();
	return 0;
}
