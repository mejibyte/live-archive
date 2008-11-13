/*
 * Two-Stack Sorting -- Solution Verifier Program
 *
 * by Guilherme Ottoni
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE_NAME "2stacks.in"

#define MAX_CARDS    210
#define INFINITE    1000

#define MIN(X,Y) ((X)<(Y) ? (X) : (Y))

int n;
int value[MAX_CARDS];
char conflicts[MAX_CARDS][MAX_CARDS];
int stack_num[MAX_CARDS];
int min_after[MAX_CARDS];
int test_num=0;
int order[MAX_CARDS];
int next_in, next_out;
FILE *response_file;

typedef struct {
  int elems[MAX_CARDS];
  int size;
} Stack;


void usage()
{
  printf("Usage: 2stacks-verifier output-file\n\n");
  exit(1);
}

void incorrect()
{
  printf("INCORRECT -- failed test case %d\n", test_num);
  fclose(response_file);
  exit(1);
}

void initialize(Stack *s)
{
  s->size = 0;
}

int empty(Stack *s)
{
  return s->size == 0;
}

void push(Stack *s, int v)
{
  s->elems[(s->size)++] = v;
}

int pop(Stack *s)
{
  return s->elems[--(s->size)];
}

int top(Stack *s)
{
  return s->elems[s->size - 1];
} 

int dfs_bipartite(int i, int stack)
{
  int j;

  /* if i was already assigned to a stack, return success iff it was the 
     correct stack */
  if (stack_num[i] != -1)
    return stack_num[i] == stack;

  stack_num[i] = stack;

  /* try to put every node j conflicting with i in the opposite stack */
  for (j = 0; j < n; j++)
    if (conflicts[i][j])
      if (dfs_bipartite(j, 1 - stack) == 0)
	return 0;

  /* if reached here, then succeeded */
  return 1;
}

int bipartite()
{
  int i;
  memset(stack_num, -1, sizeof(stack_num));
  
  /* check each connected component */
  for (i = 0; i < n; i++)
    if (stack_num[i] == -1)
      if (dfs_bipartite(i, 0) == 0)
	return 0;

  return 1;
}

int impossible()
{
  int i, j;

  /* fill in min value appearing after each element */
  min_after[n-1] = INFINITE;
  for (i = n-2; i >= 0; i--)
    min_after[i] = MIN(value[i+1], min_after[i+1]);
  
  /* create conflict graph */
  memset(conflicts, 0, sizeof(conflicts));
  
  for (i = 0; i < n-2; i++)
    for (j = i+1; j < n-1; j++)
      if (value[i] < value[j] && min_after[j] < value[i])
	conflicts[i][j] = conflicts[j][i] = 1;
  
  return !bipartite();
}

void simulate_operation(Stack stacks[2], char *oper, int stack)
{
  if (stack != 1 && stack != 2)
    incorrect();

  if (strcmp(oper, "push") == 0) {
    if (next_in >= n)
      incorrect();
    push(&stacks[stack-1], value[next_in++]);
  }
  else if (strcmp(oper, "pop") == 0) {
    if (empty(&stacks[stack-1]))
      incorrect();
    order[next_out++] = pop(&stacks[stack-1]);
  }
  else
    incorrect();
}

void check_order()
{
  int i;
  for (i = 0; i < n-1; i++)
    if (order[i] > order[i+1])
      incorrect();
}

int main(int argc, char *argv[])
{
  int i;
  Stack stacks[2];
  int intval;
  char strval[10000];

  if (argc != 2) {
    usage();
  }

  if (freopen(INPUT_FILE_NAME, "r", stdin) == NULL) {
    printf("Error: failed to open input file %s\n\n", INPUT_FILE_NAME);
    usage();
  }
  
  if ((response_file = fopen(argv[1], "r")) == NULL) {
    printf("Error: failed to open response-file %s\n\n", argv[1]);
    usage();
  }

  while (scanf("%d", &n) == 1 && n > 0) {

    test_num++;
    
    for (i = n-1; i >= 0; i--)
      scanf("%d", &value[i]);
    
    if (fscanf(response_file, " #%d", &intval) != 1 || intval != test_num)
      incorrect();

    if (fscanf(response_file, "%s", strval) != 1) 
      incorrect();

    if (strcmp(strval, "impossible") == 0) {
      if (!impossible())
	incorrect();
    }
    else {
      if (fscanf(response_file, "%d", &intval) != 1)
	incorrect();

      initialize(&stacks[0]);
      initialize(&stacks[1]);
      next_out = 0;
      next_in = 0;

      simulate_operation(stacks, strval, intval);
      for (i = 1; i < 2*n; i++) {
	if (fscanf(response_file, "%s %d", strval, &intval) != 2)
	  incorrect();
	simulate_operation(stacks, strval, intval);
      }

      check_order();
    }

  }
  
  fclose(response_file);
  printf("CORRECT\n");
  return 0;
}
