/*
  Accepted.
 */
using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>

#define D(x) cout << #x " is " << x << endl
#define EPS 1e-9
#define dprintf debug && printf
//#define debug true
#define debug false
const long double pi = 2*acos(0);

typedef long double real;

inline bool smaller(real a, real b){
  return (a - b <= EPS);
}

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
bool collides(real x, real y,    real nx, real ny,    real bx, real by){
  real cross = (bx-x)*(ny-y)-(by-y)*(nx-x);
  bool inside = point_in_box(bx, by,     x, y, nx, ny);
  bool zero = fabs(cross) < EPS;
  bool ans = inside && zero;
  /*
    dprintf("Collition from (%llf, %llf) to (%llf, %llf) with (%llf, %llf) = %d (inside = %d, zero = %d)\n",
    x,y,nx,ny,bx,by, ans, inside, zero);
  */
  return ans;
}

struct ball{
  real x, y;
  char owner; //Player who owns this ball
  ball(real x=0, real y=0, char owner=-1) : x(x), y(y), owner(owner) {}
};

inline real dist(real ax, real ay, real bx, real by){
  return sqrt((ax-bx)*(ax-bx)+(ay-by)*(ay-by));
}

inline real dist(ball a, ball b){
  return dist(a.x, a.y, b.x, b.y);
}

vector<ball> boules;
ball couche;

/*
  Returns 0 || 1
*/
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
    real d = dist(couche, boules[i]);
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
    //Read couche
    real x, y, angle, r;
    cin >> x >> y >> angle >> r;
    angle *= pi/180.0;
    couche.x = x + r*cos(angle);
    couche.y = y + r*sin(angle);
    couche.owner = -1;

    for (int b=0; b<6; ++b){
      int player = nextPlayer();
      cin >> x >> y >> angle >> r;
      angle *= pi/180.0;
      real nx = x + r*cos(angle);
      real ny = y + r*sin(angle);

      vector<pair<int, ball> > will_collide;

      if (collides(x, y, nx, ny, couche.x, couche.y)){
        will_collide.push_back(make_pair(-1, couche));
      }

      for (int i=boules.size()-1; i>=0; --i){
        if (collides(x, y, nx, ny, boules[i].x, boules[i].y)){
          will_collide.push_back(make_pair(i, boules[i]));
        }
      }

      //sort will_collide according to distance to (x,y)
      for (int i=0; i<will_collide.size(); ++i){
        for (int j=i+1; j<will_collide.size(); ++j){
          real di = dist(x, y, will_collide[i].second.x, will_collide[i].second.y);
          real dj = dist(x, y, will_collide[j].second.x, will_collide[j].second.y);
          if (dj < di) swap(will_collide[i], will_collide[j]);
        }
      }

      dprintf("moving ball from (%llf, %llf) to (%llf, %llf)\n", x, y, nx, ny);
      if (will_collide.size() == 0){
        dprintf("   no collitions\n");
        boules.push_back(ball(nx, ny, player));
      }else{
        dprintf("    %d collitions\n", will_collide.size());
        for (int i=0; i<will_collide.size(); ++i){
          dprintf(" (%llf, %llf) - ", will_collide[i].second.x, will_collide[i].second.y);
        }
        dprintf("\n");
        boules.push_back(ball(will_collide[0].second.x, will_collide[0].second.y, player));
        for (int i=0; i<will_collide.size(); ++i){
#define assign(ball, other_ball) ball.x = other_ball.second.x, ball.y = other_ball.second.y

          if (will_collide[i].first == -1){
            if (i < will_collide.size() - 1){
              assign(couche, will_collide[i+1]);
            }else{
              couche.x = nx;
              couche.y = ny;
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

      dprintf("Done simulating player's %d turn. These are the balls:\n", player);
      dprintf("Couche = (%llf, %llf)\n", couche.x, couche.y);
      for (int i=0; i<boules.size(); ++i){
        dprintf("Boule = (%llf, %llf) owned by %d\n", boules[i].x, boules[i].y, (char)boules[i].owner);
      }
    }
    dprintf("end of game\n\n");

    char winner = -1;
    real minDistance = 1e20;
    for (int i=0; i<boules.size(); ++i){
      real d = dist(couche, boules[i]);
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
            isPoint = isPoint && (dist(boules[i], couche) < dist(boules[j], couche));
          }
        }
        points += isPoint;
      }
    }

    printf("%s %d\n", names[winner].c_str(), points);
  }
  return 0;
}
