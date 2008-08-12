#include <iostream>
#include <set>

using namespace std;


int main(){
  int x;
  while (cin >> x && x != -1){
    set<int> v;
    v.insert(x);
    while (cin >> x && x != 0) v.insert(x);
    int answer = 0;
    for (set<int>::iterator i = v.begin(); i != v.end(); ++i)
      answer += (v.count(*i*2));
    cout << answer << endl;
  }

  return 0;
}
