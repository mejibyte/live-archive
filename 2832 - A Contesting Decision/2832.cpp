#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

struct team{
  string name;
    ll subs[4];
  ll times[4];
    ll penalty;
  ll solved;
    bool operator < (const team &t) const {
      if (solved > t.solved) return true;
      if (solved < t.solved) return false;
      return penalty < t.penalty;
    }
};

int main(){
    int n;
    cin >> n;
    team t[n];
    for (int i=0; i<n; ++i){
        cin >> t[i].name;
        t[i].penalty = t[i].solved = 0;
        for (int j=0; j<4; ++j){
            cin >> t[i].subs[j];
            cin >> t[i].times[j];
            if (t[i].times[j]){
                t[i].penalty += t[i].times[j];
                t[i].penalty += (t[i].subs[j]-1)*20;
                t[i].solved++;
            }
        }
    }
    sort(t, t+n);
    cout << t[0].name << " " << t[0].solved << " " << t[0].penalty << endl;
    return 0;
}
