/*
  Accepted.

  Trying to make it cleaner.
*/
using namespace std;
#include <algorithm>
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <cmath>

#define EPS 1e-9

typedef double real;

const real pi = 2*acos(0);
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

vector<ball> balls;

ball& getCoche(){
  for (int i=0; i<balls.size(); ++i)
    if (balls[i].owner == -1)
      return balls[i];
  assert(false);
}

char nextPlayer(){
  int n = balls.size();
  if (n == 1) return 0; //only coche thrown
  if (n == 2) return 1; //coche and other ball

  int cnt[] = {0, 0};
  for (int i=n-1; i>=0; --i){
    if (balls[i].owner != -1){
      cnt[balls[i].owner]++;
    }
  }
  assert(cnt[0] < 3 || cnt[1] < 3);
  //threw all balls
  if (cnt[0] == 3) return 1;
  if (cnt[1] == 3) return 0;

  ball coche = getCoche();
  char owner = -1;
  real minDistance = 1e20;
  for (int i=n-1; i>=0; --i){
    if (balls[i].owner != -1){
      real d = dist(coche, balls[i]);
      if (d < minDistance){
        minDistance = d;
        owner = balls[i].owner;
      }
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

    balls.clear();
    //Read coche
    real x, y, angle, r;
    cin >> x >> y >> angle >> r;
    angle *= pi/180.0;

    ball coche(x + r*cos(angle), y + r*sin(angle), -1);
    balls.push_back(coche);

    for (int b=0; b<6; ++b){
      int player = nextPlayer();
      cin >> x >> y >> angle >> r;
      angle *= pi/180.0;
      real nx = x + r*cos(angle);
      real ny = y + r*sin(angle);

      //<distance, index in balls>
      vector<pair<real, int> > will_collide;

      for (int i=balls.size()-1; i>=0; --i){
        if (collides(x, y, nx, ny, balls[i].x, balls[i].y)){
          will_collide.push_back(make_pair(dist(x, y, balls[i].x, balls[i].y), i));
        }
      }

      //sort by distance to (x,y)
      sort(will_collide.begin(), will_collide.end());


      if (will_collide.size() == 0){
        balls.push_back(ball(nx, ny, player));
      }else{
        ball b = balls[will_collide[0].second];
        b.owner = player;
        balls.push_back(b);
        for (int i=0; i<will_collide.size(); ++i){
          ball &before = balls[will_collide[i].second];
          if (i < will_collide.size() - 1){
            ball &after = balls[will_collide[i+1].second];
            before.x = after.x, before.y = after.y;
          }else{
            before.x = nx, before.y = ny;
          }
        }
      }
    }


    char winner = -1;
    real minDistance = 1e20;
    coche = getCoche();
    for (int i=0; i<balls.size(); ++i){
      if (balls[i].owner != -1){
        real d = dist(coche, balls[i]);
        if (d < minDistance){
          minDistance = d;
          winner = balls[i].owner;
        }
      }
    }

    assert(winner != -1);
    int points = 0;
    for(int i=0; i<balls.size(); ++i){
      if (winner == balls[i].owner){
        bool isPoint = true;
        for (int j=0; j<balls.size(); ++j){
          if (winner != balls[j].owner && balls[j].owner != -1){
            isPoint &= (dist(balls[i], coche) < dist(balls[j], coche));
          }
        }
        points += isPoint;
      }
    }
    cout << names[winner] << " " << points << endl;
  }
  return 0;
}
