#include <iostream>
#include <map>
#include <cassert>
#include <cstdio>
using namespace std;

int f(const int &n){
  if (n == 1) return 1;
  if (n % 2 == 0) return n/2;
  

  static map<int, int> cache;
  if (cache.count(n) > 0){
    return cache[n];
  }

  return cache[n] = f((n-1)/2) + f((n-1)/2 + 1);
  
}

int main(){
  int n;
  bool first = true;
  while (cin >> n && n != -1){
    if (!first){
      cout << endl;
    }
    first = false;
    assert(n >= 0);
    printf("f(%d) = %d\n", n, ((n % 2 == 0)?(n/2):((n+1)/2)));
    
  }
  return 0;
}
