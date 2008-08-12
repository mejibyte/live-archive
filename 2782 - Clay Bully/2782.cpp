/*
  Accepted
 */
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

struct student{
  int a, b, c;
  string name;
  student(int A, int B, int C) : a(A), b(B), c(C) {}
  bool operator < (const student &that) const {
    return a*b*c < that.a*that.b*that.c;
  }
};

int main(){
  int n;
  while (cin >> n && n != -1){
    student small(1000, 1000, 1000), big(0, 0, 0), s(0, 0, 0);
    for (int i=0; i<n; ++i){
      cin >> s.a >> s.b >> s.c >> s.name;
      if (s < small) small = s;
      if (!(s < big)) big = s;
    }
    cout << big.name << " took clay from " << small.name << "." << endl;

  }
  return 0;
}
