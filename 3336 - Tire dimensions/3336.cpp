#include <iostream>
#include <string>
#include <sstream>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

using namespace std;

const double pi = 2*acos(0);

int main(){
    string s, backup;
    while (getline(cin, s)){
        backup = s;
        for (int i=0; i<s.size(); ++i) if (!isdigit(s[i])) s[i] = ' ';
        stringstream sin(s);
        int sw, p, rim;
        sin >> sw >> p >> rim;
        double ans = pi*(rim*2.54 + 2*sw*p/1000.0);
        printf("%s: %.0lf\n", backup.c_str(), ans);
    }
    return 0;
}

