#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

struct polynomial{
    int deg;//ree
    vector<int> coef;//ficients
    polynomial(int deg=0) : deg(deg) {
        coef.assign(deg+1, 0);
    }
    polynomial(const string &s, int start = -1, int end = -1){
        if (start == -1 && end == -1) start = 0, end = s.size();
        deg = end - 1 - start;
        coef.resize(deg+1);
        for (int i=0; i<=deg; ++i){
            coef[i] = s[start+deg-i] - '0';
        }
    }
    
    void clean_zeros(){
        while (coef[deg] == 0 && deg > 0) --deg;
        coef.resize(deg+1);
    }
    
    //makes sure that coef[0] != 0
    //this is equivalent to discarding x=0 roots of the polynomial
    void get_independent_term(){
        clean_zeros();
        if (deg == 0) return;
        int i = 0;
        while (coef[i] == 0 && i <= deg) ++i;
        if (i > 0){
            deg -= i;
            for (int j=0; j<=deg; ++j){
                coef[j] = coef[j+i];
            }
        }
        coef.resize(deg+1);
    }
    
    bool is_solution(int x) const{
        int y = 0;
        for (int i=0; i<=deg; ++i){
            int a = coef[i];
            y -= a;
            if (y % x != 0) return false;
            y /= x;
        }
        return y == 0;
    }
    
    void print() const {
        for (int i=0; i<=deg; ++i){
            char sign = '+';
            if (coef[i] < 0) sign = '-';
            cout << sign << abs(coef[i]) << "x^" << i << " ";
        }
        cout << endl;     
    }
};

const polynomial operator * (const polynomial &a, const polynomial &b){
    polynomial r(a.deg + b.deg);
    for (int i=0; i<=a.deg; ++i){
        for (int j=0; j<=b.deg; ++j){
            r.coef[i+j] += a.coef[i] * b.coef[j]; 
        }
    }
    return r;
}

const polynomial operator + (const polynomial &a, const polynomial &b){
    polynomial r(max(a.deg, b.deg));
    for (int i=0; i<=r.deg; ++i){
        if (i <= a.deg) r.coef[i] += a.coef[i];
        if (i <= b.deg) r.coef[i] += b.coef[i];
    }
    return r;
}

const polynomial operator - (const polynomial &a, const polynomial &b){
    polynomial r(max(a.deg, b.deg));
    for (int i=0; i<=r.deg; ++i){
        if (i <= a.deg) r.coef[i] += a.coef[i];
        if (i <= b.deg) r.coef[i] -= b.coef[i];
    }
    return r;
}

//returns the product of polynomials in s between [start, end)
const polynomial multiply(const string &s, int start, int end){
    int star_pos = start;
    while (s[star_pos] != '*' && star_pos < end) star_pos++;
    polynomial a(s, start, star_pos);
    star_pos++;
    
    while (star_pos < end){
        int from = star_pos;
        while (s[star_pos] != '*' && star_pos < end) star_pos++;
        polynomial b(s, from, star_pos);
        a = a * b;
        star_pos++;
    }
    return a;
}

//returns the sum of products between [start, end)
const polynomial add(const string &s, int start, int end){
    int plus_pos = start;
    while (s[plus_pos] != '+' && plus_pos < end) plus_pos++;
    polynomial a = multiply(s, start, plus_pos);
    plus_pos++;
    
    while (plus_pos < end){
        int from = plus_pos;
        while (s[plus_pos] != '+' && plus_pos < end) plus_pos++;
        polynomial b = multiply(s, from, plus_pos);
        a = a + b;
        plus_pos++;
    }
    return a;
}

int main(){
    string s;
    while (getline(cin, s) && s != "="){
        int pos = s.find("=");
        
        polynomial p = add(s, 0, pos) - add(s, pos+1, s.length());
        p.clean_zeros();
        
        /*
        polynomial left = add(s, 0, pos), right = add(s, pos+1, s.length());
        left.print();
        right.print();
        p.get_independent_term();
        p.print();
        */
        
        int minimum_base = 2;
        for (int i=0; i<s.size(); ++i) if (isdigit(s[i])) minimum_base = max(minimum_base, s[i]-'0'+1);
        
        if (p.deg == 0 && p.coef[0] == 0){
            //infinite solutions!
            cout << minimum_base << "+\n";
            continue;
        }
        p.get_independent_term();
        //p.print();
        
        vector<int> ans;
        for (int i=1, a = abs(p.coef[0]); i*i <= a; ++i){
            if (a % i == 0){
                if (i >= minimum_base && p.is_solution(i)) ans.push_back(i);
                if (i*i < a && a / i >= minimum_base && p.is_solution(a / i)) ans.push_back(a / i);
            }
        }
        if (ans.empty()) cout << "*\n";
        else{
            sort(ans.begin(), ans.end());
            ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
            cout << ans[0];
            for (int i=1; i<ans.size(); ++i){
                cout << " " << ans[i];
            }
            cout << endl;
        }
    }   
}
