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

set<string> words;
vector<string> vowels, consonants, ans;
int v, c;

void backtrack(string so_far, int used_c, bool last_vowel){
  //printf("so_far = %s, used_c=%X, last_vowel=%d\n", so_far.c_str(), used_c, last_vowel);
  if (words.size() >= 100) return;
  if (used_c == (1<<c)-1){
    if (words.count(so_far) == 0){
      words.insert(so_far);
    }
  }

  if (last_vowel == false)
    for (int i=0; i<v; ++i){
      backtrack(so_far + vowels[i], used_c, true);
    }
  else{
    for (int i=0; i<c; ++i){
      if (used_c & (1<<i)){
        continue;
      }
      backtrack(so_far + consonants[i], used_c | (1<<i), false);
    }
  }
}

int main(){
  int DS = 1;
  while (cin >> v && v){

    vowels = vector<string>(v);
    for (int i=0; i<v; ++i){
      cin >> vowels[i];
    }
    cin >> c;
    consonants = vector<string>(c);
    for (int i=0; i<c; ++i){
      cin >> consonants[i];
    }

    unsigned long long count = 0, inside = 1;
    for (int i=1; i<=c; ++i){
      inside *= i*v;
    }
    inside /= v;

    count = inside + 2*v*inside + v*v*inside;

    if (DS > 1) cout << endl;
    cout << "Data set " << DS++ << ":" << endl;

    cout << count << " words." << endl;

    sort(vowels.begin(), vowels.end());
    sort(consonants.begin(), consonants.end());
    words.clear();
    for (int i=0, j=0; i<v || j<c; ){
      if (i < v && j < c){
        if (vowels[i][0] < consonants[j][0]){
          backtrack(vowels[i], 0, true);
          ++i;
        }else{
          backtrack(consonants[j], (1<<j), false);
          ++j;
        }
      }else{
        if (i < v){
          backtrack(vowels[i], 0, true);
          ++i;
        }else{
          backtrack(consonants[j], (1<<j), false);
          ++j;
        }
      }
    }

    int i=0;
    for (set<string>::iterator j=words.begin(); j!=words.end(); ++i, ++j){
      if (i % 10 > 0) cout << " ";
      if (i > 0 && i % 10 == 0) cout << endl;
      cout << *j;
    }
    cout << endl;
  }
  return 0;
}
