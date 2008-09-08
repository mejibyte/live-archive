/*
  Accepted, cleaner version
 */
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


/*
  n = The number we are visiting right now.
  so_far = List of all numbers we have visited before reaching to n.
  ans = where the final answer will be stored.
 */
void backtrack(int n, vector<int> &so_far, vector<int> &ans){
  vector<int> seq;
  int x = n;
  while (x){
    seq.insert(seq.begin(), x%10);
    x /= 10;
  }
  so_far.push_back(n);

  reverse(seq.begin(), seq.end());
  bool hasSubfactor = false;
  for (int mask = 1; mask < (1 << seq.size()) -1; ++mask){
    /*
      mask tells me which digits should be removed and which should be kept.
      1 = Delete
      0 = Keep
    */

    int firstDigit = -1;
    int subfactor = 0;
    for (int i=seq.size()-1; i>=0; --i){
      if (mask & (1 << i)){
        subfactor *= 10;
        subfactor += seq[i];
        if (firstDigit == -1) firstDigit = seq[i];
      }
    }
    if (firstDigit == 0 || (n % subfactor) || subfactor <= 1) continue;

    hasSubfactor = true;
    int new_n = 0;
    for (int i=seq.size()-1; i>=0; --i){
      if (!(mask & (1 << i))){
        new_n *= 10;
        new_n += seq[i];
      }
    }
    backtrack(new_n, so_far, ans);
  }

  if (!hasSubfactor)
    /*
      Possible solution found.
     */
    if (so_far.size() > ans.size() || (so_far.size() == ans.size() && so_far < ans)){
      ans = so_far;
    }

  /*
    Delete the only change we did on so_far, in order to keep it exactly equal for
    the parent function that called this one.
   */
  so_far.erase(so_far.end()-1);
}

int main(){
  int n;
  while (cin >> n && n){
    vector<int> ans, so_far;
    backtrack(n, so_far, ans);

    cout << ans[0];
    for (int i=1; i<ans.size(); ++i){
      cout << " " << ans[i];
    }
    cout << endl;
  }
  return 0;
}
