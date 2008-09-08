#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

#define V(x) cout << #x " is: "; copy(x.begin(), x.end(), ostream_iterator<int>(cout, " ")); cout << endl
#define D(x) cout << #x " is: " << x << endl

using namespace std;

void buildSubsequences(const vector<int> &seq, int n, int i, vector<int> &ans, const int &originalNumber){
  if (i == seq.size()) return;

  n *= 10;
  n += seq[i];
  if (n == originalNumber) return;
  if (n > 1) ans.push_back(n);
  for (int j=i+1; j<seq.size(); ++j){
    buildSubsequences(seq, n, j, ans, originalNumber);
  }
}


void buildSubfactors(vector<int> &seq, int n, vector<int> &ans){
  if (n < 10) return; //no puedo quitar ningún dígito

  //construir la lista de subsecuencias
  for (int i=0; i<seq.size(); ++i){
    if (seq[i] != 0){
      buildSubsequences(seq, 0, i, ans, n);
    }
  }

  for (vector<int>::iterator i=ans.begin(); i != ans.end(); ++i){
    if ((n % (*i)) != 0) i = ans.erase(i)-1;
  }
  sort(ans.begin(), ans.end());
  vector<int>::iterator final = unique(ans.begin(), ans.end());
  ans.resize(final - ans.begin());
}

void backtrack(int n, vector<int> so_far, vector<int> &ans){
  vector<int> seq;
  int x = n;
  while (x){
    seq.insert(seq.begin(), x%10);
    x /= 10;
  }
  //V(seq);
  so_far.push_back(n);
  vector<int> subfactors;
  buildSubfactors(seq, n, subfactors);
  D(n);
  V(subfactors);
  if (subfactors.size() == 0){
    if (so_far.size() > ans.size() || (so_far.size() == ans.size() && so_far < ans)){
      ans = so_far;
    }
  }else{
    //para cada subfactor, quitar todos sus digitos de seq, hacer un numero con eso y recurrir
    for (int i=0; i<subfactors.size(); ++i){
      //D(i);
      vector<int> t = seq;
      vector<int> subdigits;
      int x = subfactors[i];
      while (x){
        subdigits.push_back(x%10);
        x /= 10;
      }
      //V(subdigits);
      for (int j=0; j<subdigits.size(); ++j){
        for (int k=0; k<t.size(); ++k){
          if (t[k] == subdigits[j]){
            t.erase(t.begin()+k);
            --k;
          }
        }
      }
      //V(t);
      int new_n = 0;
      for (int i=0; i<t.size(); ++i){
        new_n *= 10;
        new_n += t[i];
      }
      //D(n);
      //D(new_n);
      backtrack(new_n, so_far, ans);
    }
  }
}

int main(){
  int n;
  while (cin >> n && n){
    vector<int> ans;
    backtrack(n, vector<int>(), ans);
    //V(ans);
    cout << ans[0];
    for (int i=1; i<ans.size(); ++i){
      cout << " " << ans[i];
    }
    cout << endl;
  }
  return 0;
}
