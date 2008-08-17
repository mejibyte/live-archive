#include <iostream>
#include <iterator>
#include <algorithm>
#include <stack>
#include <queue>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

using namespace std;

string directions[] = {"north", "east", "south", "west"};

int main(){
  int n, D=1;
  while (cin >> n && n){
    string s;
    getline(cin, s); //\n despues del numero

    vector<string> calles(n), turns(n);

    cin >> s; //Head
    cin >> s; // north, east, ...
    int dir;
    for (int k=0; k<4; ++k){
      if (directions[k] == s){
        dir = k;
        break;
      }
    }

    cin >> s; //from
    string number0;
    cin >> number0;
    getline(cin, calles[0]);
    for (int i=1; i<n-1; ++i){
      cin >> s; //Turn || continue
      if (s == "Continue"){
        turns[i] = s;
        cin >> s; //on
        getline(cin, calles[i]);
      }else{
        cin >> s; //left || right
        if (s == "left") dir = (dir+3)%4;
        else dir = (dir+1)%4;
        turns[i] = s;
        cin >> s; //at
        getline(cin, calles[i]);
      }
    }

    cin >> s >> s; //Arrive at
    string number1;
    cin >> number1;
    getline(cin, calles[n-1]);


    /*
    cout << "Calles es: "; copy(calles.begin(), calles.end(), ostream_iterator<string>(cout, "\n"));
    cout << endl;
    cout << "Turns es: "; copy(turns.begin(), turns.end(), ostream_iterator<string>(cout, "\n"));
    cout << endl;
    cout << endl;
    */

    cout << "Directions " << D++ << ":" << endl;
    cout << "Head " << directions[(dir+2)%4] << " from " << number1  << calles[n-1] << endl;
    int director = n-2, calle=n-3;
    while (calle >= 0){
      if (turns[director] == "left") cout << "Turn right at";
      else if (turns[director] == "right") cout << "Turn left at";
      else cout << "Continue on";
      cout << calles[calle] << endl;
      director--, calle--;
    }
    cout << "Arrive at " << number0 << calles[0] << endl;
    cout << endl;
  }
  return 0;
}
