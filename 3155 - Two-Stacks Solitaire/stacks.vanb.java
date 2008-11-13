//Robado de: http://contests.vanb.org/2005regionals/9-25/
import java.io.*;
import java.util.*;
import java.text.*;

class stacks
{
    public BufferedReader br;
    public PrintStream ps;

    public String toString()
    {
        return "stacks";
    }

    public String pips = "123456789TJQK";
    public String suits = "HCDS";

    public int value( String card )
    {
        int p = pips.indexOf( card.charAt(0) );
        int s = suits.indexOf( card.charAt(1) );
        return s*13+p;
    }

    public Stack<Integer> stack1, stack2, deck;
    public int p, counts[];
    public LinkedList<String> solution, sofar;

    public void movecard()
    {
        if( solution==null )
        {
            if( deck.size()==0 && stack1.size()==1 && stack2.size()==1 )
            {
                solution = new LinkedList( sofar );
            }
            else
            {

                int top1 = stack1.peek();
                int top2 = stack2.peek();

                if( top1==p )
                {
                    stack1.pop();
                    sofar.add( "pop 1" );
                    --counts[p];
                    while( p<53 && counts[p]==0 ) ++p;

                    movecard();

                    p=top1;
                    ++counts[p];
                    stack1.push( top1 );                     
                    sofar.removeLast();
                }
                else if( top2==p )
                {
                    stack2.pop();
                    sofar.add( "pop 2" );
                    --counts[p];
                    while( p<53 && counts[p]==0 ) ++p;

                    movecard();

                    p=top2;
                    ++counts[p];
                    stack2.push( top2 );                     
                    sofar.removeLast();
                }
                else if( deck.size()>0 )
                {
                    int card = deck.pop();

                    if( card==p )
                    {
                        sofar.add( "push 1" );
                        sofar.add( "pop 1" );
                        --counts[p];
                        while( p<53 && counts[p]==0 ) ++p;

                        movecard();

                        sofar.removeLast();
                        sofar.removeLast();
                        p=card;
                        ++counts[p];
                    }
                    else
                    {
                        if( card<=top1 )
                        {
                            stack1.push( card );
                            sofar.add( "push 1" );

                            movecard();

                            stack1.pop();
                            sofar.removeLast();
                        }

                        if( card<=top2 )
                        {
                            stack2.push( card );
                            sofar.add( "push 2" );

                            movecard();

                            stack2.pop();
                            sofar.removeLast();
                        }
                    }
                    deck.push( card );
                }
            }
        }
    }

    public void doit() throws Exception
    {
        br = new BufferedReader( new FileReader( "stacks.in" ) );
        // br = new BufferedReader( new InputStreamReader( System.in ) );
        ps = new PrintStream( new FileOutputStream( "stacks.sol" ) );
        // ps = System.out;
        int i, j, k;
        String tokens[];

        int nsets = 0;

        for(;;)
        {
            int n = Integer.parseInt( br.readLine().trim() );
            if( n==0 ) break;

            ++nsets;

            deck = new Stack<Integer>();
            counts = new int[53];
            Arrays.fill( counts, 0 );
            tokens = br.readLine().trim().split( "\\s+" );
            for( i=0; i<n; i++ )
            {
                int card = Integer.parseInt( tokens[i] );
                deck.push( card );
                ++counts[card];
            }

            p=0;
            while( counts[p]==0 ) ++p;

            solution = null;
            sofar = new LinkedList<String>();
            stack1 = new Stack<Integer>();
            stack2 = new Stack<Integer>();
            stack1.push( 100 );
            stack2.push( 100 );

            movecard();

            ps.println( "#" + nsets );
            if( solution==null )
            {
                ps.println( "impossible" );
            }
            else
            {
                for( String step : solution )
                {
                    ps.println( step );
                }
            }
        }
    }

    public static void main( String args[] ) throws Exception
    {
        (new stacks()).doit();
    }
};
