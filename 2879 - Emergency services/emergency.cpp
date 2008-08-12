#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include <iterator>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
int n;

bool compara(const vector<int> &a, const vector<int> &b){
     if (a[2] < b[2]) return true;
     if (b[2] < a[2]) return false;
     //tienen el mismo peso
     if (a.size() < b.size()) return true;
     if (b.size() < a.size()) return false;
     for (int i=0, n=a.size(); i<n; ++i){
         if (a[i] < b[i]) return true;
         if (b[i] < a[i]) return false;
     }
     return false;
}

void dijkstra(int start, int end, const vector<vector<int> > &g, vector<vector<int> > &all){
   vector<int> ans;
   
   vector<int> d(n, INT_MAX), p(n, -1);
   priority_queue<pii, vector<pii>, greater<pii> > q;
   d[start] = 0;
   q.push(pii(0, start));
   while (q.size()){
       int i = q.top().second;
       int w = q.top().first;
       q.pop();
       
       if (i == end) break;
       if (w > d[i]) continue;
       
       for (int j=0; j<n; ++j){
           if (g[i][j] != -1){
               int w_extra = g[i][j];
               if (w + w_extra < d[j]){
                   p[j] = i;
                   d[j] = w + w_extra;
                   q.push(pii(d[j], j));
               }
           }
       }         
   }
   //printf("start=%d, end=%d, time=%d\n", start, end, d[end]);
   int i = end;
   while (i != -1){
         ans.push_back(i+1);
         i = p[i];
   }
   ans.push_back(d[end]);
   ans.push_back(end+1);
   ans.push_back(start+1);
   reverse(ans.begin(), ans.end());
   //copy(ans.begin(), ans.end(), ostream_iterator<int>(cout, " "));
   //cout << endl;
   all.push_back(ans);
}

int main(){
    int Sets;
    cin >> Sets;
    for (int set=1; set<=Sets; ++set){
        cout << "Set Number " << set << endl;

        cin >> n;
        vector<vector<int> > g(n, vector<int>(n));
        for (int i=0; i<n; ++i)
            for (int j=0; j<n; ++j)
                cin >> g[i][j];
        
        int p;
        cin >> p;
        --p;
        string line;
        getline(cin, line);
        vector<int> eaft;
        stringstream ss(line);
        int x;
        while (ss >> x){
          eaft.push_back(--x);
        }
        
        vector<vector<int> > ans;
        for (int i=0; i<eaft.size(); ++i){
            dijkstra(eaft[i], p, g, ans);
        }
        sort(ans.begin(), ans.end(), compara);
        for (int i=0; i<ans.size(); ++i){
            copy(ans[i].begin(), ans[i].end()-1, ostream_iterator<int>(cout, " "));
            cout << ans[i].back() << endl;
        }
        
    }
    return 0;
}
