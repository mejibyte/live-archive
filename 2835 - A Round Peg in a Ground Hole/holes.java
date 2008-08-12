import java.io.*;
import java.util.*;

class coord {
  double x, y;

  public String toString(){
    return "("+x+","+y+")";
  } 
}

public class holes {

    public static boolean onLeftSide(coord point, coord linea, coord lineb){
	double dy = lineb.y - linea.y;
	double dx = lineb.x - linea.x;
	boolean onLeft;
	
	if(dx == 0){
	    onLeft = point.x < linea.x;
	    if(dy < 0)
		onLeft = !onLeft;
	}
	else{
	    double slope = dy/dx;
	    
	    double lineY = slope*(point.x - linea.x)+linea.y;
	    
	    onLeft = point.y > lineY;

	    if(dx<0 )
		onLeft = !onLeft;

	}


	System.err.println("point "+point+" is on left of "+linea+"-"+lineb+
			   ": "+onLeft);

	return onLeft;
    }


  public static double distPointLine(coord point, coord line, coord slopeV){

    if(slopeV.x == 0)
      return Math.abs(point.x - line.x);
    
    double m = slopeV.y/slopeV.x;
    double a = -m;
    double b = 1;
    double c = m*line.x-line.y;

    return Math.abs(a*point.x+b*point.y+c)/Math.sqrt(a*a+b*b);
  }

  public static coord vector(coord a, coord b){
    coord vector = new coord();
    vector.x = b.x-a.x;
    vector.y = b.y-a.y;
    return vector;
  }
    
  public static double length(double x1, double y1, double x2, double y2){
    return Math.sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
  }

  public static double length(coord vector){
    return Math.sqrt(vector.x*vector.x + vector.y*vector.y);
  }

  public static void main(String[] argv)
    throws Exception {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

    SHAPE:
    while (true){
      coord[] vertices;

      coord peg = new coord();

      StringTokenizer t = new StringTokenizer(in.readLine());
      int Nvert = Integer.parseInt(t.nextToken());
      if(Nvert < 3)
	break;
      double pegRadius = Double.parseDouble(t.nextToken());
      peg.x = Double.parseDouble(t.nextToken());
      peg.y = Double.parseDouble(t.nextToken());

      vertices = new coord[Nvert];

      for(int i=0;i<Nvert;i++){
	vertices[i] = new coord();
	t = new StringTokenizer(in.readLine());
	vertices[i].x = Double.parseDouble(t.nextToken());
	vertices[i].y = Double.parseDouble(t.nextToken());
      }

      double angleSum = 0 ;
      double thisAngle;
      for(int i=0;i<Nvert;i++){
	coord va = vector(vertices[i], vertices[(i+1)%Nvert]);
	coord vb = vector(vertices[(i+1)%Nvert],vertices[(i+2)%Nvert]);
	thisAngle= Math.acos((va.x*vb.x +
			      (va.y*vb.y))/
			     (length(vb)*length(va)));
	thisAngle = Math.toDegrees(thisAngle);
	angleSum+=thisAngle;
	System.err.println("got indiv angle "+thisAngle);
      }
      System.err.println("total "+angleSum);
    
      if(angleSum > 360.01){
	System.out.println("HOLE IS ILL-FORMED");
	continue;
      }

      for(int i=0;i<Nvert;i++){
	double dist = distPointLine(peg, vertices[i], vector(vertices[i],vertices[(i+1)%Nvert]));
	System.err.println("distance of line from "+vertices[i]+" at slope "+
			   vector(vertices[i],vertices[(i+1)%Nvert])+" from peg "+peg+
			   " = "+dist);
	if (dist < pegRadius){
	  System.out.println("PEG WILL NOT FIT");
	  continue SHAPE;
	}

      }

      

      boolean firstLeft = onLeftSide(peg, vertices[Nvert-1],vertices[0]);
      boolean allSame = true;

      for(int i=0;i<Nvert-1;i++){
	  if(onLeftSide(peg, vertices[i],vertices[i+1])!=firstLeft){
	      System.out.println("PEG WILL NOT FIT");
	      continue SHAPE;
	  }
      }


      System.out.println("PEG WILL FIT");
    }
  }
}

