/*
  Problema: Electronic document security

  Equipo: Factor común (team18)
  Sebastián Arcila Valenzuela
  Daniel Restrepo Montoya
  Andrés Mejía Posada

*/
#include <iostream>
#include <cassert>
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <vector>
#include <string>
#include <string.h>
#include <set>
#include <map>
#include <stack>
#include <list>
#include <queue>
#include <sstream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <iterator>

using namespace std;

string make_string(const set<char> &p){
  string ans = "";
  for (set<char>::iterator i = p.begin(); i != p.end(); ++i){
    ans += *i;
  }
  return ans;
}

int main() {
  int caso = 1;
  string line;
  while (getline(cin, line) && line != "#"){
    cout << caso++<<":";
    //split
    for (int i=0; i<line.size(); ++i){
      if (line[i] == ',') line[i] = ' ';
    }
    vector<string> log;
    stringstream sin(line);
    string s;
    while (sin >> s){
      log.push_back(s);
    }

    /*
      cout << "log es: " << endl;
      copy(log.begin(), log.end(), ostream_iterator<string>(cout, "\n"));
    */

    map<char, set<char> > m;
    for (int i=0; i<log.size(); ++i){
      int op_pos = -1;
      for (int j=0; j<log[i].size(); ++j){
        if (log[i][j] == '+' || log[i][j] == '-' || log[i][j] == '='){
          op_pos = j;
          break;
        }
      }
      assert(op_pos != -1);

      string entidades = log[i].substr(0, op_pos);
      string permisos = log[i].substr(op_pos+1, log[i].size());
      char op = log[i][op_pos];

      /*
        cout << "Entidades es " << entidades << endl;
        cout << "Permisos es " << permisos << endl;
        cout << "op es " << op << endl;
      */

      for (int j=0; j<entidades.size(); ++j){
        set<char> &perm = m[entidades[j]];
        if (op == '=') perm.clear();
        for (int k=0; k<permisos.size(); ++k){
          if (op == '+' || op == '='){
            perm.insert(permisos[k]);
          }else if (op == '-'){
            set<char>::iterator it = perm.find(permisos[k]);
            if (it != perm.end()){
              perm.erase(it);
            }
          }
        }
      }
    }
    vector<pair<char, string> > ans;
    for (char e='A'; e<='Z'; ++e){
      string s = make_string(m[e]);
      if (s != ""){
        ans.push_back(make_pair(e, s));
      }
    }
    /*
      for (int i=0; i<ans.size(); ++i){
      cout << "ans["<<i<<"] = " << ans[i].first << " " << ans[i].second << endl;
      }
    */
    int i=0, n = ans.size();
    while (i<n){
      string s = ""; s += ans[i].first;
      int j=i+1;
      while (j < n && ans[i].second == ans[j].second){
        s += ans[j].first;
        ++j;
      }
      cout << s << ans[i].second;
      i = j;
    }
    cout << endl;
  }
  return 0;
}
