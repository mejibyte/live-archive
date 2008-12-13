import java.util.Scanner;
import java.util.ArrayList;

public class erikjan {
	public static Scanner scanner;
	
	public static P sub(P a,P b) { return new P(a.x-b.x,a.y-b.y); }
	public static int dot(P a,P b) { return a.x*b.x+a.y*b.y; }
	
	public static double dist(P c,P a,P b) {
		double t=1.0*dot(sub(b,a),sub(c,a))/dot(sub(b,a),sub(b,a));
		if(t<0) t=0; if(t>1) t=1;
		double ret=dot(sub(a,c),sub(a,c))+2*t*dot(sub(a,c),sub(b,a))+t*t*dot(sub(b,a),sub(b,a));
		return Math.sqrt(ret);
	}
	
	public static void run() {
		int n1=scanner.nextInt();
		P[] inner=new P[n1];
		for(int i=0;i<n1;++i) {
			int x=scanner.nextInt();
			int y=scanner.nextInt();
			inner[i]=new P(x,y);
		}
		int n2=scanner.nextInt();
		P[] outer=new P[n2];
		for(int i=0;i<n2;++i) {
			int x=scanner.nextInt();
			int y=scanner.nextInt();
			outer[i]=new P(x,y);
		}
		
		double ret=Double.POSITIVE_INFINITY;
		for(int i=0;i<n1;++i)
			for(int j=0;j<n2;++j) {
				ret=Math.min(ret,dist(inner[i],outer[j],outer[(j+1)%n2]));
				ret=Math.min(ret,dist(outer[j],inner[i],inner[(i+1)%n1]));
			}

		System.out.println(ret/2);
	}
	
	public static void main(String[] args) {
		scanner = new Scanner(System.in);
		int n=scanner.nextInt();
		for(int i=0;i<n;++i) run();
	}
}

class P {
	public int x,y;
	
	public P(int x,int y) {
		this.x=x;
		this.y=y;
	}
	
	public String toString() { return "("+x+","+y+")"; }
}