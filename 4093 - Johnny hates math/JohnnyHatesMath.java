//Robado de https://www.cs.up.ac.za/module.php?spc=cg&module=ACM101
//26343305
import java.util.Scanner;

public class JohnnyHatesMath
{
	public static void main(String[] args)
	{
		Scanner in=new Scanner(System.in);
		String input;
        int count=1;
		while (in.hasNextLine())
		{
			input=in.nextLine();
			if (input.equals("0=0"))
				return;
			int eqPos=input.indexOf("=");
			int result=Integer.parseInt(input.substring(eqPos + 1));
			String digits=input.substring(0,eqPos),answ="";
			for (int terms=digits.length() / 5; terms<digits.length(); terms++)
            {
                answ=findPossibility(digits,result,terms);
                if (answ!=null)
                {
                    System.out.println((count++)+". "+answ+"="+result);
                    break;
                }
            }
            if (answ==null)
                System.out.println((count++)+". IMPOSSIBLE");
		}
	}
	
	public static String findPossibility(String digits,int goal,int terms)
	{
		return findPossibility("",digits,goal,terms);
	}
	
	public static String findPossibility(String expression,String digits,int goal,int terms)
	{
        if (terms==0)
            return goal==0 ? expression : null;
        if ((digits.length() / terms>5) || (goal<=0))
            return null;
		if (terms==1)
			return findPossibility((expression.length()==0 ? "" : expression+"+")+digits,"",goal - Integer.parseInt(digits),0);
        String sub,answ;
        for (int i=1; i<Math.min(6,digits.length()); i++)
        {
            sub=digits.substring(0,i);
            answ=findPossibility((expression.length()==0 ? "" : expression+"+")+sub,digits.substring(i),goal - Integer.parseInt(sub),terms - 1);
            if (answ!=null)
                return answ;
        }
        return null;
	}
}
