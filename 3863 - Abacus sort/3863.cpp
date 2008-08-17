#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

using namespace std;

int main(){
  bool first = true;
  int i, n;

  while (cin >> i){

    if (!first) cout << endl;
    first = false;

    vector<int> v(1, i);
    while (cin >> i && i != 0){
      v.push_back(i);
    }
    int n = v.size();


    /*
    for (int i=0; i<n; ++i){
      cout << v[i] << " ";
    }
    */

    bool ficha[n][55];
    memset(ficha, 0, sizeof ficha);
    for (int i=0; i<n; ++i){
      for (int j=0; j<v[i]; ++j){
        ficha[i][j] = true;
      }
    }
    int slided = 0;
    for (int i=0; i<n; ++i){
      for (int j=0; j<55; ++j){
        if (!ficha[i][j]){
          for (int k=i-1; k>=0; --k){
            if (ficha[k][j]){
              slided++;
              ficha[k][j] = false; //Para que no vuelva a contar la misma ficha
            }
          }
        }
      }
    }

    sort(v.begin(), v.end());
    int big = v.back();
    for (int i=0; i<n; ++i){
      for (int j=0; j<v[i]; ++j){
        cout << "X";
      }
      for (int j=v[i]; j<big; ++j){
        cout << "-";
      }
      cout << " > " << v[i] << endl;
    }
    cout << "A total of " << slided << " beads slid during the sort." << endl;

  }
  return 0;
}

