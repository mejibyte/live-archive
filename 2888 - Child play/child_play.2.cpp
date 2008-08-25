#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 400, MAXV = 1000;

int x[MAXN+1], y[MAXN+1], sum, discarded, n, dp[MAXN][MAXN*MAXV+1];

int main(){
        while (cin >> n && n){
                int maxd = 0;
                for (int i=0; i<n; ++i){
                        cin >> x[i] >> y[i];
                        if (y[i] < x[i]) swap(x[i], y[i]);
                        maxd += y[i];
                }
                sum = discarded = -1;

                for (int i=0; i<n; ++i){
                        for (int j=0; j<=maxd; ++j){
                                dp[i][j] = INT_MIN;
                        }
                }

                dp[0][y[0]-x[0]] = y[0];
                for (int i=0; i<n-1; ++i){
                        for (int j=0; j<=maxd; ++j){
                                if (dp[i][j] >= 0){
                                        int t;

                                        t = abs(j+x[i+1]-y[i+1]);
                                        if (t <= maxd) dp[i+1][t] >?= max(dp[i][j]+x[i+1], dp[i][j]-j+y[i+1]);

                                        t = abs(j+y[i+1]-x[i+1]);
                                        if (t <= maxd) dp[i+1][t] >?= max(dp[i][j]+y[i+1], dp[i][j]-j+x[i+1]);
                                }
                        }
                }


                for (int j = 0; j<maxd; ++j) printf("%4d ", j);
                puts("");
                for (int j = 0; j<maxd; ++j) printf("%4s ", "****");
                puts("");

                for (int i=0; i<n; ++i){
                        for (int j = 0; j < maxd; ++j) {
                                if (dp[i][j] < 0) printf("%4s ", "-i");
                                else printf("%4d ", dp[i][j]);
                        }
                        puts("");
                }
                puts("");

                if (dp[n-1][0] >= 0) cout << dp[n-1][0] << " discard none...";
                else{
                        if (sum == -1 || (n == 1 && discarded != -1)) cout << "impossible";
                        else{
                                cout << sum << " discard ";
                                if (discarded == -1) cout << "none";
                                else cout << x[discarded] << " " << y[discarded];
                        }
                }
                cout << endl;
        }
        return 0;
}
