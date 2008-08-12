#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <ctype.h>
#include <climits>

using namespace std;

/*
 * DEBUG ONLY: If compiled with -DDEBUG, each dataset will be printed back out
 * to stderr with all bricks on the shortest path marked with lowercase letters.
 */

/* Maximum width and height allowed by the problem statement */
#define ROWS 20
#define COLS 20

/* A convenient way to represent a single coordinate */
typedef pair<int, int> point;

/* Number of cells adjacent to any other given cell */
#define DIRS 4

/* Movement cost used as starting point for shortest path algorithm */
#define MAXCOST INT_MAX

/* List of all possible directions that one can move from one cell to another */
point dir[] = {
    point(  0, -1 ),
    point(  0, +1 ),
    point( -1,  0 ),
    point( +1,  0 ),
};

/* Data structure representing a single unit in the wall */
typedef struct cell_s {
    char letter;  /* Letter assigned to this unit as read in from the input */

    /* These fields are used by Dijkstra's algorithm in shortest_path() */
    point prev;   /* DEBUG ONLY: Coordinate of previous cell on shortest path */
    int cost;     /* Tentative shortest path cost to this cell */
} cell_t;

/* Array representing the entire wall */
cell_t wall[ROWS][COLS];

/* Wall height and width for current data set */
int rows, cols;

/*
 * Comparison function object required for priority_queue<point> in
 * shortest_path. Since each point in the queue refers to a specific cell_t in
 * the grid, this function object compares the costs associated with the two
 * cells. A greater than (>) comparison produces a priority queue with the
 * smallest cost node on top.
 */
class cost_compare {
    public:
        inline bool operator()(point const &a, point const &b) const
        {
            int cost1 = wall[a.first][a.second].cost;
            int cost2 = wall[b.first][b.second].cost;
            return cost1 > cost2;
        }
};

#ifdef DEBUG
/*
 * DEBUG ONLY: This function implements a simple recursive flood fill algorithm
 * that starts at unit [row][col] in the wall and changes wall[i][j].letter to
 * lowercase for every (ith, jth) adjacent wall unit that is part of the same
 * brick (i.e. based on the letter "match"). Used for debug outout to show which
 * bricks have to be removed on the shortest path.
 */
void flood_fill(int row, int col, char match)
{
    /* Stop recursing if coordinate (row, col) is outside of the wall */
    if(row < 0 || col < 0 || row >= rows || col >= cols) {
        return;
    }
    
    char &letter = wall[row][col].letter;
    
    /* Stop if this is not the unit we're looking for */
    if(letter != match) {
        return;
    }
    
    /* Stop if this wall unit has already been converted to lowercase */
    if(islower(letter)) {
        return;
    }
    
    /* Convert this wall unit's letter to lowercase */
    letter = tolower(letter);
    
    /* Recursively flood fill all neighbors of this unit */
    for(int i = 0; i < DIRS; i++) {
        flood_fill(row + dir[i].first, col + dir[i].second, match);
    }
}

/*
 * DEBUG ONLY: Print out the overall shortest path in the wall by converting
 * all bricks along that path to lowercase letters. This function makes use of
 * flood_fill() to mark every brick along the shortest path starting from
 * the brick at column "endcol" in the bottom most row.
 */
void print_path(int endcol)
{
    /* Starting location for shortest path in the bottom most row */
    point loc(rows - 1, endcol);
    
    /* Follow the shortest path in reverse, marking every brick along the way */
    while(loc != point(-1, -1)) {
        int row = loc.first;
        int col = loc.second;
        
        flood_fill(row, col, wall[row][col].letter);
        loc = wall[row][col].prev;
    }

    /* Print out brick letter grid after marking the shortest path on it */
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            cerr << wall[row][col].letter;
        }
        cerr << endl;
    }
}
#endif

/*
 * Run Dijkstra's algorithm starting with the cell at column "start" in the
 * top row, and return the shortest path found to any cell in the bottom row.
 * DEBUG ONLY: If the "print" flag is specified, the shortest path is printed
 * out to stderr.
 */
