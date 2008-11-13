import java.io.*;
import java.util.*;
import java.text.*;

public class longnight
{
    public BufferedReader br;
    public PrintStream ps;

    public String toString()
    {
        return "longnight";
    }

    public int best;
    public int times[][];
    public int watch[];
    public boolean visited[];
    public boolean seen[][];
    public int n;

    public void snake( int id, int where, int count, int time )
    {
        int i, j;
        if( time <= 420 )
        {
            if( !seen[where][id] )
            {
                seen[where][id] = true;
                if( count>best ) best=count;
                visited[where] = true;

                i = where;
                for( j=0; j<n; j++ ) if( !visited[j] )
                {
                    if( !seen[j][id|(1<<j)] )
                    {
                        snake( id|(1<<j), j, count+1, time+times[i][j]+watch[j] );
                    }
                }

                visited[where] = false;
            }
        }
    }

    public void doit() throws Exception
    {
        //br = new BufferedReader( new FileReader( "longnight.in" ) );
        br = new BufferedReader( new InputStreamReader( System.in ) );
        //ps = new PrintStream( new FileOutputStream( "longnight.sol" ) );
        ps = System.out;
        int i, j, k;
        String tokens[];
        
        for(;;)
        {
            n = Integer.parseInt( br.readLine().trim() );
            if( n==0 ) break;

            watch = new int[n];
            tokens = br.readLine().trim().split( "\\s+" );
            for( i=0; i<n; i++ )
            {
                watch[i] = Integer.parseInt( tokens[i] );
            }

            times = new int[n][n];
            for( i=0; i<n; i++ )
            {
                tokens = br.readLine().trim().split( "\\s+" );
                for( j=0; j<n; j++ )
                {
                    times[i][j] = Integer.parseInt( tokens[j] );
                }
            }

            best = 0;
            seen = new boolean[n][1<<n];
            for( i=0; i<n; i++ )
            {
                Arrays.fill( seen[i], false );
            }

            visited = new boolean[n];
            for( i=0; i<n; i++ )
            {
                Arrays.fill( visited, false );
                snake( 1<<i, i, 1, watch[i] );
            }
 
            ps.println( best );
        }
    }

    public static void main( String args[] ) throws Exception
    {
        (new longnight()).doit();
    }
};
