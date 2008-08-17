#include <iostream>
#include <algorithm>
#include <string> 

using namespace std;

int main(){
  int cols;
  while (cin >> cols && cols){
    string line;
    getline(cin, line);
    getline(cin, line);
    int rows = line.size() / cols;

    int n = line.size();
    int start = cols;
    while (start < n){
      reverse(line.begin()+start, line.begin()+start+cols);
      start += 2*cols;
    }
    for (int j=0; j<cols; ++j){
      for (int i=0; i<rows; ++i){
	cout << line[j+cols*i];
      }
    }
    cout << endl;
    
  }
  return 0;
}
