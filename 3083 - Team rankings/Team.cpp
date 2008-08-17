#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;


int dif(string a, string b){
  set<string> s;
  int ans = 0;
  for (int i=0; i<4; ++i){
    for (int j=i+1; j<5; ++j){
      s.insert(a.substr(i, 1) + a.substr(j, 1));
      //cout << "Inserted " << (a.substr(i, 1) + a.substr(j, 1)) << endl;
    }
  }

  for (int i=0; i<4; ++i){
    for (int j=i+1; j<5; ++j){
      if (s.count(b.substr(i, 1) + b.substr(j, 1)) == 0){
	ans++;
	//cout << "counted " << b.substr(i, 1) + b.substr(j, 1) << endl;
      }
    }
  }
  return ans;
}





int main(){
  int n;
  //cout << dif("ADCBE", "ABDCE") << endl;
  //cout << dif("ADCBE", "BACDE") << endl;
  while (cin >> n && n){
    vector<string> p(n);
    for (int i = 0; i<n; ++i){
      cin >> p[i];
    }
    
    string posible = "ABCDE", ans;
    int mini = (1<<30);
    do{
      int score = 0;
      for (int i=0; i<n; ++i){
	score += dif(posible, p[i]);
      }
      
      if (score < mini){
	ans = posible;
	mini = score;
      }
    }while(next_permutation(posible.begin(), posible.end()));
    cout << ans << " is the median ranking with value " << mini << "." << endl;
  }
}


