using namespace std;

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>

vector<int> payout;

const char rank[14] = "23456789TJQKA";
const char suit[5]  = "cdhs";

vector<long long> hands, allhands;
vector<int> allvalues;

struct foo {
	long long sumpay, nsum;

	foo() { sumpay = 0; nsum = 0; }
};

vector< map<long long,foo> > sums;

long long str2card(char *str)
{
	int r, s;
	for(r=0; r<13; r++) if ( rank[r]==str[0] ) break;
	for(s=0; s<4;  s++) if ( suit[s]==str[1] ) break;
	if ( r>=13 || s>=4 ) abort();
	return 4*r+s;
}

void printhand(long long h)
{
	for(int j=0; j<52; j++)
		if ( h&(1LL<<j) ) printf("%c%c ",rank[j/4],suit[j%4]);
	printf("\n");
}

int value(long long h)
{
	vector<int> nrank(13,0);
	vector<int> nsuit(4,0);
	vector<int> nkind(6,0);

	for(int i=0; i<52; i++)
		if ( h&(1LL<<i) ) {
			nrank[i/4]++;
			nsuit[i%4]++;
		}
	for(int i=0; i<13; i++) nkind[nrank[i]]++;

	int flush = 0;
	for(int i=0; i<4; i++) if ( nsuit[i]==5 ) { flush = 1; break; }
	
	int straight = 0;
	for(int i=0; i<9; i++) {
		int j;
		for(j=i; j<i+5; j++) if ( !nrank[j] ) break;
		if ( j>=i+5 ) { straight = 1; break; }
		if ( i==0 && j>=4 && nrank[12] ) { straight = 1; break; }
	}

	// (royal) straight flush
	if ( flush && straight ) {
		if ( nrank[11] && nrank[12] ) return 9;
		return 8;
	}

	// four of a kind
	if ( nkind[4]==1 ) return 7;

	// full house
	if ( nkind[3]==1 && nkind[2]==1 ) return 6;
	
	if ( flush       ) return 5;
	if ( straight    ) return 4;
	if ( nkind[3]==1 ) return 3;
	if ( nkind[2]==2 ) return 2;
	if ( nkind[2]==1 ) return 1;

	return 0;
}

void dfs(long long h, int todo, int last)
{
	if ( todo==0 ) {
		allhands.push_back(h);
		allvalues.push_back(value(h));
		return;
	}

	for(int i=last+1; i<52; i++) dfs(h | (1LL<<i),todo-1,i);
}

int main()
{
	int run, nruns;

	scanf("%d\n",&nruns);

	payout = vector<int>(10,0);

	allhands.reserve (2598960); // 52 choose 5
	allvalues.reserve(2598960);
	
	dfs(0,5,-1);

//	fprintf(stderr,"found %d hands\n",allhands.size());
	
	for(run=0; run<nruns; run++) {

		for(int i=0; i<9; i++) scanf("%d",&payout[i+1]);
	
		int n;
		scanf("%d\n",&n);
		hands = vector<long long>(n,0);
		
		sums = vector< map<long long, foo> >(n);

		for(int i=0; i<n; i++) {
			for(int j=0; j<5; j++) {
				char tmp[10];
				scanf("%s",tmp);
				hands[i] |= 1LL<<str2card(tmp);
			}
		}

		for(int i=0; i<allhands.size(); i++) {
			long long h = allhands[i];
			int v = payout[allvalues[i]];
			
			for(int k=0; k<hands.size(); k++) {
				long long m = hands[k]&h;
				sums[k][m].sumpay += v;
				sums[k][m].nsum++;
			}
		}

		for(int k=0; k<hands.size(); k++) {
			double best = 0;
			for(map<long long, foo>::iterator it=sums[k].begin(); it!=sums[k].end(); ++it) {
				best >?= (double)(it->second.sumpay) / it->second.nsum;
			}
			printf("%.8lf\n",best);
		}

	}
	
	return 0;
}
