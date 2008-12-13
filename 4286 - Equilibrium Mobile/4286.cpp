using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>

int deepest_level, parse_pos;
string s;
vector< pair<int, int> > v;

void expr(int level){ //parser mas rapido del mundo
 deepest_level = max(level, deepest_level);
 if (s[parse_pos] == '['){
   parse_pos++;
   expr(level+1);
   assert(s[parse_pos++] == ',');
   expr(level+1);
   assert(s[parse_pos++] == ']');
 }else{
   int value = 0;
   while (parse_pos < s.size() && isdigit(s[parse_pos])){
     value = 10*value + (s[parse_pos] - '0');
     parse_pos++;
   }
   v.push_back(make_pair(value, level));
 }
}

int main(){
 int casos;
 cin >> casos;
 getline(cin, s);
 while (casos--){
   getline(cin, s);

   deepest_level = 0;
   v.clear();

   parse_pos = 0;
   expr(0);

   for (int i=0; i<v.size(); ++i){
     v[i].second = (1 << (deepest_level - v[i].second));
     int g = __gcd(v[i].first, v[i].second);
     v[i].first /= g, v[i].second /= g;
   }
   //for (int i=0; i<v.size(); ++i){ printf("<%d, %d> ", v[i].first, v[i].second); } puts("");
   sort(v.begin(), v.end());

   int best = INT_MAX;

   const int n = v.size();
   for (int i=0, j=0; i < n && j < n; ){
     while (j < n && v[i] == v[j]) ++j;
     best = min(best, n - (j - i));
     i = j;
   }
   printf("%d\n", best);
 }
 return 0;
}

