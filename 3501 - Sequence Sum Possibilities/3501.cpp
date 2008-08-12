#include <iostream>
using namespace std;
typedef long long ll;

int main(){
   int Casos;
   cin >> Casos;
   while (Casos--){
       int K;
       ll i;
       cin >> K >> i;
       cout << K << " ";
       int ans = 0;
       for (ll len=2; len*(len+1)/2 <= i; ++len){
           ll low = 1, mid, high = i;
           while (low < high){
                 mid = (low+high)/2;
                 ll t = (mid+len)*(mid+len-1)/2 - mid*(mid-1)/2;
                 if (t == i){
                       //printf("Contando mid = %lld, len = %lld, i = %lld\n", mid, len, i);
                       ans++;
                       break;
                 }
                 else if (t < i) low = ++mid;
                 else if (t > i) high = mid;
           }
       }
       cout << ans << endl;
   }
   return 0;
}

