#include <vector>
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <climits>

using namespace std;

typedef pair<int,int> point;
vector<point> a, b;

int main(){
  
  int r,c,seats;
  
  while(cin >> r >> c >> seats && (r | c | seats)){
    
    a.clear();
    b.clear();

    for (int i=1; i<=r; ++i){
      for (int j=1; j<=c; ++j){
	char d;
	cin >> d;
	if (d == '.'){
	  a.push_back(point(i, j));
	  b.push_back(point(j, i));
	}
      }
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    /*cout << "seats es: " << seats << endl;
    cout << "a.size() es: " << a.size() << endl;
    for (int i=0; i<a.size(); ++i){
      cout << "(" << a[i].first << "," << a[i].second << ") ";
    }
    cout << endl;*/


    int minArea = INT_MAX;

    for (int i=0; i+seats<a.size(); ++i){
      int ladoX = a[i+seats-1].first - a[i].first + 1;
      //cout << "i es: " << i << " i + seats es: " << i + seats << endl;
      //cout << "ladoX es: " << ladoX << endl;
      int minY = a[i].second, maxY = a[i].second;
      for (int j=i+1; j<=i+seats; ++j){
	minY = min(minY, a[j].second);
	maxY = max(maxY, a[j].second);
      }
      int ladoY = maxY - minY + 1;
      minArea = min(minArea, ladoX * ladoY);
      cout << "area con a es: " << ladoX * ladoY << endl;
    }


    for (int i=0; i<b.size(); ++i){
      cout << "(" << b[i].first << "," << b[i].second << ") ";
    }
    cout << endl;

    for (int i=0; i+seats<b.size(); ++i){
      int ladoX = b[i+seats-1].first - b[i].first + 1;
      //cout << "i es: " << i << " i + seats es: " << i + seats << endl;
      //cout << "ladoX es: " << ladoX << endl;
      int minY = b[i].second, maxY = b[i].second;
      for (int j=i+1; j<=i+seats; ++j){
	minY = min(minY, b[j].second);
	maxY = max(maxY, b[j].second);
      }
      int ladoY = maxY - minY + 1;
      minArea = min(minArea, ladoX * ladoY);
      cout << "area con b es: " << ladoX * ladoY << endl;
    }
    
    cout << minArea << endl;
  }
}
