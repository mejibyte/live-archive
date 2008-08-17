/*
  Time limit exceeded
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>

using namespace std;

struct point{
  double x, y;
  bool operator < (const point &t) const {
    return (x < t.x || (x == t.x && y < t.y) );
  }
  bool operator ==(const point &t) const{
    return (x==t.x && y== t.y);
  }
};

struct recta{
  point a, b;
  void sort() {
    if (a < b){
      swap(a, b);
    }
  }
  bool operator <(const recta &p) const{
    return (a<p.a || (a==p.a && b<p.b));
  }
};

bool colineales(const point &a, const point &b, const point &c){
  return (fabs( (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x)) <= 1e-9);
}

bool overlap(const recta &p,const recta &q){
  double m_n=p.b.y-p.a.y ,m_d=p.b.x-p.a.x;
  if (m_d==0){
    return (q.a.y<=p.b.y && q.b.y >=p.a.y);
  }else{
    if(q.a.x<=p.b.x && q.b.x>= p.a.x){
      if(m_n/m_d>0){
        return (q.a.y<=p.b.y && q.b.y >=p.a.y);
      }else{
        return (q.a.y>=p.b.y && q.b.y <=p.a.y);
      }
    }
  }
}
int main(){
  int n;
  while (cin >> n && n){
    vector<recta> p(n);
    for (int i=0; i<n; ++i){
      cin >> p[i].a.x >> p[i].a.y >> p[i].b.x >> p[i].b.y;
      p[i].sort();
    }
    sort(p.begin(),p.end());
    for (int i=0; i<p.size()-1; ++i){
      for (int j=i+1; j<p.size(); ++j){
        if (colineales(p[i].a, p[i].b, p[j].a) && colineales(p[i].a, p[i].b, p[j].b)){
          if(overlap(p[i],p[j])){
            recta nueva;
            nueva.a=p[i].a<p[j].a?p[i].a:p[j].a;
            nueva.b=p[i].b<p[j].b?p[j].b:p[i].b;
            p[i]=nueva;
            p.erase(p.begin()+j);
            j--;
          }
        }
      }
    }
    cout << p.size() << endl;
  }
  return 0;
}
