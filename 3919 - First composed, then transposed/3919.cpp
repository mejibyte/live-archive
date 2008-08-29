#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

string notes[] = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};

string flat_to_sharp(string n){
  if (n.size() == 1 || (n.size() == 2 && n[1] == '#') ) return n;
  if (n == "Cb") return "B";
  if (n == "Fb") return "E";
  char c = n[0];
  if (c == 'A') return "G#";
  string ans = "";
  ans += c-1;
  ans += "#";
  return ans;
}

string enharmonic(string n){
  if (n == "E#") return "F";
  if (n == "B#") return "C";
  return n;
}

int main(){
  string s;
  while (getline(cin, s) && s != "***"){
    int n;
    cin >> n;
    while (n < 0) n += 12;
    stringstream sin(s);
    if (sin >> s){
      do{
        s = enharmonic(flat_to_sharp(s));
        int i = 0;
        //cout << "s es: " << s << endl;
        while (notes[i] != s) ++i;
        cout << notes[(i+n)%12];
      }while(sin >> s && cout << " ");
    }
    cout << endl;
    getline(cin, s);
  }
  return 0;
}
