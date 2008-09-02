/*
  Accepted
 */
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

int G[] = {1, 5, 7, 6, 2, 8, 3, 0, 9, 4};

char * type[] = {"athlete", "reserve", "judge", "staff", "press" };

int f(int i, int j){
  if (i == 0) return j;
  if (i == 1) return G[j];
  return f(i-1, G[j]);
}

int mod(int a, int b){
  return ((a%b)+b)%b;
}

int product(int i, int j){
  if (i < 5 && j < 5) return mod(i+j, 5);
  if (i < 5 && j >= 5) return mod(i+j-5, 5) + 5;
  if (i >= 5 && j < 5) return mod(i-5-j, 5) + 5;
  return mod(i-j, 5);
}

int main(){
  int n;
  cin >> n;
  while (n--){
    string s;
    cin >> s;
    int pow5 = 1;
    long long id = 0;
    for (int i=s.size()-1; i>=0; --i){
      id += pow5*('Z'-s[i]);
      pow5 *= 5;
    }
    bool valid = true;
    if (id > 99999999LL) valid = false;
    else{
      long long semi_id = id;
      int d = semi_id % 10, result = f(0, d);
      semi_id /= 10;
      for (int i=1; i<=7; ++i){
        d = semi_id % 10;
        result = product(result, f(i, d));
        semi_id /= 10;
      }
      if (result != 0){
        valid = false;
      }
    }
    printf("%s/%.8lld is ", s.c_str(), id);
    if (valid){
      printf("valid %s id number\n", type[(id % 100000000) / 20000000]);
    }else{
      printf("invalid id number\n");
    }

  }
  return 0;
}
