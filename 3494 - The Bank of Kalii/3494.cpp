#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

int days_of_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool isLeap(int y){
    if (y % 100 == 0) return y % 400 == 0;
    return y % 4 == 0;
}

struct date{
    int day, month, year;
};

int dateToDays(date d){
   int ans = 0;
   for (int y=1900; y<d.year; ++y){
       ans += 365 + (isLeap(y) ? 1 : 0);
   }
   for (int m=1; m<d.month; ++m){
       ans += days_of_month[m];
       if (m == 2 && isLeap(d.year)){
           ans++;
       }
   }
   return ans + d.day;
}

int main(){
   int C;
   scanf("%d", &C);
   for (int c=1; c<=C; ++c){
       printf("%d ", c);

       date a, b;
       scanf("%d/%d/%d", &a.month, &a.day, &a.year);
       scanf("%d/%d",&b.month, &b.day);
       if (a.month == b.month && a.day == b.day){
          printf("SAME DAY\n");
          continue;
       }

       int newYear, diff, score = 1<<30, bestYear;
       for (newYear = a.year-1; newYear<=a.year+1; ++newYear){
           b.year = newYear;
           int t = dateToDays(b)-dateToDays(a);
           if (abs(t) < score){
               score = abs(t);
               bestYear = newYear;
               diff = t;
           }
       }
       if (score > 7){
           printf("OUT OF RANGE\n");

       }else{
           printf("%d/%d/%d IS %d DAY", b.month, b.day, bestYear, score);
           if (score > 1) printf("S");
           if (diff < 0){
             printf(" PRIOR\n");
           }else{
             printf(" AFTER\n");
           }
       }
   }
   return 0;
}
