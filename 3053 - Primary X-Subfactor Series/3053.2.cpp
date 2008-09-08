/*
  Accepted
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

#define V(x) cout << #x " is: "; copy(x.begin(), x.end(), ostream_iterator<int>(cout, " ")); cout << endl
#define D(x) cout << #x " is: " << x << endl

using namespace std;

void printBin(int i){
  unsigned int mask = 1 << 31;
  while (mask){
    cout << int((mask & i) > 0);
    mask >>= 1;
  }
}

void backtrack(int n, vector<int> &so_far, vector<int> &ans){
  vector<int> seq;
  int x = n;
  while (x){
    seq.insert(seq.begin(), x%10);
    x /= 10;
  }
  //V(seq);
  so_far.push_back(n);

  //D(n);
  reverse(seq.begin(), seq.end());
  //V(seq);
  bool hasSubfactor = false;
  for (int mask = 1; mask < (1 << seq.size()) -1; ++mask){
    //veamos si es subfactor
    int firstDigit = -1;
    int subfactor = 0;
    for (int i=seq.size()-1; i>=0; --i){
      if (mask & (1 << i)){
        subfactor *= 10;
        subfactor += seq[i];
        if (firstDigit == -1) firstDigit = seq[i];
      }
    }
    //printBin(mask); cout << " maps to " << subfactor << endl;
    //D(subfactor);
    //D(firstDigit);
    if (firstDigit == 0 || (n % subfactor) || subfactor <= 1) continue;
    //D(subfactor);
    hasSubfactor = true;
    int new_n = 0;
    for (int i=seq.size()-1; i>=0; --i){
      if (!(mask & (1 << i))){
        new_n *= 10;
        new_n += seq[i];
      }
    }
    //D(new_n);
    backtrack(new_n, so_far, ans);
  }


  //D(n);
  //D(hasSubfactor);
  if (!hasSubfactor)
    if (so_far.size() > ans.size() || (so_far.size() == ans.size() && so_far < ans)){
      ans = so_far;
    }

  //V(so_far);
  so_far.erase(so_far.end()-1);
}

int main(){
  int n;
  while (cin >> n && n){
    vector<int> ans, so_far;
    backtrack(n, so_far, ans);
    //V(ans);
    cout << ans[0];
    for (int i=1; i<ans.size(); ++i){
      cout << " " << ans[i];
    }
    cout << endl;
  }
  return 0;
}
