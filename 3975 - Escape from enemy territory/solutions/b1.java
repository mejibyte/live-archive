import java.util.*;

public class b1 {
	public static Scanner in=new Scanner(System.in).useLocale(Locale.US);
	
	boolean augment(int[][] cap,boolean[] done,int from,int to,int add) {
		if(done[from]) return false; else done[from]=true;
		if(from==to) return true;
		for(int i=0;i<cap[from].length;++i) if(cap[from][i]>=add&&augment(cap,done,i,to,add)) {
			cap[from][i]-=add;
			cap[i][from]+=add;
			return true;
		}
		return false;
	}
	
	int maxflow(int[][] cap,int from,int to) {
		int ret=0;
		int n=cap.length;
		for(int add=8;add>=1;add/=2) {
			boolean[] done=new boolean[n];
			while(augment(cap,done,from,to,add)) {
				ret+=add;
				done=new boolean[n];
			}
		}
		return ret;
	}
	
	public void run() {
		int n=in.nextInt(); double maxdist=in.nextDouble();
		int[] x=new int[n],y=new int[n],nrstart=new int[n],nrjump=new int[n];
		for(int i=0;i<n;++i) { x[i]=in.nextInt(); y[i]=in.nextInt(); nrstart[i]=in.nextInt(); nrjump[i]=in.nextInt(); }
		
		int[][] cap=new int[2*n+1][2*n+1];
		for(int i=0;i<n;++i) for(int j=0;j<n;++j) if((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])<=maxdist*maxdist) cap[2*i+1][2*j]=nrjump[i];
		for(int i=0;i<n;++i) cap[2*i][2*i+1]=nrjump[i];
		for(int i=0;i<n;++i) cap[2*n][2*i]=nrstart[i];
		int tot=0; for(int i=0;i<n;++i) tot+=nrstart[i];
		
		List<Integer> ret=new ArrayList<Integer>();
		for(int i=0;i<n;++i) {
			int[][] copycap=new int[2*n+1][2*n+1];
			for(int j=0;j<2*n+1;++j) for(int k=0;k<2*n+1;++k) copycap[j][k]=cap[j][k];
			if(maxflow(copycap,2*n,2*i)==tot) ret.add(i);
		}
		if(ret.size()==0) {
			System.out.println("-1");
		} else {
			for(int i=0;i<ret.size();++i) {
				if(i!=0) System.out.print(" ");
				System.out.print(ret.get(i));
			}
			System.out.println();
		}
	}
	
	public static void main(String[] args) {
		int n=in.nextInt(); for(int i=0;i<n;++i) new b1().run();
	}
}
