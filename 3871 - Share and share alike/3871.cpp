#include <iostream>
#include <iterator>
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
  int n, G=1;
  while (cin >> n && n){
    vector<int> nuevo(n), viejo(n);
    for (int i=0; i<n; ++i) cin >> nuevo[i];
    int l, r, m;
    cin >> l >> m >> r;
    int sum = l+r+m, repeat;
    cin >> repeat;
    while (repeat--){
      viejo = nuevo;
      nuevo = vector<int>(n, 0);
      for (int i=0; i<n; ++i){
        nuevo[(i+n-1)%n] += (viejo[i]*l)/sum;
        nuevo[(i+1)%n] += (viejo[i]*r)/sum;
        nuevo[i] += viejo[i] - (viejo[i]*l)/sum - (viejo[i]*r)/sum;

      }

      /*
      cout << "Viejo es: " << endl;
      copy(viejo.begin(), viejo.end(), ostream_iterator<int>(cout, " "));
      cout << endl;

      cout << "Nuevo es: " << endl;
      copy(nuevo.begin(), nuevo.end(), ostream_iterator<int>(cout, " "));
      cout << endl;
      */

    }
    cout << "Game " << G++ << endl;
    cout << nuevo[0];
    for (int i=1; i<n; ++i){
      cout << " " << nuevo[i];
    }
    cout << endl << endl;
  }
  return 0;
}
