/*
  [NWERC'07] ASSEMBLE
  by: Jan Kuipers
*/

using namespace std;

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

struct component {
  int qual, price;
  component (int qual, int price): qual(qual), price(price) {}
};

bool operator < (component a, component b) {
  if (a.qual !=b.qual) return a.qual <b.qual;
  return a.price>b.price;
}

int main () {

  int runs;
  cin>>runs;
  while (runs--) {

    int N, C=0, budget;
    cin>>N>>budget;

    map<string,int> typenum;
    vector<vector<component> > comp;
    vector<set<component> > comp2;
    
    for (int i=0; i<N; i++) {
      string type,name;
      int price,qual;
      cin>>type>>name>>price>>qual;

      if (!typenum.count(type)) {
	typenum[type] = C++;
	comp.push_back(vector<component>());
      }

      comp[typenum[type]].push_back(component(qual,price));
    }

    for (int i=0; i<C; i++) {
      sort (comp[i].begin(), comp[i].end());
      int idx=1;
      for (int j=1; j<comp[i].size(); j++) {
	while (idx>0 && comp[i][j].price<=comp[i][idx-1].price) idx--;
	comp[i][idx++] = comp[i][j];
      }
      
      comp2.push_back(set<component>(comp[i].begin(),comp[i].begin()+idx));
    }
      
    int minqual=0, maxqual=INT_MAX;
    for (int i=0; i<C; i++) maxqual<?=comp[i].back().qual;

    while (minqual != maxqual) {
      int tryqual = (minqual+maxqual+1)/2;
      int price = 0;
      for (int i=0; i<C; i++)
	price += comp2[i].lower_bound(component(tryqual,INT_MAX))->price;
      
      if (price>budget)
	maxqual = tryqual-1;
      else 
	minqual = tryqual;
    }
    
    cout<<minqual<<endl;
  }

  return 0;
}
