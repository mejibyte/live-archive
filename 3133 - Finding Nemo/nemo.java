//Stolen from: http://contests.vanb.org/2005finals/3-13/
import java.io.*;
import java.util.*;
import java.awt.*;
import java.text.*;

public class nemo
{
    public BufferedReader br;
    public PrintStream ps;

    public String toString()
    {
        return "nemo";
    }

    public static final int OPEN = 0;
    public static final int WALL = 1;
    public static final int DOOR = 2;

    public class Cell
    {
        public int steps, top, bottom, left, right;

        public Cell()
        {
            reset();
        }

        public void reset()
        {
            steps = -1;
            top = bottom = left = right = OPEN;
        }
    };

    public void dump( Cell sea[][] )
    {
        DecimalFormat df = new DecimalFormat( "00" );
        int i, j;
        for( i=200; i>=0; i-- )
        {
            String s;
            for( j=0; j<201; j++ )
            {
                s = sea[i][j].top==OPEN ? "  "
                  : sea[i][j].top==WALL ? "--"
                  : sea[i][j].top==DOOR ? ".." : "??";

                ps.print( "+" + s + "+");
            }
            ps.println();
            for( j=0; j<201; j++ )
            {
                s = sea[i][j].left==OPEN ? " "
                  : sea[i][j].left==WALL ? "|"
                  : sea[i][j].left==DOOR ? ":" : "?";
                s += sea[i][j].steps < 0 ? "??" : df.format( sea[i][j].steps );
                s += sea[i][j].right==OPEN ? " "
                   : sea[i][j].right==WALL ? "|"
                   : sea[i][j].right==DOOR ? ":" : "?";


                ps.print( s );
            }
            ps.println();
            for( j=0; j<201; j++ )
            {
                s = sea[i][j].bottom==OPEN ? "  "
                  : sea[i][j].bottom==WALL ? "--"
                  : sea[i][j].bottom==DOOR ? ".." : "??";

                ps.print( "+" + s + "+");
            }
            ps.println();
        }
    }

    public void doit() throws Exception
    {
        br = new BufferedReader( new FileReader( "nemo.in" ) );
        ps = new PrintStream( new FileOutputStream( "nemo.sol" ) );
        //ps = System.out;
        int i, j, k;
        String tokens[];

        Cell sea[][] = new Cell[201][201];
        for( i=0; i<201; i++ )for( j=0; j<201; j++ )
        {
            sea[i][j] = new Cell();
        }

        for(;;)
        {
            tokens = br.readLine().trim().split( "\\s+" );
            int n = Integer.parseInt( tokens[0] );
            int m = Integer.parseInt( tokens[1] );
            if( n==-1 && m==-1 ) break;

            for( i=0; i<201; i++ )for( j=0; j<201; j++ )
            {
                sea[i][j].reset();
            }

            for( i=0; i<n; i++ )
            {
                tokens = br.readLine().trim().split( "\\s+" );
                int x = Integer.parseInt( tokens[0] );
                int y = Integer.parseInt( tokens[1] );
                int d = Integer.parseInt( tokens[2] );
                int t = Integer.parseInt( tokens[3] );

                if( d==0 )
                {
                    for( j=0; j<t; j++ )
                    {
                        sea[y][x+j].bottom = WALL;
                        sea[y-1][x+j].top = WALL;
                    }
                }
                else
                {
                    for( j=0; j<t; j++ )
                    {
                        sea[y+j][x].left = WALL;
                        sea[y+j][x-1].right = WALL;
                    }
                }
            }

            for( i=0; i<m; i++ )
            {
                tokens = br.readLine().trim().split( "\\s+" );
                int x = Integer.parseInt( tokens[0] );
                int y = Integer.parseInt( tokens[1] );
                int d = Integer.parseInt( tokens[2] );

                if( d==0 )
                {
                    sea[y][x].bottom = DOOR;
                    sea[y-1][x].top = DOOR;
                }
                else
                {
                    sea[y][x].left = DOOR;
                    sea[y][x-1].right = DOOR;
                }
            }

            tokens = br.readLine().trim().split( "\\s+" );
            int nx = (int)Math.floor( Double.parseDouble( tokens[0] ) );
            int ny = (int)Math.floor( Double.parseDouble( tokens[1] ) );

            if( nx>200 ) nx = 200;
            if( nx<0 ) nx = 0;
            if( ny>200 ) ny = 200;
            if( ny<0 ) ny = 0;

            LinkedList oldpts;
            LinkedList newpts = new LinkedList();
            newpts.add( new Point( 0, 0 ) );
            int doors = -1;
            while( sea[ny][nx].steps==-1 && newpts.size() > 0 )
            {
                oldpts = newpts;
                newpts = new LinkedList();
                ++doors;
                while( oldpts.size() > 0 )
                {
                    Point p = (Point)oldpts.removeFirst();
                    if( sea[p.y][p.x].steps==-1 )
                    {
                        sea[p.y][p.x].steps = doors;
                        if( sea[p.y][p.x].top==OPEN && p.y<200 )
                        {
                            if( sea[p.y+1][p.x].steps==-1 ) oldpts.add( new Point( p.x, p.y+1 ) );
                        }
                        if( sea[p.y][p.x].bottom==OPEN && p.y>0 )
                        {
                            if( sea[p.y-1][p.x].steps==-1 ) oldpts.add( new Point( p.x, p.y-1 ) );
                        }
                        if( sea[p.y][p.x].left==OPEN && p.x>0 )
                        {
                            if( sea[p.y][p.x-1].steps==-1 ) oldpts.add( new Point( p.x-1, p.y ) );
                        }
                        if( sea[p.y][p.x].right==OPEN && p.x<200 )
                        {
                            if( sea[p.y][p.x+1].steps==-1 ) oldpts.add( new Point( p.x+1, p.y ) );
                        }
                        if( sea[p.y][p.x].top==DOOR && p.y<200 )
                        {
                            if( sea[p.y+1][p.x].steps==-1 ) newpts.add( new Point( p.x, p.y+1 ) );
                        }
                        if( sea[p.y][p.x].bottom==DOOR && p.y>0 )
                        {
                            if( sea[p.y-1][p.x].steps==-1 ) newpts.add( new Point( p.x, p.y-1 ) );
                        }
                        if( sea[p.y][p.x].left==DOOR && p.x>0 )
                        {
                            if( sea[p.y][p.x-1].steps==-1 ) newpts.add( new Point( p.x-1, p.y ) );
                        }
                        if( sea[p.y][p.x].right==DOOR && p.x<200 )
                        {
                            if( sea[p.y][p.x+1].steps==-1 ) newpts.add( new Point( p.x+1, p.y ) );
                        }
                    }
                }
            }

            //dump( sea );
            ps.println( sea[ny][nx].steps );
        }
    }

    public static void main( String args[] ) throws Exception
    {
        (new nemo()).doit();
    }
};
