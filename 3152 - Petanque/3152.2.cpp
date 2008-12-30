/*
  Accepted.

  Trying to make it cleaner.
 */
using namespace std;
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <cmath>

#define EPS 1e-9
const long double pi = 2*acos(0);
typedef long double real;

//returns true if a <= b
inline bool smaller(real a, real b){  return (a - b <= EPS); }

/*
  Returns true if point (x, y) lies inside (or in the border)
  of box defined by points (x0, y0) and (x1, y1).
*/
bool point_in_box(real x, real y,
                  real x0, real y0,    real x1, real y1){
  return
    smaller(min(x0, x1), x) && smaller(x, max(x0, x1)) &&
    smaller(min(y0, y1), y) && smaller(y, max(y0, y1));
}

/*
  Returns true if a ball that rolls from (x,y) to (nx,ny) will collide
  with a ball located at (bx, by).

*/
inline bool collides(real x, real y,    real nx, real ny,    real bx, real by){
  return point_in_box(bx, by, x, y, nx, ny) && fabs((bx-x)*(ny-y)-(by-y)*(nx-x)) < EPS;
}

struct ball{
  real x, y;
  char owner; //Player who owns this ball, or -1 if its the coche
  ball(real x=0, real y=0, char owner=-1) : x(x), y(y), owner(owner) {}
};

inline real dist(real ax, real ay, real bx, real by){
  return sqrt((ax-bx)*(ax-bx)+(ay-by)*(ay-by));
}

inline real dist(ball a, ball b){
  return dist(a.x, a.y, b.x, b.y);
}

vector<ball> boules;
ball coche;

char nextPlayer(){
  if (boules.size() == 0) return 0;
  if (boules.size() == 1) return 1;

  int cnt[] = {0, 0};
  for (int i=boules.size()-1; i>=0; --i){
    cnt[boules[i].owner]++;
  }
  assert(cnt[0] < 3 || cnt[1] < 3);
  //threw all balls
  if (cnt[0] == 3) return 1;
  if (cnt[1] == 3) return 0;

  char owner = -1;
  real minDistance = 1e20;
  for (int i=boules.size()-1; i>=0; --i){
    real d = dist(coche, boules[i]);
    if (d < minDistance){
      minDistance = d;
      owner = boules[i].owner;
    }
  }
  assert(owner != -1);
  return !owner;
}

int main(){
  int casos;
  cin >> casos;
  while (casos--){
    string names[2];
    cin >> names[0] >> names[1];

    boules.clear();
    //Read coche
    real x, y, angle, r;
    cin >> x >> y >> angle >> r;
    angle *= pi/180.0;
    coche.x = x + r*cos(angle);
    coche.y = y + r*sin(angle);
    coche.owner = -1;

    for (int b=0; b<6; ++b){
      int player = nextPlayer();
      cin >> x >> y >> angle >> r;
      angle *= pi/180.0;
      real nx = x + r*cos(angle);
      real ny = y + r*sin(angle);

      /*
        first = index of this ball in "boules" vector, or -1 if its the coche
       */
      vector<pair<int, ball> > will_collide;

      if (collides(x, y, nx, ny, coche.x, coche.y)){
        will_collide.push_back(make_pair(-1, coche));
      }

      for (int i=boules.size()-1; i>=0; --i){
        if (collides(x, y, nx, ny, boules[i].x, boules[i].y)){
          will_collide.push_back(make_pair(i, boules[i]));
        }
      }

      //sort will_collide according to distance to (x,y), using bubble-sort :)
      for (int i=0; i<will_collide.size(); ++i){
        for (int j=i+1; j<will_collide.size(); ++j){
          real di = dist(x, y, will_collide[i].second.x, will_collide[i].second.y);
          real dj = dist(x, y, will_collide[j].second.x, will_collide[j].second.y);
          if (dj < di) swap(will_collide[i], will_collide[j]);
        }
      }

      if (will_collide.size() == 0){
        boules.push_back(ball(nx, ny, player));
      }else{
        boules.push_back(ball(will_collide[0].second.x, will_collide[0].second.y, player));
        for (int i=0; i<will_collide.size(); ++i){
#define assign(ball, other_ball) ball.x = other_ball.second.x, ball.y = other_ball.second.y
          if (will_collide[i].first == -1){
            if (i < will_collide.size() - 1){
              assign(coche, will_collide[i+1]);
            }else{
              coche.x = nx;
              coche.y = ny;
            }
          }else{

            if (i < will_collide.size() - 1){
              assign(boules[will_collide[i].first], will_collide[i+1]);
            }else{
              boules[will_collide[i].first].x = nx;
              boules[will_collide[i].first].y = ny;
            }
          }
        }
      }
    }

    char winner = -1;
    real minDistance = 1e20;
    for (int i=0; i<boules.size(); ++i){
      real d = dist(coche, boules[i]);
      if (d < minDistance){
        minDistance = d;
        winner = boules[i].owner;
      }
    }

    assert(winner != -1);
    int points = 0;
    for(int i=0; i<boules.size(); ++i){
      if (winner == boules[i].owner){
        bool isPoint = true;
        for (int j=0; j<boules.size(); ++j){
          if (winner != boules[j].owner){
            isPoint = isPoint && (dist(boules[i], coche) < dist(boules[j], coche));
          }
        }
        points += isPoint;
      }
    }

    cout << names[winner] << " " << points << endl;
  }
  return 0;
}
