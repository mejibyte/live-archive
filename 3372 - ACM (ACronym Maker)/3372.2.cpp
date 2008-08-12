/*
  Solution to problem: 3372 - ACM (ACronym Maker)
  (From the ACM-ICPC Live archive around the world
  http://acm.uva.es/archive/nuevoportal/
  )

  Author: Andres Mejia-Posada
  http://blogaritmo.factorcomun.org
*/
#include <iostream>
#include <cassert>
#include <vector>
#include <sstream>
#include <map>
#include <string>
#include <set>

using namespace std;

int main(){
  int S;
  while (cin >> S && S){
    set<string> bad;
    while (S--){
      string s;
      cin >> s;
      bad.insert(s);
    }

    string acronym, line;
    vector<string> w;
    getline(cin, line);
    while (getline(cin, line) && line.find("LAST CASE") != 0){
      //cout << "line es: " << line << endl;
      w.clear();
      stringstream sin(line);
      sin >> acronym;
      for (int i=0; i<acronym.size(); ++i) acronym[i] = tolower(acronym[i]);
      string s;
      while (sin >> s)
        if (bad.count(s) == 0) w.push_back(s);

      /*cout << "acronym es: " << acronym << endl;
      cout << "words es: " << endl;
      for (int i=0; i<w.size(); ++i){
      cout << w[i] << endl;
      }*/

      /*
        dp[n][i][j] = La cantidad de maneras diferentes que puedo acomodar las primeras n letras
        del acrónimo scando al menos una de cada palabra y terminando en la letra j-ésima de la
        palabra i-ésima
       */
      int dp[acronym.size()][w.size()][150];
      for (int n=0; n<acronym.size(); ++n)
        for (int i=0; i<w.size(); ++i)
          for (int j=0; j<w[i].size(); ++j)
            dp[n][i][j] = 0;

      assert(w.size() > 0);
      dp[0][0][0] = (w[0][0] == acronym[0]);
      for (int j=1; j<w[0].size(); ++j)
        dp[0][0][j] = dp[0][0][j-1] + (w[0][j] == acronym[0]);

      //Let's dance
      for (int n=1, A=acronym.size(); n<A; ++n){
        for (int i=0, W=w.size(); i<W; ++i){
          int t = 0; //Tiene un acumulado que se suma al resto de la palabra
          for (int j=0, Wi=w[i].size(); j<Wi; ++j){
            dp[n][i][j] += t;
            if (acronym[n] == w[i][j]){
              if (j > 0 && dp[n-1][i][j-1]){
                dp[n][i][j] += dp[n-1][i][j-1];
                t += dp[n-1][i][j-1];
              }if (i > 0 && dp[n-1][i-1][w[i-1].size()-1]){
                dp[n][i][j] += dp[n-1][i-1][w[i-1].size()-1];
                t += dp[n-1][i-1][w[i-1].size()-1];
              }
            }
          }
        }
      }
      int t = dp[acronym.size()-1][w.size()-1][w.back().size()-1];
      for (int i=0; i<acronym.size(); ++i) acronym[i] = toupper(acronym[i]);
      if (t)
        cout << acronym << " can be formed in " << t << " ways" << endl;
      else
        cout << acronym << " is not a valid abbreviation" << endl;
    }

  }
  return 0;
}
