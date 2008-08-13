#include <iostream>
#include <math.h>
#include <stdio.h>
using namespace std;

struct point{
 double x,y;
};

double dist(point a, point b){
 return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

const double pi = 2*acos(0.0);

inline bool right(int a){ return (a >= 88 && a <= 92); }

int main(){
 point a,b,c;
 while (cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y){

   if (fabs((a.x-b.x)*(a.y-c.y) - (a.y-b.y)*(a.x-c.x)) < 1e-7)
     printf("Not a Triangle\n");
   else{
   double l1, l2, l3;
   l1 = dist(a,b);
   l2 = dist(b,c);
   l3 = dist(a,c);

   int iguales = 0;
   iguales += (fabs(l1-l2) < 0.01);
   iguales += (fabs(l2-l3) < 0.01);
   iguales += (fabs(l1-l3) < 0.01);
   if (iguales == 0) printf("Scalene ");
   else if (iguales == 1) printf("Isosceles ");
   else printf("Equilateral ");


   int a1, a2, a3;
   a1 = int(acos((l1*l1 + l2*l2 - l3*l3)/(2*l1*l2))*180.0/pi);
   a2 = int(acos((l1*l1 + l3*l3 - l2*l2)/(2*l1*l3))*180.0/pi);
   a3 = int(acos((l2*l2 + l3*l3 - l1*l1)/(2*l2*l3))*180.0/pi);



   if (right(a1) || right(a2) || right(a3)){
     printf("Right");
   }else if (a1 > 90 || a2 > 90 || a3 > 90){
     printf("Obtuse");
   }else printf("Acute");

   printf("\n");
   }

   //printf("%lf,  %lf, %lf\n", l1, l2, l3);
   //printf("%d,  %d, %d\n", a1, a2, a3);

 }
 printf("End of Output\n");
 return 0;
}
