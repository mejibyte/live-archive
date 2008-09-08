/*
  Accepted
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct comp {
  long long p;
  long long q;
  bool operator<(const comp &c)const {
    if(q>c.q) return true;
    else if(q==c.q && p>c.p) return true;
    return false;
  }
};

int main() {
  int cases;
  cin >> cases;
  while(cases) {
    int c, b;
    long long qu = 1000000001;
    cin >> c >> b;
    vector<string> names;
    vector<vector<comp> > grid;
    for(int i =0; i<c; ++i) {
      string name,basura;
      long long p,q;
      comp co;
      cin >> name >> basura;
      cin >> co.p >> co.q;
      int j;
      for(j = 0; j<names.size(); ++j) {
        if(name==names[j]) break;
      }
      if(j==names.size()) {
        vector<comp> ctemp;
        names.push_back(name);
        ctemp.push_back(co);
        grid.push_back(ctemp);
      }
      else grid[j].push_back(co);
    }
    /*for(int i = 0; i<grid.size(); ++i) {
      for(int j =0; j<grid[i].size(); ++j) {
      cout << grid[i][j].p << " ";
      }
      cout << endl;
      }*/
    for(int i =0; i<grid.size(); ++i) {
      if(grid[i].size()==1) {
        b-=grid[i][0].p;
        if(grid[i][0].q<qu) qu = grid[i][0].q;
        grid.erase(grid.begin()+i);
        i--;

      }
      else sort(grid[i].begin(),grid[i].end());
    }
    vector<int> pos(grid.size());

    bool compre = false;
    while(!compre) {
      /*for(int i =0; i<pos.size(); ++i) {
        cout << pos[i] << " ";
        }
        cout << endl;*/
      long long suma = b;
      long long qt = 1000000001;
      for(int i =0; i<pos.size(); ++i) {
        suma = suma - grid[i][pos[i]].p;
        if(grid[i][pos[i]].q<qt) qt = grid[i][pos[i]].q;
      }
      if(suma>=0) {
        compre = true;
        if(qt<qu) qu = qt;
      }
      else {
        vector<int> puede(grid.size());
        for(int i =0; i<pos.size(); ++i) {
          for(int j = pos[i]+1; j<grid[i].size(); ++j) {
            if(grid[i][j].p<grid[i][pos[i]].p) {
              puede[i]=j;
              break;
            }
          }
        }
        /*for(int i =0; i<puede.size(); ++i) {
          cout << puede[i] << " ";
          }
          cout << endl;*/
        long long qtt = 0;
        int ipuede;
        for(int i =0; i<puede.size();++i) {
          if(puede[i]!=0) {
            if(grid[i][puede[i]].q>qtt) {
              qtt = grid[i][puede[i]].q;
              ipuede = i;
            }
          }
        }
        pos[ipuede] = puede[ipuede];
      }
    }
    cout << qu << endl;
    cases--;
  }
  return 0;
}
