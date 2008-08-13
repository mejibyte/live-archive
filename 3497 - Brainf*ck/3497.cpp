/*
  Problem: 
  Accepted
 */
#include <stack>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

char prog[128001];
int   jmp[128001];
int  array[32769];
int n;

void run(int pc, int pntr){
  while (pc < n){
    switch(prog[pc]){
    case '.':
      printf("%c", array[pntr]);
      pc++;
      break;
    case '-':
      array[pntr] = (array[pntr] + 255) % 256;
      pc++;
      break;
    case '+':
      array[pntr] = (array[pntr] + 1) % 256;
      pc++;
      break;
    case '<':
      pntr = (pntr + 32767) % 32768;
      pc++;
      break;
    case '>':
      pntr = (pntr + 1) % 32768;
      pc++;
      break;
    case '[':
      if (array[pntr] == 0) pc = jmp[pc] + 1;
      else pc++;
      break;
    case ']':
      if (array[pntr] != 0) pc = jmp[pc];
      else pc++;
      break;
    }
  }
}

int main(){
  int N, C=0;
  scanf("%d\n", &N);
  while (N-- && ++C){
    printf("PROGRAM #%d:\n", C);
    memset(prog,0, sizeof prog);
    memset(jmp, 0, sizeof jmp);
    memset(array, 0, sizeof array);
    n = 0;
    stack<int> stk;
    string line;
    bool compiled = true;
    while (getline(cin, line) && line != "end"){
      for (int i=0, _n=line.size(); i<_n && line[i] != '%'; ++i){
        char c = line[i];
        if (c == '.' || c == '<' || c == '>' || c == '[' ||
            c == ']' || c == '+' || c == '-'){
          if (c == '['){
            stk.push(n);
          }else if (c == ']'){
            if (stk.size()){
              jmp[stk.top()] = n;
              jmp[n] = stk.top();
              stk.pop();
            }else compiled = false;
          }
          prog[n++] = c;
        }
      }
    }
    //printf("The program is:\n %s\n", prog);
    if (!compiled || stk.size()) printf("COMPILE ERROR");
    else run(0, 0);
    printf("\n");
  }
  return 0;
}
