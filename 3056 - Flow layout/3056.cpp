#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

int main(){
  int ancho;
  while (cin >> ancho && ancho){
    vector<int> altura_fila(1, 0), ancho_fila(1, 0);
    int fila = 0;
    int m1, m2;
    while (cin >> m1 >> m2 && m1 != -1 && m2 != -1){
      assert(m1 <= ancho);
      if (ancho_fila[fila] + m1 <= ancho){ //Cabe en esta fila
        ancho_fila[fila] += m1;
        altura_fila[fila] >?= m2;
      }else{ //No cabe en esta fila
        altura_fila.push_back(m2), ancho_fila.push_back(m1);
        ++fila;
      }
    }
    int ans1 = 0, ans2 = 0;
    int n = altura_fila.size();
    assert(n == ancho_fila.size());
    for (int i=0; i<n; ++i){
      ans1 += altura_fila[i];
      ans2 >?= ancho_fila[i];
    }
    cout << ans2 << " x " << ans1 << endl;

  }
  return 0;
}
