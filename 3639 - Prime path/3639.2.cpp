/*
  Problem: 3639 - Prime Path (ACM-ICPC Live Archive)

  Andrés Mejía-Posada

  Verdict: Accepted.

  Algorithm: BFS and Eratosthenes' sieve.

  Version 2 = Version 1 + A little faster sieve
 */
#include <iostream>
#include <cassert>
#include <queue>

using namespace std;



const int SIZE = 9999;

//criba[i] = false si i es primo
bool criba[SIZE+1];

void buildCriba(){
  memset(criba, false, sizeof(criba));

  criba[0] = criba[1] = true;
  for (int i=4; i<=SIZE; i += 2){
    criba[i] = true;
  }
  for (int i=3; i*i<=SIZE; i += 2){
    if (!criba[i]){
      for (int j=i*i; j<=SIZE; j += i){
	criba[j] = true;
      }
    }
  }
}

int main(){
  buildCriba();
  int c;
  cin >> c;
  while (c--){
    int start, end;
    cin >> start >> end;
    bool visited[SIZE+1] = {false};
    queue<pair<int, int> > q;
    q.push(make_pair(0, start));

    int answer = -1;

    while (q.size()){
      int u = q.front().second;
      int w = q.front().first;
      q.pop();

      //cout << "Saque " << u << " en " << w << endl;

      if (1000 <= u && u <= 9999 && !criba[u] && !visited[u]){
        visited[u] = true;

        if (u == end){
          answer = w;
          break;
        }

        for (int i=1; i<=4; ++i){
          int pow10 = 1; for (int j=1; j<=i; ++j) pow10 *= 10;
          int digit = (u % pow10)* 10/pow10;

          int v = u - digit * pow10/10;
          for (int k=0; k<=9; ++k){
            int possible = v + pow10/10 * k;
            if (1000 <= possible && possible <= 9999 && !criba[possible] && !visited[possible]){
            assert(possible % 2 == 1);
              q.push(make_pair(w + 1, possible));
              //cout << "  Meti " << possible << endl;
            }
          }
        }
      }
    }
    if (answer == -1){
      cout << "Impossible" << endl;
    }else{
      cout << answer << endl;
    }
  }

  return 0;
}
