import java.util.*;

public class g1 {
	public static Scanner in=new Scanner(System.in).useLocale(Locale.US);

	public class Event implements Comparable<Event> {
		public int x,y,val;
		public Event(int val,int x,int y) { this.val=val; this.x=x; this.y=y; }
		public int compareTo(Event e) {
			if(val>e.val) return -1;
			if(val<e.val) return +1;
			return 0;
		}
	}

	public void run() {
		int h=in.nextInt(),w=in.nextInt(),d=in.nextInt();
		int[][] g=new int[h][w]; for(int i=0;i<h;++i) for(int j=0;j<w;++j) g[i][j]=in.nextInt();
		
		int[][] maxtop=new int[h][w]; for(int i=0;i<h;++i) for(int j=0;j<w;++j) maxtop[i][j]=-1;
		List<Event> events=new ArrayList<Event>();
		for(int i=0;i<h;++i) for(int j=0;j<w;++j) events.add(new Event(g[i][j],i,j));
		Collections.sort(events);
		
		int ret=0;
		for(int i=0;i<events.size();++i) {
			int sx=events.get(i).x,sy=events.get(i).y;
			if(maxtop[sx][sy]!=-1) continue;
			boolean ok=true; int cnt=0;
			Queue<Integer> qx=new LinkedList<Integer>(),qy=new LinkedList<Integer>();
			qx.offer(sx); qy.offer(sy); maxtop[sx][sy]=g[sx][sy];
			while(!qx.isEmpty()||!qy.isEmpty()) {
				int x=qx.poll(),y=qy.poll();
				if(g[x][y]==g[sx][sy]) ++cnt;
				for(int dx=-1;dx<=+1;++dx) for(int dy=-1;dy<=+1;++dy) if((dx!=0)^(dy!=0)) {
					int nx=x+dx,ny=y+dy;
					if(nx<0||nx>=h||ny<0||ny>=w) continue;
					if(maxtop[nx][ny]>g[sx][sy]) ok=false;
					if(maxtop[nx][ny]!=-1) continue;
					if(g[nx][ny]<=g[sx][sy]-d) continue;
					qx.offer(nx); qy.offer(ny); maxtop[nx][ny]=g[sx][sy];
				}
			}
			if(ok) ret+=cnt;
		}
		System.out.println(ret);
	}
	
	public static void main(String[] args) {
		int n=in.nextInt(); for(int i=0;i<n;++i) new g1().run();
	}
}
