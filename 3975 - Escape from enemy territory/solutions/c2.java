import java.util.*;

public class c2 {
	public static Scanner in=new Scanner(System.in).useLocale(Locale.US);

	public class Result {
		long a,b,val;
		public Result(long a,long b,long val) { this.a=a; this.b=b; this.val=val; }
		public boolean better(Result r) {
			if(this.val!=r.val) return this.val<r.val;
			if(this.a-this.b!=r.a-r.b) return this.a-this.b<r.a-r.b;
			return false;
		}
		public String toString() { return a+" X "+b+" = "+val; }
	}
	
	Result calc(long x,long h) {
		long w=(x+h-1)/h;
		long a=44*w+4,b=10*h+2;
		return new Result(Math.max(a,b),Math.min(a,b),a*b);
	}
	
	public long tmp(long x,long h) {
		long w=x/h;
		long a=44*w+4,b=10*h+2;
		return a*b;
	}

	public void run() {
		long n=in.nextLong();
		long x=(n+4)/5;
		double opth=Math.sqrt(11.0/5.0*x),optw=x/opth;
		long starth=(long)Math.floor(opth);
		Result ret=calc(x,starth);
		double a=40,b=8+440*x-ret.val,c=88*x,d=Math.sqrt(b*b-4*a*c);
		long fromh=Math.max(1,(long)Math.floor((-b-d)/(2*a))),toh=(long)Math.ceil((-b+d)/(2*a));
//		System.out.println(starth+" => "+fromh+".."+toh+" ["+tmp(x,fromh)+" / "+tmp(x,toh)+" "+ret.val+"]");
		for(long h=fromh;h<=toh;h=Math.max(h+1,fromh)) {
			Result cur=calc(x,h);
			if(cur.better(ret)) {
				ret=cur;
				a=40; b=8+440*x-ret.val; c=88*x; d=Math.sqrt(b*b-4*a*c);
				fromh=Math.max(1,(long)Math.floor((-b-d)/(2*a))); toh=(long)Math.ceil((-b+d)/(2*a));
//				System.out.println(h+","+((x+h-1)/h)+" => "+fromh+".."+toh+" ["+tmp(x,fromh)+" / "+tmp(x,toh)+" "+ret+"]");
			}
		}
		System.out.println(ret);
	}
	
	public static void main(String[] args) {
		int n=in.nextInt(); for(int i=0;i<n;++i) new c2().run();
	}
}
