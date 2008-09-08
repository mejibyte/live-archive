import java.util.*;

public class a1 {
	public static Scanner in = new Scanner(System.in);
	
	public class Comp {
		public String type,name; int qual,price;
		public Comp(String type,String name,int price,int qual) { this.type=type; this.name=name; this.qual=qual; this.price=price; }
		public String toString() { return type+" "+name+" "+qual+" "+price; }
	}
	
	public int calc(Comp[] comps,int want) {
		int ret=0;
		Set<String> done=new HashSet<String>();
		for(int i=0;i<comps.length;++i) {
			if(done.contains(comps[i].type)) continue;
			done.add(comps[i].type);
			int cur=Integer.MAX_VALUE;
			for(int j=i;j<comps.length;++j) if(comps[i].type.equals(comps[j].type)&&comps[j].qual>=want) cur=Math.min(cur,comps[j].price);
			if(cur==Integer.MAX_VALUE) return cur;
			ret+=cur;
		}
		return ret;
	}
	
	public void run() {
		int n=in.nextInt(),have=in.nextInt();
		Comp[] comps=new Comp[n];
		for(int i=0;i<n;++i) comps[i]=new Comp(in.next(),in.next(),in.nextInt(),in.nextInt());
		
		int l=0,h=1000000001;
		while(l+1<h) {
			int m=l+(h-l)/2;
			if(calc(comps,m)<=have) l=m; else h=m;
		}
		System.out.println(l);
	}
	
	public static void main(String[] args) {
		int n=in.nextInt(); for(int i=0;i<n;++i) new a1().run();
	}
}