int shortest_path(int start, bool print)
{
    /* Priority queue for picking the next least cost wall unit */
    priority_queue<point, vector<point>, cost_compare> queue;

    /* Initialize data grid */
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            wall[row][col].prev = point(-1, -1);
            wall[row][col].cost = MAXCOST;
        }
    }

    /* Setup the starting cell as required by Dijkstra's algorithm */
    wall[0][start].cost = 1;
    queue.push( point(0, start) );

    /* Keep running Dijkstra until all nodes are visited */
    while(!queue.empty()) {
    
        /* Remove the closest cell from the priority queue */
        int row = queue.top().first;
        int col = queue.top().second;
        queue.pop();
        
        /* Check all adjacent cells to this one */
        for(int i = 0; i < DIRS; i++) {
            int cost;
            
            /* The coordinate of the adjacent cell */
            int newrow = row + dir[i].first;
            int newcol = col + dir[i].second;
            
            /* Skip this coordinate point if it's outside the wall */
            if(newrow < 0 || newcol < 0 || newrow >= rows || newcol >= cols) {
                continue;
            }

            /* Edge cost is 0 to same brick and 1 to different brick */
            cost = wall[row][col].letter == wall[newrow][newcol].letter ? 0 : 1;
            
            /* Check if real cost is smaller than tentative cost */
            if(wall[row][col].cost + cost < wall[newrow][newcol].cost) {

                /* Adjust tentative cost and enqueue adjacent cell */
                wall[newrow][newcol].cost = wall[row][col].cost + cost;
                wall[newrow][newcol].prev = point(row, col);
                queue.push( point(newrow, newcol) );
            }                
        }
    }

    int mincost = MAXCOST;
    int endcol = 0;
        
    /* Return the shortest path found to any bottom row from "start" column */
    for(int col = 0; col < cols; col++) {
        int cost = wall[rows - 1][col].cost;

        if(cost < mincost) {
            mincost = cost;
            endcol = col;
        }
    }
    
#ifdef DEBUG
    /* DEBUG ONLY: Print out the overall shortest path */
    if(print) {  
        print_path(endcol);
    }
#endif

    return mincost;
}

/*
 * Compute and return the minimum number of bricks that have to be removed to
 * create a gap in the wall. The entire wall can be treated as a graph where
 * each wall unit (or cell) is a node in the graph and there exists an edge
 * from every cell to each of the 4 adjacent cells. If that edge leads to a
 * cell with the same letter (and therefore part of the same brick), then the
 * cost of that edge is 0; if the edge leads to a different brick the edge
 * cost is 1. Computing all pairs shortest paths and then finding the minimum
 * length path between any cell in the top row and any cell in the bottom row,
 * will give the minimum number of bricks to remove.
 *
 * In this solution Dijkstra's algorithm is run once for each of the cells in
 * the top most row to obtain the same result.
 *
 * Potential Optimization: An extra dummy row can be added either on the top
 * or the bottom of the wall. If this row is treated as a single brick that
 * is distinct from all other bricks, then just one pass of Dijkstra's would be
 * enough.
 */
int analyze(void)
{
    int mincost = MAXCOST;
    int startcol = 0;
    
    /* Find shortest path from each top row cell to any bottom row cell */
    for(int col = 0; col < cols; col++) {
        int cost = shortest_path(col, false);
        
        if(cost < mincost) {
            mincost = cost;
            startcol = col;
        }
    }
    
#ifdef DEBUG
    /* DEBUG ONLY: Recompute and print out the overall shortest path */
    shortest_path(startcol, true);
#endif
    
    return mincost;
}

/* Main body of program */
void process(void)
{
    int data_num, data_idx;

    /* Read how many data sets to process */
    cin >> data_num;
    
    /* Process each data set separately */
    for(data_idx = 0; data_idx < data_num; data_idx++) {
        int row, col;
    
        /* Read in the height and width of this wall */
        cin >> rows >> cols;
        
        /* SANITY CHECK: Make sure the wall size is within limits */
        if(rows <= 0 || cols <= 0 || rows > ROWS || cols > COLS) {
            cerr << "Bad wall size: " << rows << " " << cols << endl;
            throw;
        }        
        
        /* Read in the brick wall representation into array */
        for(row = 0; row < rows; row++) {
            for(col = 0; col < cols; col++) {
                char c;
            
                cin >> c;
                wall[row][col].letter = c;
                
                /* SANITY CHECK: Make sure wall units are valid letters */
                if(!isupper(c)) {
                    cerr << "Bad wall unit character: " << c << endl;
                    throw;
                }
            }
        }
        
        /* Compute and printout the smallest number of bricks to remove */
        int mincost = analyze();
        cout << mincost << endl;
#ifdef DEBUG
        cerr << mincost << endl;
#endif
    }
}

/* Run program and print out any exceptions that occur */
int main(void)
{
    /* Throw exceptions on failed data extraction in >> operator */
    cin.exceptions(ios::failbit);
    
    /* Run main body of code */
    try {
        process();
    }
    
    /* Catch unexpected EOF or bad input data */
    catch(exception &e) {
        cerr << "Unexpected EOF or data type mismatch on input" << endl;
    }

    return 0;
}
