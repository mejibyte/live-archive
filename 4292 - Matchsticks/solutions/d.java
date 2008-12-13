import java.util.Scanner;

public class erikjan {
	public static Scanner scanner;
	public static final int MOD=10001;	
	
	public static int mod(int x) { x%=MOD; if(x<0) x+=MOD; return x; }
	
	public static void run() {
		int n=scanner.nextInt();
		int[] in = new int[n];
		for(int i=0;i<n;++i) in[i]=scanner.nextInt();
		for(int a=0;a<10001;++a) {
			int aa=mod(a*a),b;
			if(n==1) {
				b=0;
			} else {
				// in[1]=a*a*in[0]+a*b+b (mod MOD)
				// (a+1)*b=in[1]-a*a*in[0]) (mod MOD)
				// s*b=t (mod MOD)
				int s=mod(a+1),t=mod(in[1]-aa*in[0]);
				EGcd res=new EGcd(s,MOD);
				int g=res.gcd;
				if(t%g!=0) continue;
				b=mod((t/g)*mod(res.a));
			}
			
			boolean ok=true;
			for(int i=1;i<n;++i) if(mod(a*mod(a*in[i-1]+b)+b)!=in[i]) { ok=false; break; }
			if(!ok) continue;
			
//			System.err.println("a="+a+", b="+b);
			for(int i=0;i<n;++i) System.out.println(mod(a*in[i]+b));
			
			return;
		}
		throw new RuntimeException("Invalid");
	}
	
	public static void main(String[] args) {
		scanner=new Scanner(System.in);
		run();		
	}
}

// a*x+b*y=gcd
class EGcd {
	public int a,x,b,y,gcd;
	
	public EGcd(int x,int y) {
		this.x=x; this.y=y;
		if(y==0) {
			this.a=1; this.b=0; this.gcd=x;			
		} else {
			EGcd res=new EGcd(y,x%y);
			this.a=res.b; this.b=res.a-res.b*(x/y); this.gcd=res.gcd;
		}
	}
}