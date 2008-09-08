#include <cstdio>
#include <vector>
#include <map>
#include <queue>
#include <string>
using namespace std;

#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n) FOR(i,0,n)
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n) FORE(i,0,n)
#define REPSZ(i,v) REP(i,SZ(v))
#define FORSZ(i,a,v) FOR(i,a,SZ(v))
typedef pair<int,int> PII;
typedef vector<int> VI;


typedef struct Component {
	string name; int price,quality;
	Component(string name,int price,int quality):name(name),price(price),quality(quality) {}
} Component;
bool operator<(const Component &a,const Component &b) {
	if(a.price!=b.price) return a.price<b.price;
	if(a.quality!=b.quality) return a.quality>b.quality;
	return a.name<b.name;
}

int n,budget;

void run() {
	scanf("%d%d",&n,&budget);
	map<string,vector<Component> > type2components;
	REP(i,n) {
		char type[52],name[52]; int price,quality;
		scanf("%s%s%d%d",type,name,&price,&quality);
		type2components[type].PB(Component(name,price,quality));
	}
	vector<string> types; vector<vector<Component> > components;
	for(map<string,vector<Component> >::iterator i=type2components.begin();i!=type2components.end();++i) {
		string type=i->first; vector<Component> curcomponents=i->second;
		sort(curcomponents.begin(),curcomponents.end());
		int pos=1;
		REPSZ(j,curcomponents) if(curcomponents[j].quality>curcomponents[pos-1].quality) curcomponents[pos++]=curcomponents[j];
		curcomponents.erase(curcomponents.begin()+pos,curcomponents.end());
		types.PB(type); components.PB(curcomponents);
	}
//	REPSZ(i,types) { printf("%s:\n",types[i].c_str()); REPSZ(j,components[i]) printf("%s %d %d\n",components[i][j].name.c_str(),components[i][j].price,components[i][j].quality); }
	
	priority_queue<PII> q;
	int quality=0,price=0;
	REPSZ(i,types) q.push(MP(-components[i][0].quality,i)),price+=components[i][0].price;
	VI cur(SZ(types),0);
	while(true) {
		quality=-q.top().first;
		bool ok=true; VI improve; int nprice=price;
		while(!q.empty()&&-q.top().first==quality) {
//			printf("%d %s\n",-q.top().first,types[q.top().second].c_str());
			int curtype=q.top().second; q.pop();
			if(cur[curtype]+1>=SZ(components[curtype])) {
//				printf("no more components for %s %d\n",types[curtype].c_str(),quality);
				ok=false; break;
			}
			nprice+=components[curtype][cur[curtype]+1].price-components[curtype][cur[curtype]].price;
			improve.PB(curtype);
		}
		if(!ok||nprice>budget) break;
		REPSZ(i,improve) {
			int curtype=improve[i];
			price+=components[curtype][cur[curtype]+1].price-components[curtype][cur[curtype]].price;
			++cur[curtype];
			q.push(MP(-components[curtype][cur[curtype]].quality,curtype));
		}
	}
	
	printf("%d\n",quality);
//	printf("%d %d\n",quality,price);
//	REPSZ(i,types) printf("%s %s %d %d\n",types[i].c_str(),components[i][cur[i]].name.c_str(),components[i][cur[i]].price,components[i][cur[i]].quality);
}

int main() {
	int n; scanf("%d",&n); FORE(i,1,n) run();
	return 0;
}
