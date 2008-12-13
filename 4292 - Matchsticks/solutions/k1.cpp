/*
  [NWERC'08] VIDEOPOKER
  by: Jan Kuipers
*/

using namespace std;

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

string ranks = "23456789TJQKA";
string suits = "cdhs";

vector<long long> cards;
vector<int> result;

int eval (long long mask) {

  vector<int> rank(13,0), suit(4,0);
  for (int i=0; i<52; i++) if (mask & (1LL<<i)) rank[i/4]++, suit[i%4]++;

  vector<int> cnt(5,0);
  for (int i=0; i<13; i++) cnt[rank[i]]++;
  
  int flush=0;
  for (int i=0; i<4; i++) if (suit[i]==5) flush=1;

  int straight=0;
  for (int i=0; i<9; i++)
    if (rank[i] && rank[i+1] && rank[i+2] && rank[i+3] && rank[i+4]) straight=1;
  if (rank[0] && rank[1] && rank[2] && rank[3] && rank[12]) straight=1;
  
  if (straight && flush && rank[11] && rank[12]) return 9;
  if (straight && flush) return 8;
  if (cnt[4]) return 7;
  if (cnt[3] && cnt[2]) return 6;
  if (flush) return 5;
  if (straight) return 4;
  if (cnt[3]) return 3;
  if (cnt[2]==2) return 2;
  if (cnt[2]) return 1;
  return 0;
}

void go (int dep, int from, long long mask) {

  if (dep==5) {
    cards.push_back(mask);
    result.push_back(eval(mask));
    return;
  }

  for (int i=from; i<52; i++) go(dep+1, i+1, mask | (1LL<<i));
}

int main () {

  go(0,0,0);
  
  int runs;
  cin>>runs;

  while (runs--) {

    vector<int> pay(10,0);
    for (int i=1; i<10; i++) cin>>pay[i];

    int Q;
    cin>>Q;

    for (int q=0; q<Q; q++) {

      long long hand = 0;
      for (int i=0; i<5; i++) {
	string s;
	cin>>s;
	hand |= 1LL << (4*ranks.find(s[0]) + suits.find(s[1]));
      }

      map<long long,long long> profit, nprofit;
      for (int i=0; i<cards.size(); i++) {
	profit[cards[i] & hand] += pay[result[i]];
	nprofit[cards[i] & hand]++;
      }
      
      double res=0;
      for (map<long long, long long>::iterator it = profit.begin(); it!=profit.end(); it++)
	res >?= 1.0 * it->second / nprofit[it->first];

      cout<<setprecision(10)<<res<<endl;
    }
  }

  return 0;
}
