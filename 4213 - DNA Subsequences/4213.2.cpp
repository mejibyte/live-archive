// Robado de http://forums.topcoder.com/?module=Message&messageID=1043722

#include <stdio.h>
#include <string.h>

char a[10000], b[10000];
int res1[1005][1005], res2[1005][1005], match[1005][1005];
int n1, n2, s1, s2;
int main() {
        int k;while(scanf("%d\n",&k),k) {
                gets(a);gets(b);
                n1 = strlen(a);n2 = strlen(b);
                for(int i=0;i<n1;i++){
                        for(int j=0;j<n2;j++){
                                res1[i+1][j+1] = res2[i+1][j+1] = match[i+1][j+1] = 0;
                                res1[i+1][j+1] >?= res1[i][j+1];
                                res1[i+1][j+1] >?= res1[i+1][j];
                                if (a[i] == b[j]) {
                                        match[i+1][j+1] = match[i][j] + 1;
                                        if(match[i+1][j+1] >= k) {
                                                res2[i+1][j+1] = res1[i+1-k][j+1-k] + k;
                                        }
                                        if(res2[i][j]){
                                                res2[i+1][j+1] >?= (res2[i][j] + 1);
                                        }
                                        res1[i+1][j+1] >?= res2[i+1][j+1];
                                }
                        }
                }
                printf("%d\n",res1[n1][n2]);
        }
        return 0;
}
