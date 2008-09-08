import java.util.*;

public class f1 {
	public static Scanner in=new Scanner(System.in).useLocale(Locale.US);
	public static final double eps=1e-12;
	public static final boolean debug=false;
	
	public class Point {
		public long x,y;
		public Point(long x,long y) { this.x=x; this.y=y; }
		
		Point min(Point p) { return new Point(this.x-p.x,this.y-p.y); }
		long cross(Point p) { return this.x*p.y-this.y*p.x; }
		long mult(Point p) { return this.x*p.x+this.y*p.y; }
		long dist2(Point p) { Point d=this.min(p); return d.x*d.x+d.y*d.y; }
		double len() { return Math.sqrt(this.x*this.x+this.y*this.y); }
		public String toString() { return "("+x+","+y+")"; }
				
		int side(Point a,Point b) {
			long ret=b.min(a).cross(this.min(a));
			if(ret<0) return -1; else if(ret>0) return +1; else return 0;
		}
		
		boolean onseg(Point a,Point b) {
			return this.side(a,b)==0&&this.dist2(a)<=a.dist2(b)&&this.dist2(b)<=a.dist2(b);
		}
	}
	
	public class Seg {
		public Point a,b;
		public List<Double> crosses;
		public Seg(Point a,Point b,List<Double> crosses) { this.a=a; this.b=b; this.crosses=crosses; }
		public String toString() { return a+"-"+b; }
	}
	
	public class Event implements Comparable<Event> {
		public double pos;
		public int type;
		public Event(double pos,int type) { this.pos=pos; this.type=type; }
		public int compareTo(Event e) {
			if(pos<e.pos) return -1; else if(pos>e.pos) return +1; else if(type>e.type) return -1; else if(type<e.type) return +1; else return 0;
		}
	}

	int sign(long a) { if(a<0) return -1; else if(a>0) return +1; else return 0; }
	
	double smindist(Point c,Point a,Point b) {
		return b.min(a).cross(c.min(a))/b.min(a).len();
	}

	double mindist(Point c,Point a,Point b) {
		return Math.abs(smindist(c,a,b));
	}
	
	boolean perpendicular(Point a,Point b,Point c,Point d) {
		return b.min(a).mult(d.min(c))==0;
	}
	
	double project(Point c,Point a,Point b) {
		return b.min(a).mult(c.min(a))/b.min(a).len()/b.min(a).len();
	}
	
	double transfer(Point c,Point d,Point a,Point b) {
		double num=c.min(a).mult(d.min(c));
		double den=b.min(a).mult(d.min(c));
		return num/den;
	}
	
	boolean can(double want,List<Seg> testsegs,Point[][] continents) {
		for(int i=0;i<testsegs.size();++i) {
			Seg seg=testsegs.get(i);
			Point a=seg.a,b=seg.b;
			if(debug) System.out.println(a+"-"+b+":");
			if(debug) for(int j=0;j<seg.crosses.size();j+=2) System.out.println("\t"+seg.crosses.get(j)+".."+seg.crosses.get(j+1)+" [need]");
			List<Event> events=new ArrayList<Event>();
			for(int j=0;j<seg.crosses.size();++j) events.add(new Event(seg.crosses.get(j),0));
			for(int j=0;j<continents.length;++j) for(int k=0;k<continents[j].length;++k) {
				Point c=continents[j][k];
				double d=mindist(c,a,b);
				if(d>want) continue;
				double center=project(c,a,b);
				double diff=Math.sqrt(want*want-d*d)/b.min(a).len();
				events.add(new Event(center-diff,+1));
				events.add(new Event(center+diff,-1));
				if(debug) System.out.println("\t"+(center-diff)+".."+(center+diff)+" [point "+j+","+k+"="+c+"]");
			}
			for(int j=0;j<continents.length;++j) for(int k=0;k<continents[j].length;++k) {
				Point c=continents[j][k],d=continents[j][(k+1)%continents[j].length];
				double fa=0,fb=1;
				double da=smindist(a,c,d),db=smindist(b,c,d);
				if(da>want&&db>want||da<-want&&db<-want) continue;
				if(da>want) fa=(want-da)/(db-da); if(da<-want) fa=(-want-da)/(db-da);
				if(db>want) fb=(want-da)/(db-da); if(db<-want) fb=(-want-da)/(db-da);
				if(fa>fb) throw new RuntimeException("fa>fb");
				double from=fa,to=fb;
				if(perpendicular(a,b,c,d)) {
					double pos=project(a,c,d);
					if(pos<0||pos>1) continue;
				} else {
					double fc=transfer(c,d,a,b),fd=transfer(d,c,a,b);
					from=Math.max(from,Math.min(fc,fd)); to=Math.min(to,Math.max(fc,fd));
				}
				if(from>to) continue;
				events.add(new Event(from,+1));
				events.add(new Event(to,-1));
				if(debug) System.out.println("\t"+from+".."+to+" [seg "+j+","+k+"="+c+"-"+d+"]");
			}
			Collections.sort(events);
			
			int cur=0; boolean need=false;
			for(int j=0;j<events.size();++j) {
				Event e=events.get(j);
				if(need&&cur<=0) return false;
				if(e.type==0) {
					need=!need;
				} else {
					cur+=e.type;
				}
				if(need&&cur<=0) return false;
			}
		}
		return true;
	}
	
