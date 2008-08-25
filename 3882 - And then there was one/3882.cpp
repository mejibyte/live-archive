#include <iostream>
#include <cassert>
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <vector>
#include <string>
#include <string.h>
#include <set>
#include <map>
#include <stack>
#include <list>
#include <queue>
#include <sstream>
#include <fstream>
#include <math.h>
#include <algorithm>

using namespace std;

int main() {
    int n,m,k;
    cin >> n >> k >> m;
    while(n) {
        vector<int> t(n);
        for(int i = 0; i<t.size(); ++i) {
            t[i] = i +1;
        }
        int pos = m-1;
        t.erase(t.begin() + pos);
        pos--;

        for(int i =n-1; i>1; i--) {
            pos = (pos+k)%i;
            t.erase(t.begin() + pos);
            pos--;
        }
        cout << t[0] << endl;
        cin >> n >> k >> m;
    }
    return 0;
}
