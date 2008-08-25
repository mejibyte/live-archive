/*
  Solución oficial robada de http://contests.vanb.org/2005finals/3-13/
 */
import java.io.*;
import java.util.*;
import java.awt.*;

public class color
{
    public BufferedReader br;
    public PrintStream ps;

    public String toString()
    {
        return "color";
    }

    public String dump( int a[] )
    {
        String result = a.length==0 ? "[" : "";
        for( int i=0; i<a.length; i++ )
        {
            result += (i==0?"[":" ") + a[i];
        }
        result += "]" ;
        return result;
    }

    public int[] merge( int a[], int b[] )
    {
        int i, j, k;

        boolean froma[][] = new boolean[a.length+1][b.length+1];
        int cost[][] = new int[a.length+1][b.length+1];
        cost[0][0] = 0;
        froma[0][0] = false;

        for( i=1; i<=a.length; i++ )
        {
            froma[i][0] = true;
            cost[i][0] = cost[i-1][0] + i*a[i-1];
        }

        for( j=1; j<=b.length; j++ )
        {
            froma[0][j] = false;
            cost[0][j] = cost[0][j-1] + j*b[j-1];
        }

        for( i=1; i<=a.length; i++ )for( j=1; j<=b.length; j++ )
        {
            int costa = cost[i-1][j]+(i+j)*a[i-1];
            int costb = cost[i][j-1]+(i+j)*b[j-1];
            if( costa < costb )
            {
                froma[i][j] = true;
                cost[i][j] = costa;
            }
            else
            {
                froma[i][j] = false;
                cost[i][j] = costb;
            }
        }

        int result[] = new int[a.length+b.length];
        i = a.length;
        j = b.length;
        for( k=a.length+b.length-1; k>=0; k-- )
        {
            if( froma[i][j] )
            {
                result[k] = a[--i];
            }
            else
            {
                result[k] = b[--j];
            }
        }

        return result;
    }

    public class Node
    {
        int id, c;
        LinkedList children;
        int o[];

        public Node( int i )
        {
            id = i;
            c = 0;
            children = new LinkedList();
        }

        public String toString()
        {
            return "{Node:id=" + id + ", c=" + c +  ", #children=" + children.size() + "}";
        }

        public void computeOrdering()
        {
            int co[] = new int[0];
            int i, j, k, m, e;

            Iterator it = children.iterator();
            while( it.hasNext() )
            {
                Node child = (Node)it.next();
                child.computeOrdering();

                co = merge( co, child.o );
            }
            o = new int[1+co.length];
            o[0] = c;
            System.arraycopy( co, 0, o, 1, co.length );
        }

    };

    public void doit() throws Exception
    {
        br = new BufferedReader( new FileReader( "color.in" ) );
        ps = new PrintStream( new FileOutputStream( "color.sol" ) );
        //ps = System.out;
        int i, j, k;
        String tokens[];

        for(;;)
        {
            tokens = br.readLine().trim().split( "\\s+" );
            int n = Integer.parseInt( tokens[0] );
            int r = Integer.parseInt( tokens[1] );
            if( n==0 && r==0 ) break;

            --r;

            Node nodes[] = new Node[n];
            tokens = br.readLine().trim().split( "\\s+" );
            for( i=0; i<n; i++ )
            {
                nodes[i] = new Node( i );
                nodes[i].c = Integer.parseInt( tokens[i] );
            }

            for( i=0; i<n-1; i++ )
            {
                tokens = br.readLine().trim().split( "\\s+" );
                int parent = Integer.parseInt( tokens[0] )-1;
                int child = Integer.parseInt( tokens[1] )-1;
                nodes[parent].children.add( nodes[child] );
            }

            nodes[r].computeOrdering();


            int sum = 0;
            for( i=0; i<nodes[r].o.length; i++ )
            {
                sum += nodes[r].o[i]*(i+1);
            }

            ps.println( sum );
            System.out.println( sum );
        }
    }

    public static void main( String args[] ) throws Exception
    {
        (new color()).doit();
    }
};
