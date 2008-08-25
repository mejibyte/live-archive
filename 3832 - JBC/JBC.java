/*
  Utiliza BigInteger y no compila en el Live Archive.
 */

import java.io.*;
import java.util.*;
import java.math.*;

public class JBC {

        public static int damePos(String orden, char c){
                //System.out.println("Orden es " + orden + " c es : " + c);
                return (int)orden.indexOf(c);
        }

        public static void main(String[] args) throws FileNotFoundException{
                System.setIn(new FileInputStream("JBC.in"));
                Scanner cin = new Scanner(System.in);

                boolean firstCase = true;
                String order = null;
                while (cin.hasNextLine()){
                        order = cin.nextLine();
                        if (!order.equals("")) break;
                }
                if (order == null || order.equals("")) return;

                while (true){
                        if (!firstCase) System.out.println("");
                        firstCase = false;
                        String s = "";
                        //System.out.println("Order es: " + order);
                        for (int i=0; i<order.length(); ++i){
                                if ((order.charAt(i)>' ')){
                                        //System.out.println(order.charAt(i));
                                        s = s + order.charAt(i) + "";
                                }
                        }
                        order = s;
                        //System.out.println("Order es: " + order);

                        String number = null;
                        while (cin.hasNextLine()){
                                number = cin.nextLine();
                                if (number.equals("")) break;
                                s = "";
                                for (int i=0; i<number.length(); ++i){
                                        if (number.charAt(i) > ' '){
                                                s = s + number.charAt(i);
                                        }
                                }
                                number = s;

                                BigInteger ans = BigInteger.ZERO;
                                int grande = 0;
                                for (int i=0; i<number.length(); ++i){
                                        int t = damePos(order, number.charAt(i));
                                        //System.out.println("t es " + t);
                                        if (t > grande) grande = t;
                                }

                                //System.out.println("Number es " + number);
                                //System.out.println("Grande es " + grande);
                                for (int i=grande+1; i<=order.length(); ++i){
                                        BigInteger pow = BigInteger.ONE;

                                        for (int j=number.length()-1; j >=0; --j){
                                                int bk = damePos(order, number.charAt(j));
                                                BigInteger t = new BigInteger(String.valueOf(bk));
                                                ans = ans.add(pow.multiply(t));
                                                pow = pow.multiply(new BigInteger(String.valueOf(i)));
                                        }
                                }
                                System.out.println(ans.toString());
                        }                   order = null;
                        while (cin.hasNextLine()){
                                order = cin.nextLine();
                                if (!order.equals("")) break;
                        }
                        if (order == null || order.equals("")) return;
                }
        }
}
