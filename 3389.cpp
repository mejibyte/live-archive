#include <iostream>
#include <vector>

using namespace std;
bool termine;

void bt(vector<int> mons, const int &precio){
     if (termine ||  ((mons[0]*25 + mons[1]*10 + mons[2]*5 + mons[3]) > precio)) return;
     else if ((mons[0]*25 + mons[1]*10 + mons[2]*5 + mons[3]) == precio){
          cout << mons[0] <<" QUARTER(S), "<<mons[1]<<" DIME(S), "<<mons[2]<<" NICKEL(S), "<<mons[3]<<" PENNY(S)\n";
          termine = true;
     }else{
           if (mons[0] >= 1){
              for (int i=0; i<4; i++){
                  vector<int> temp(mons);
                  temp[i]++;
                  bt(temp, precio);
              }
           }else if (mons[1] >= 1){
              for (int i=1; i<4; i++){
                  vector<int> temp(mons);
                  temp[i]++;
                  bt(temp, precio);
              }
           }else if (mons[2] >= 1){
              for (int i=2; i<4; i++){
                  vector<int> temp(mons);
                  temp[i]++;
                  bt(temp, precio);
              }
           }else if (mons[3] >= 1){
              for (int i=3; i<4; i++){
                  vector<int> temp(mons);
                  temp[i]++;
                  bt(temp, precio);
              }
           }       
     }
}

int main()
{
    int casos, cents;
    cin >> casos;
    for (int caso=1; caso<=casos; caso++){
        termine = false;
        cin >> cents;
        cout << caso << " ";
        for (int i=0; i<4; i++){
            vector<int> mons(4, 0);
            mons[i]++;
            bt(mons, cents);            
        }
    }
    return 0;
}
