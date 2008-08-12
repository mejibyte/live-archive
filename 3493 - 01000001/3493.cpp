#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string suma(string a, string b){
 if (a.length() > b.length()) swap(a, b);
 while (a.length() < b.length()){
   a = '0' + a;
 }
 string r = "";
 bool carry = 0;
 for (int i=a.length()-1; i>=0; --i){
     int t = a[i] - '0' + b[i] - '0';
     //cerr << "t es: " << t << endl;
     t += carry;
     if (t == 2){
       t = 0;
       carry = 1;
     }else if (t == 3){
       t = 1;
       carry = 1;
     }else{
       carry = 0;
     }
     r = char('0'+t) + r;
     //cerr << r << endl;
 }
 if (carry) r = '1'+r;
 while (r.length() > 1 && r[0] == '0'){
     r.erase(0, 1);
 }
 return r;
}

int main() {
   int cases, c=1;
   cin >> cases;
   while(cases) {
       string n1,n2;
       cin >> n1 >> n2;
       //Algortimo...
       cout << c++ << " " << suma(n1, n2) << endl;
       cases--;
   }
   return 0;
}
