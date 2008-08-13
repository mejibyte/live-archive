/*
  Problem: 2836 - Helping Florida

  Andrés Mejía-Posada

  Accepted.
 */
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

bool round(vector< vector<string> > &b, set<string> &e, int candidates){
  int totalVotes = 0;
  map<string, int> v;

  //Contar votos de cada balota
  for (int i=0; i<b.size(); ++i){
    v[b[i][0]]++;
    totalVotes++;
  }

  //Meter todas las parejas persona-votos en un vector
  vector< pair<int, string> > to_eliminate;
  for (map<string, int>::iterator i=v.begin(); i != v.end(); ++i){
    if (i->second > (totalVotes/2)){
      cout << i->first << " won" << endl;
      return true;
    }
    to_eliminate.push_back(make_pair(i->second, i->first));
  }
  sort(to_eliminate.begin(), to_eliminate.end());
  //Hacer que el vector tenga solo los tipitos con menos votos
  while (to_eliminate.size() > 1 && to_eliminate.back().first > to_eliminate.front().first){
    to_eliminate.erase(to_eliminate.end()-1);
  }
  if (to_eliminate.size() == candidates - e.size() && to_eliminate.size() > 1){
    //tie
    cout << "it is a tie between " << to_eliminate.front().second;
    for (int i=1; i<to_eliminate.size(); ++i){
      cout << " and " << to_eliminate[i].second;
    }
    cout << endl;
    return true;
  }

  if (to_eliminate.size() == 1 && candidates - e.size() == 1){
    //winner
    cout << to_eliminate[0].second << " won" << endl;
    return true;
  }

  //Eliminar los que quedaron de ultimos
  for (int i=0; i<to_eliminate.size(); ++i){
    e.insert(to_eliminate[i].second);
  }

  //Retabular balotas
  for (int i=0; i<b.size(); ++i){

    while (b[i].size() && e.count(b[i][0])){
      b[i].erase(b[i].begin());
    }
    if (b[i].size() == 0){
      b.erase(b.begin()+i);
      --i;
    }

  }
  return false;
}

int main(){
  int n, b;
  while (scanf("%d %d\n", &n, &b) == 2 && (n+b)){
    vector< vector<string> > ballots(b);
    for (int i=0; i<b; ++i){
      string line;
      getline(cin, line);
      stringstream sin(line);
      while (sin >> line) ballots[i].push_back(line);
    }
    set<string> eliminated;
    while (!round(ballots, eliminated, n));
  }
  return 0;
}
