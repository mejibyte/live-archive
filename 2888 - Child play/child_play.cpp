#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 400;

int x[MAXN+1], y[MAXN+1], sum, discarded, n;

void backtrack(int a, int b, int i, int d){
        if (i == n){ //no hay mas fichas
                if (a == b){
                        if ((a > sum) || (a == sum && d != -1 && discarded != -1 && x[d] < x[discarded])){
                                sum = a;
                                discarded = d;
                        }
                }
        }else{ //hay mas fichas
                backtrack(a+x[i], b+y[i], i+1, d);
                backtrack(a+y[i], b+x[i], i+1, d);
                if (d == -1){
                        backtrack(a, b, i+1, i);
                }
        }
}

int main(){
        while (cin >> n && n){
                for (int i=0; i<n; ++i){
                        cin >> x[i] >> y[i];
                        if (y[i] < x[i]) swap(x[i], y[i]);
                }
                sum = discarded = -1;
                backtrack(0, 0, 0, -1);
                if (sum == -1 || (n == 1 && discarded != -1)) cout << "impossible";
                else{
                        cout << sum << " discard ";
                        if (discarded == -1) cout << "none";
                        else cout << x[discarded] << " " << y[discarded];
                }
                cout << endl;
        }
}
