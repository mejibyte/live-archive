/* NWERC 2007: Sample solution to "Cat vs. Dog"
 * Author: Per Austrin
 *
 * Algorithm:
 * 
 * It might be tempting to consider a graph where the cats and dogs
 * are vertices and the voters are directed edges.  The problem then
 * asks for a Maximum Directed Cut in this graph.  However, a better
 * approach to the problem (and the only one I know of that works), is
 * the following: Consider instead a graph where each voter is a
 * vertex, and there is an edge between two voters if their votes are
 * in conflict (i.e. if both cannot be satisfied simultaneously).  It
 * is not hard to see that what the problem asks for is the size of a
 * maxmimum independent set in this graph.  It is also not hard to see
 * that the graph is bipartite.  Recalling some graph theory, this
 * implies that the size of a maximum independent set is given by the
 * number of nodes minus the size of a maximum matching.  What remains
 * is then to implement your favorite bipartite matching algorithm.
 * This code uses Ford-Fulkerson with DFS.
 *
 * This program also checks that the range of the inputs adhere to the
 * problem statement.  However, it does not check formatting of the
 * inputting file.
 * 
 */
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;

int n;
int cap[600][600];
int visited[600];

/* Find an augmenting path from s to t in the flow graph using DFS.
 * Returns amount of flow added.
 */
int augment(int s, int t, int c) {
  if (s == t) return c;
  visited[s] = true;
  for (int x = 0; x < n+2; ++x) {
    if (cap[s][x] && !visited[x]) {
      // If there is capacity to an unvisited node, try to augment that way.
      int add = augment(x, t, min(c, cap[s][x]));
      if (add) {
	// Augmenting path found, update capacities
	cap[s][x] -= add;
	cap[x][s] += add;
	return add;
      }
    }
  }
  return 0;
}

/* Ford-Fulkersons algorithm for finding the maximum flow from s to t.
 * Returns the total maximum flow that could be added.
 */
int max_flow(int s, int t) {
  int totflow = 0, addflow = 0;
  do {
    memset(visited, 0, sizeof(visited));
    addflow = augment(s, t, 1<<28);
    totflow += addflow;
  } while (addflow);
  return totflow;
}

void solve(int P) {
  int c, d;
  cin >> c >> d >> n;

  assert(1 <= c && c <= 100);
  assert(1 <= d && d <= 100);
  assert(0 <= n && n <= 500);

  vi inedges[250], outedges[250];
  int side[600];
  
  for (int i = 0; i < n; ++i) {
    char ca, cb;
    int a, b;
    cin >> ca >> a >> cb >> b;
    assert(1 <= a && (ca == 'C' && a <= c || ca == 'D' && a <= d));
    assert(1 <= b && (cb == 'C' && b <= c || cb == 'D' && b <= d));
    assert(ca != cb);
    if (ca == 'D') a += c;
    if (cb == 'D') b += c;
    inedges[b].push_back(i);
    outedges[a].push_back(i);
    side[i] = (a>b);
  }

  memset(cap, 0, sizeof(cap));
  for (int i = 0; i < 250; ++i)
    for (vi::iterator it = outedges[i].begin(); it != outedges[i].end(); ++it)
      for (vi::iterator jt = inedges[i].begin(); jt != inedges[i].end(); ++jt)
	if (side[*it] == 0) cap[*it][*jt] = 1;
	else cap[*jt][*it] = 1;

  int s = n;
  int t = n+1;

  /* Add edges to sink and from source.
   */
  for (int i = 0; i < n; ++i) {
    if (side[i] == 0) cap[s][i] = 1;
    else cap[i][t] = 1;
  }
  
  int f = max_flow(s, t);
  
  printf("%d\n", n-f);
}


int main(void) {
  int T;
  scanf("%d", &T);
  for (int i = 1; i <= T; ++i) 
    solve(i);
  return 0;
}
