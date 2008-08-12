#include <iostream>
#include <fstream>

using namespace std;

int nVertices;

struct Point {
  double x;
  double y;
};

ostream& operator<< (ostream& out, Point p)
{
  out << "(" << p.x << ", " << p.y << ")";
  return out;
}


Point* vertices = 0; 
double pegSize;
Point pegPosition;

bool debugging = false;



double edgeEval (int edgeNum, Point p)
{
  Point p1 = vertices[edgeNum];
  Point p2 = vertices[(edgeNum + 1) % nVertices];

  double r = (p1.y - p2.y)*(p.x - p2.x) - (p.y - p2.y)*(p1.x - p2.x);
  return r;
}


Point center()
{
  Point p = {0.0, 0.0};
  for (int i = 0; i < nVertices; ++i)
    {
      p.x += vertices[i].x;
      p.y += vertices[i].y;
    }
  p.x /= (double)nVertices;
  p.y /= (double)nVertices;
  return p;
}


bool testForConvexity()
{
  Point c = center();
  for (int v = 0; v < nVertices; ++v)
    for (int e = 0; e < nVertices; ++e)
      {
	double rc = edgeEval(e, c);
	double rv = edgeEval(e, vertices[v]);
	if (rc * rv < 0.0)
	  return false;
      }
  return true;
}

double distSqr(Point p1, Point p2)
{
  return ((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

double dist(Point p1, Point p2)
{
  return sqrt(distSqr(p1, p2));
}


Point closestPoint (int edgeNum, Point p3)
{
  Point p1 = vertices[edgeNum];
  Point p2 = vertices[(edgeNum+1) % nVertices];
  double u = (p3.x - p1.x) * (p2.x - p1.x) + (p3.y - p1.y) * (p2.y - p1.y);
  u = u / distSqr(p1, p2);
  if (debugging)  cerr << "u = " << u << endl;
  if (u < 0.0)
    return p1;
  else if (u > 1.0)
    return p2;
  else
    {
      Point p;
      p.x = p1.x + u * (p2.x - p1.x);
      p.y = p1.y + u * (p2.y - p1.y);
      return p;
    }
}



bool testPegPosition()
{
  double peg2 = (pegSize*pegSize);
  for (int e = 0; e < nVertices; ++e)
    {
      Point p = closestPoint(e, pegPosition);
      double d = distSqr(pegPosition,p);
      if (d < peg2)
	return false;
    }
  Point c = center();
  for (int e = 0; e < nVertices; ++e)
    {
      double rc = edgeEval(e, c);
      double rp = edgeEval(e, pegPosition);
      if (rc * rp < 0.0)
	return false;
    }
  return true;
}
  



void holes (istream& in)
{
  in >> nVertices;
  while (nVertices > 2)
    {
      in >> pegSize >> pegPosition.x >> pegPosition.y;
      if (debugging)
	cerr << nVertices << " "
	     << pegSize << " "
	     << pegPosition << endl;
      delete [] vertices;
      vertices = new Point[nVertices];

      for (int i = 0; i < nVertices; ++i)
	{
	  in >> vertices[i].x >> vertices[i].y;
	  if (debugging)
	    cerr << vertices[i] << endl;
	}


      if (testForConvexity())
	{
	  if (testPegPosition())
	    cout << "PEG WILL FIT" << endl;
	  else
	    cout << "PEG WILL NOT FIT" << endl;
	}
      else
	cout << "HOLE IS ILL-FORMED" << endl;

      in >> nVertices;
    }
}


int main (int argc, char** argv)
{
  if (argc > 1)
    {
      ifstream in (argv[1]);
      debugging = true;
      holes(in);
    }
  else
    holes(cin);

  return 0;
}
