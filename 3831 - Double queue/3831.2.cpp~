/*
  Problem: 3831 - Double queue (ACM-ICPC Live archive)

  Andrés Mejía-Posada

  Accepted
 */
#include <iostream>
#include <set>

using namespace std;

int main(){
  int x;
  set<pair<int, int> > q; //first - priority, second - client
  while (cin >> x && x){
    if ((x == 2 || x == 3) && q.size() == 0){
      cout << 0 << endl;
    }else if (x == 1){
      int k, p;
      cin >> k >> p;
      q.insert(make_pair(p, k));
    }else if (x == 2){
      set<pair<int, int> >::iterator i = q.end();
      --i;
      cout << i->second << endl;
      q.erase(i);
    }else if (x == 3){
      cout << q.begin()->second << endl;
      q.erase(q.begin());
    }else while (true) cout << "error ";
  }
  return 0;
}
