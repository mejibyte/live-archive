/*
  Wrong Answer
 */
#include <iostream>
#include <map>
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
    if (b < a){
      swap(a, b);
    }
  }
  bool operator <(const recta &p) const{
    return (a<p.a || (a==p.a && b<p.b));
  }
};

bool colineales(const point &a, const point &b, const point &c){
  //printf("a = (%lf,%lf), b = (%lf,%lf), c = (%lf,%lf) ", a.x, a.y, b.x, b.y, c.x, c.y);
  double z =(fabs( (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x)));
  if (z <= 1e-9){
    //printf("true\n");
    return true;
  }
  //printf("false\n");
  return false;
}

bool overlap(const recta &p,const recta &q){
  //printf("p = (%lf,%lf) hasta (%lf,%lf)\n", p.a.x, p.a.y, p.b.x, p.b.y);
  //printf("q = (%lf,%lf) hasta (%lf,%lf)\n", q.a.x, q.a.y, q.b.x, q.b.y);
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
    map<double, vector<recta> > m;
    vector<recta> infinitas;

    for (int i=0; i<n; ++i){
      cin >> p[i].a.x >> p[i].a.y >> p[i].b.x >> p[i].b.y;
      p[i].sort();

      double m_n=p[i].b.y-p[i].a.y ,m_d=p[i].b.x-p[i].a.x;
      if (m_d == 0.0) infinitas.push_back(p[i]);
      else m[m_n/m_d].push_back(p[i]);

    }
    int ans = 0;
    for (map<double, vector<recta> >::iterator k=m.begin(); k != m.end(); ++k){
      vector<recta> &p = (k->second);
      sort(p.begin(),p.end());
      for (int i=0; i<p.size(); ++i){
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
      ans += p.size();
    }

    sort(infinitas.begin(),infinitas.end());
    for (int i=0; i<infinitas.size(); ++i){
      for (int j=i+1; j<infinitas.size(); ++j){
        if (colineales(infinitas[i].a, infinitas[i].b, infinitas[j].a) && colineales(infinitas[i].a, infinitas[i].b, infinitas[j].b)){

          if(overlap(infinitas[i],infinitas[j])){
            //cout << "entre \n";
            recta nueva;
            nueva.a=infinitas[i].a<infinitas[j].a?infinitas[i].a:infinitas[j].a;
            nueva.b=infinitas[i].b<infinitas[j].b?infinitas[j].b:infinitas[i].b;
            infinitas[i]=nueva;
            infinitas.erase(infinitas.begin()+j);
            j--;
          }
        }
      }
    }


    cout << ans + infinitas.size() << endl;
  }
  return 0;
}