	public void run() {
		int nrcontinents=in.nextInt(),nrwaypoints=in.nextInt();
		Point[] waypoints=new Point[nrwaypoints];
		for(int i=0;i<nrwaypoints;++i) waypoints[i]=new Point(in.nextInt(),in.nextInt());
		Point[][] continents=new Point[nrcontinents][];
		for(int i=0;i<nrcontinents;++i) {
			continents[i]=new Point[in.nextInt()];
			for(int j=0;j<continents[i].length;++j) continents[i][j]=new Point(in.nextInt(),in.nextInt());
		}
		
		boolean oncontinent=true;
		List<Seg> testsegs=new ArrayList<Seg>();
		for(int i=0;i+1<nrwaypoints;++i) {
			List<Double> crosses=new ArrayList<Double>();
			Point a=waypoints[i],b=waypoints[i+1];
			for(int j=0;j<nrcontinents;++j) for(int k=0;k<continents[j].length;++k) {
				Point c=continents[j][k],d=continents[j][(k+1)%continents[j].length];
				long checkden=4*d.min(c).cross(b.min(a));
				if(checkden!=0) {
					long checknum1=4*d.min(c).cross(c.min(a))-2*sign(d.min(c).x)+sign(d.min(c).y);
					long checknum2=4*a.min(c).cross(b.min(a))+2*sign(b.min(a).y)-sign(b.min(a).x);
					if(checkden<0) { checknum1=-checknum1; checknum2=-checknum2; checkden=-checkden; }
					if(checknum1==0||checknum1==checkden||checknum2==0||checknum2==checkden) throw new RuntimeException("point on seg");
					if(checknum1<0||checknum1>checkden||checknum2<0||checknum2>checkden) continue;
					long realden=d.min(c).cross(b.min(a));
					long realnum=d.min(c).cross(c.min(a));
					crosses.add(1.0*realnum/realden);
				}
			}
			boolean nextoncontinent=oncontinent^(crosses.size()%2==1);
			if(!oncontinent) crosses.add(0.0);
			if(!nextoncontinent) crosses.add(1.0);
			Collections.sort(crosses);
			if(crosses.size()%2!=0) throw new RuntimeException("number of crosses not divisible by 2");
			testsegs.add(new Seg(a,b,crosses));
			oncontinent=nextoncontinent;
		}
		if(!oncontinent) throw new RuntimeException("Not ending on continent");
		
		if(debug) {
			System.out.println(can(5,testsegs,continents));
		} else {
			double l=0,h=1; while(!can(h,testsegs,continents)) { l=h; h*=2; }
			for(int i=0;i<1000;++i) {
				if(h-l<1e-9) break;
				double m=l+(h-l)/2;
				if(!can(m,testsegs,continents)) l=m; else h=m;
			}
			System.out.println((l+h)/2);
		}
	}
	
	public static void main(String[] args) {
		int n=in.nextInt(); for(int i=0;i<n;++i) new f1().run();
	}
}
