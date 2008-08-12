#include <iostream>
#include <vector>
#include <string>

using namespace std;

int r,c;
bool visited[21][21];
char p[21][21];
int t[21][21];

void dfs(int i, int j){
     if (visited[i][j]) return;
     
     visited[i][j] = true;
     if (j+1 < c && t[i][j]%2 == 1 && !visited[i][j+1]){
         p[i][j+1] = 'R';
         dfs(i, j+1);
     }
     if (j>0 && t[i][j-1]%2 == 1 && !visited[i][j-1]){
         p[i][j-1] = 'L';
         dfs(i, j-1);
     }
     if (i+1 < r && t[i][j]>=2 && !visited[i+1][j]){
         p[i+1][j] = 'D';
         dfs(i+1, j);
     }
     if (i>0 && t[i-1][j]>=2 && !visited[i-1][j]){
         p[i-1][j] = 'U';
         dfs(i-1, j);
     }
}

int main(){
    cin >> r >> c;
    int cont = 1;
    while(r && c) {
        if (cont > 1) cout << endl;
        for(int i =0; i<r; i++) {
            for(int j = 0; j<c; j++) {
                cin >> t[i][j];
            }
        }
        cout << "Super-maze " << cont << ":" << endl;
        cout << "+";
        for(int i = 0; i<c; i++) {
            cout << "---+";
        }
        cout << endl;
        for(int i = 0; i<r; i++) {
            cout << "|";
            for(int j = 0; j<c; j++) {
                if(t[i][j]%2==0) cout << "   |";
                else cout << "    ";
            }
            cout << endl;
            cout << "+";
            for(int j = 0; j<c; j++) {
                if(t[i][j]<=1) cout << "---+";
                else cout << "   +";
            }
            cout << endl;
        }
        
        //Andrés
        memset(visited, false, sizeof visited);
        memset(p, '\0', sizeof p);
        dfs(0, 0);
        string ans = "";
        int i=r-1, j=c-1;
        //cout << "p[r-1][c-1] es: " << (int)p[r-1][c-1] << " " << p[r-1][c-1] << endl; 
        while (p[i][j] != '\0'){
           ans = p[i][j] + ans;
           switch (p[i][j]){
               case 'U':
                    ++i;
                    break;
               case 'D':
                    --i;
                    break;
               case 'L':
                    ++j;
                    break;
               case 'R':
                    --j;
                    break;
               default:
                  p[i][j] = '\0';
               break;
           }
        }
        ans = "Solution: " + ans;
        for (int i=0; i<ans.size(); ++i){
            if (i > 0 && i % 80 == 0) cout << endl;
            cout << ans[i];
        }
        cout << endl;
        cont ++;
        cin >> r >> c;
    }
    return 0;
}
