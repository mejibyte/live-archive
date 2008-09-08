import java.util.*;

public class j1 {
	public static Scanner in=new Scanner(System.in).useLocale(Locale.US);
	
	public class Point {
		long x,y;
		public Point(long x,long y) { this.x=x; this.y=y; }
		
		Point min(Point p) { return new Point(this.x-p.x,this.y-p.y); }
		long cross(Point p) { return this.x*p.y-this.y*p.x; }
		long dist2(Point p) { Point d=this.min(p); return d.x*d.x+d.y*d.y; }
				
		int side(Point a,Point b) {
			long ret=b.min(a).cross(this.min(a));
			if(ret<0) return -1; else if(ret>0) return +1; else return 0;
		}
		
		boolean onseg(Point a,Point b) {
			return this.side(a,b)==0&&this.dist2(a)<=a.dist2(b)&&this.dist2(b)<=a.dist2(b);
		}
	}
	
	public class Curve {
		public int h;
		public Point[] p;
	}
	
	public class Intersection implements Comparable<Intersection> {
		public long n,d;
		public int curve;
		public Intersection(long n,long d,int curve) { this.n=n; this.d=d; this.curve=curve; }
		public int compareTo(Intersection i) {
			if(1.0*n*i.d<1.0*d*i.n) return -1;
			if(1.0*n*i.d>1.0*d*i.n) return +1;
			return 0;
		}
	}
	
	public void run() {
		int n=in.nextInt();
		Curve[] curves=new Curve[n];
		Point s=new Point(2*0+1,2*0+1),t=new Point(2*100000+1,2*0+1);
		for(int i=0;i<n;++i) {
			curves[i]=new Curve();
			curves[i].h=in.nextInt();
			curves[i].p=new Point[in.nextInt()];
			for(int j=0;j<curves[i].p.length;++j) curves[i].p[j]=new Point(2*in.nextInt(),2*in.nextInt());
		}
		
		List<Intersection> intersections=new ArrayList<Intersection>();
		for(int i=0;i<n;++i) for(int j=0;j<curves[i].p.length;++j) {
			Point a=s,b=t,c=curves[i].p[j],d=curves[i].p[(j+1)%curves[i].p.length];
			long den=d.min(c).cross(b.min(a));
			if(den==0) {
				boolean res=a.onseg(c,d)||b.onseg(c,d)||c.onseg(a,b)||d.onseg(a,b);
				if(res) throw new RuntimeException("point in common on parallel lines");
			} else {
				long num1=d.min(c).cross(c.min(a));
				long num2=a.min(c).cross(b.min(a));
				if(den<0) { den=-den; num1=-num1; num2=-num2; }
				if(0==num1||num1==den||0==num2||num2==den) throw new RuntimeException("segments touch");
				if(0<=num1&&num1<=den&&0<=num2&&num2<=den) {
					intersections.add(new Intersection(num1,den,i));
				}
			}
		}
		Collections.sort(intersections);
		
		int[] last=new int[n],cnt=new int[n];
		for(int i=0;i<n;++i) last[i]=-1;
		for(int i=0;i<intersections.size();++i) {
			int cur=intersections.get(i).curve;
			last[cur]=i;
			cnt[cur]++;
		}
		
		int up=0,down=0,at=0,now=-1;
		while(at<intersections.size()) {
			int cur=intersections.get(at).curve;
			if(cnt[cur]%2==0) {
				at=last[cur]+1;
			} else {
				int next=curves[cur].h;
				if(now!=-1) { if(now<next) up+=next-now; else down+=now-next; }
				now=next;
				at=last[cur]+1;
			}
		}

			System.out.println(up+" "+down);
	}
	
	public static void main(String[] args) {
		int n=in.nextInt(); for(int i=0;i<n;++i) new j1().run();
	}
}
