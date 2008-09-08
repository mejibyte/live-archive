import java.util.*;

public class e1 {
	public static Scanner in=new Scanner(System.in).useLocale(Locale.US);


	public void run() {
		int n=in.nextInt(),h=in.nextInt(),w=in.nextInt();
		int sx=in.nextInt(),sy=in.nextInt(),ex=in.nextInt(),ey=in.nextInt();
		
		int[][] cost=new int[h][w]; for(int i=0;i<h;++i) for(int j=0;j<w;++j) cost[i][j]=-1;
		Queue<Integer> qx=new LinkedList<Integer>(),qy=new LinkedList<Integer>();
		for(int i=0;i<n;++i) {
			int x=in.nextInt(),y=in.nextInt();
			if(cost[x][y]!=-1) continue;
			cost[x][y]=0; qx.offer(x); qy.offer(y);
		}
		while(!qx.isEmpty()||!qy.isEmpty()) {
			int x=qx.poll(),y=qy.poll();
			for(int dx=-1;dx<=+1;++dx) for(int dy=-1;dy<=+1;++dy) if((dx!=0)^(dy!=0)) {
				int nx=x+dx,ny=y+dy;
				if(nx<0||nx>=h||ny<0||ny>=w||cost[nx][ny]!=-1) continue;
				cost[nx][ny]=cost[x][y]+1; qx.offer(nx); qy.offer(ny);
			}
		}
//		System.out.println("cost:"); for(int i=0;i<h;++i) { for(int j=0;j<w;++j) System.out.print(cost[i][j]+" "); System.out.println(); }
		
		boolean[][] done=new boolean[h][w]; int bestcost=Math.min(cost[sx][sy],cost[ex][ey]);
		qx.offer(sx); qy.offer(sy); done[sx][sy]=true;
		while(!done[ex][ey]) {
			Queue<Integer> nqx=new LinkedList<Integer>(),nqy=new LinkedList<Integer>();
			while(!qx.isEmpty()||!qy.isEmpty()) {
				int x=qx.poll(),y=qy.poll();
				bestcost=Math.min(bestcost,cost[x][y]);
				for(int dx=-1;dx<=+1;++dx) for(int dy=-1;dy<=+1;++dy) if((dx!=0)^(dy!=0)) {
					int nx=x+dx,ny=y+dy;
					if(nx<0||nx>=h||ny<0||ny>=w||done[nx][ny]) continue;
					done[nx][ny]=true; 
					if(cost[nx][ny]>=bestcost) { qx.offer(nx); qy.offer(ny); } else { nqx.offer(nx); nqy.offer(ny); }
				}
			}
			qx=nqx; qy=nqy;
		}
		qx.clear(); qy.clear();
//		System.out.println("done:"+bestcost); for(int i=0;i<h;++i) { for(int j=0;j<w;++j) System.out.print((done[i][j]?1:0)+" "); System.out.println(); }
		
		int[][] dist=new int[h][w]; for(int i=0;i<h;++i) for(int j=0;j<w;++j) dist[i][j]=Integer.MAX_VALUE;
		qx.offer(sx); qy.offer(sy); dist[sx][sy]=0;
		while(!qx.isEmpty()||!qy.isEmpty()) {
			int x=qx.poll(),y=qy.poll();
			for(int dx=-1;dx<=+1;++dx) for(int dy=-1;dy<=+1;++dy) if((dx!=0)^(dy!=0)) {
				int nx=x+dx,ny=y+dy;
				if(nx<0||nx>=h||ny<0||ny>=w||cost[nx][ny]<bestcost||dist[x][y]+1>=dist[nx][ny]) continue;
				dist[nx][ny]=dist[x][y]+1;
				qx.offer(nx); qy.offer(ny);
			}
		}
//		System.out.println("dist:"); for(int i=0;i<h;++i) { for(int j=0;j<w;++j) System.out.print((dist[i][j]!=Integer.MAX_VALUE?dist[i][j]:-1)+" "); System.out.println(); }
		
		System.out.println(bestcost+" "+dist[ex][ey]);
	}
	
	public static void main(String[] args) {
		int n=in.nextInt(); for(int i=0;i<n;++i) new e1().run();
	}
}
