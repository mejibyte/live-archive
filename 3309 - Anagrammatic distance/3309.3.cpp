/*
  Problema: Annagramatic distance

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

int dist(string &a, string &b){
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  int _a = a.size(), _b = b.size();
  bool used_a[_a], used_b[_b];
  memset(used_a, 0, sizeof used_a);
  memset(used_b, 0, sizeof used_b);
  for (int i=0; i<_a; ++i){
    assert(used_a[i] == false);
    for (int j=0; j<_b; ++j){
      if (a[i] == b[j] && !used_b[j]){
        used_a[i] = used_b[j] = true;
        break;
      }
    }
  }
  int ans = 0;
  for (int i=0; i<_a; ++i){
    if (!used_a[i]) ans++;
  }
  for (int j=0; j<_b; ++j){
    if (!used_b[j]) ans++;
  }
  return ans;
}


int main() {
  int n;
  cin >> n;
  string a, b;
  getline(cin, a);
  for (int i=1; i<=n && (cout << "Case #" << i << ": "); ++i){
    getline(cin, a);
    getline(cin, b);
    cout << dist(a, b) << endl;
  }
  return 0;
}
