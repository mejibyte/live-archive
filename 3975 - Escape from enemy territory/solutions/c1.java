/*
  Solution in Java for problem Containers3
  for NWEPC2007
  author: P.G.Kluit
  March 2007
  Last update: August 2007
*/

import java.io.*;

public class c1{
   private static String infile = "testdata.in";

    public static void main (String [] args){
       run(args);
    }

    private static void run(String [] args){
        if (args.length > 0) // another inputfile can be given
              infile = args[0]; // as command line argument
        try{
           BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
           String regel = br.readLine();
           int cases = Integer.parseInt(regel);
           for(int k = 0; k < cases; k++){
                regel = br.readLine();
                long num = Long.parseLong(regel);
                ContainerParking c = new ContainerParking(num);
                c.solve();
                System.out.println(c.getSolution());
           }
        }
        catch (IOException iox){
            System.err.println(iox.toString());
        }
    }
}

class ContainerParking{
    long noOfStacks;
    Dimension solution;

    public ContainerParking(long m){
       long no = m / 5;
       if (m % 5 > 0)
         no++;
       noOfStacks = no;
    }

    public void solve(){

       long b = noOfStacks + 1;
       for  (long a = 1; a < b; a++){
          b = noOfStacks / a;

          while (a * b < noOfStacks)
            b++;
          Dimension test = new Dimension(10 * a + 2, 44 * b + 4);
          if (test.betterThan(solution))
             solution = test;
          test = new Dimension(10 * b + 2, 44 * a + 4);
          if (test.betterThan(solution))
             solution = test;
       }
    }

    public Dimension getSolution(){
       return solution;
    }
}

class Dimension{
   long length, width;
   public Dimension (long x, long y){
      if (x > y){
          length = x;
          width = y;
      }
      else{
         length = y;
         width = x;
      }
   }

   public boolean betterThan(Dimension that){
      if (that == null)
         return true;
      if (this.area() < that.area())
         return true;
      if (this.area() > that.area())
         return false;
      return this.length - this.width < that.length - that.width;
   }

   public String toString(){
      return length + " X " + width + " = " + area();
   }

   public long area (){
     return length * width;
   }
}
