// 2007 ACM Mid-Central USA Regional Programming Contest
// Solution to Problem F: Electronic Document Security [easy/moderate]
// Eric D. Shade, Missouri State University

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;

const int ENTITIES = 26;
const int RIGHTS = 26;

bool has_right[ENTITIES][RIGHTS];

int entity(char name) { return name - 'A'; }
int right(char name)  { return name - 'a'; }

char ename(int e) { return e + 'A'; }
char rname(int r) { return r + 'a'; }

void clear_rights(int e) {
    for (int r = 0; r < RIGHTS; r++) has_right[e][r] = false;
}

string rights(int e) {
    string t = "";
    for (int r = 0; r < RIGHTS; r++)
        if (has_right[e][r])
            t += rname(r);
    return t;
}
 
int main() {
    ifstream in("eds.in");
    string s;
    int lognum = 0;

    for (;;) {        
        getline(in, s);
        if (s == "#") break;
        lognum++;

        for (int e = 0; e < ENTITIES; e++) clear_rights(e);
                
        int n = s.length();
        int i, k;
        
        for (i = 0; i < n; i = k) {
            if (s[i] == ',') i++;
            for (k = i + 1; isupper(s[k]); k++) ;
            int op = k;
            char x = s[op];
            
            if (x == '=')
                for (int j = i; j < op; j++)
                    clear_rights(entity(s[j]));
            
            for (k = op + 1; k < n && islower(s[k]); k++)        
                for (int j = i; j < op; j++)
                    has_right[entity(s[j])][right(s[k])] = (x != '-');
        }
        
        string prev_rights = "";
        string next_rights;
        
        cout << lognum << ":";
        
        for (int e = 0; e < ENTITIES; e++) {
            next_rights = rights(e);
            if (next_rights != "") {
                if (prev_rights == "") prev_rights = next_rights;
                if (next_rights != prev_rights) {
                    cout << prev_rights;
                    prev_rights = next_rights;
                }
                cout << ename(e);
            }
        }

        cout << prev_rights << endl;
    }

    in.close();
}
