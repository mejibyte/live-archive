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

#define D(x) cout << #x " is " << x << endl

int n, a[10001], next[10001], perimeter, biggest;

void divisores(int x, vector<int> &d){
  for (int i=1; i*i<=x; ++i){
    if (x % i == 0){
      d.push_back(i);
      if (i*i < x) d.push_back(x / i);
    }
  }
  sort(d.begin(), d.end());
  
}

int f(const vector<int> &div){
  for (int k=div.size()-1; k>=0; --k){
    const int &divisor = div[k];
    if (divisor >= 3){
      //Ver si funciona con este divisor
      int sum = perimeter / divisor;

      if (biggest > sum) continue;
      //Cada segmentito debe sumar sum
      int i=0, j=0, acum=0;
      do{
	if (acum == sum){
	  next[i] = j;
	  acum  -= a[i];
	  i = i+1;
	}else if (acum > sum){
	  next[i] = -1;
	  acum -= a[i];
	  i = i+1;
	}else{
	  acum += a[j];
	  j = (j+1)%n;
	}
      }while (i < n);
      

      //Intentemos una soluci&#65533;n empezando en pivot
      for (int pivot=0; pivot<n; ++pivot){
	int i = pivot;
	while (i != -1){
	  i = next[i];
	  if (i == pivot) return n - divisor;
	}
      }
    }
  }
  
  return -1;
}

int main(){
  while (scanf("%d", &n) && n){
    
    biggest = -1;
    perimeter = 0;
    for (int i=0; i<n; ++i){
      scanf("%d", &a[i]);
      perimeter += a[i];
      if (a[i] > biggest) biggest = a[i];
    }

    if (n < 3){
      printf("-1\n");
      continue;
    }

    vector<int> div;
    divisores(perimeter, div);
    
    printf("%d\n", f(div));

  }
  return 0;
}
