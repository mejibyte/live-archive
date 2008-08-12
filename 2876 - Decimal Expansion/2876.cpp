#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    int n;
    cin >> n;
    while (n--){
       int a, b;
       cin >> a >> b;
       cout << a << " " << b << endl;
       
       int d[205], r[205];
       for (int i=0; i<200; ++i){
           r[i] = a % b;
           d[i] = a / b;
           
           a = r[i]*10;
       }
       
       bool period = false;
       int start, end;
       for (int i=0; i<200 && !period; ++i){
           for (int j=i+1; j<200 && !period; ++j){
               if (r[i] == r[j]){
                   start = i;
                   end = j;
                   period = true;
               }
           }
       }
       
       int last = 200;
       if (period) last = end+1;
       for (int i=0; i<last; ++i) cout << d[i];
       if (period){
           cout << " sequence of repeating digits: ";
           for (int i=start+1; i<=end; ++i){
               cout << d[i];
           }
       }
       cout << endl;
    }
    return 0;
}
