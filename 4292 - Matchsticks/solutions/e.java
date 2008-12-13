import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class erikjan {
	static Scanner scanner;
	
	public static void run() {
		int n=scanner.nextInt();
		long dh=scanner.nextInt();
		int[] h=new int[n];
		for(int i=0;i<n;++i) h[i]=scanner.nextInt();
		
		ArrayList<Long> allhlst=new ArrayList<Long>();
		for(int i=0;i<n;++i) {
			int maxdist=Math.max(i,n-1-i);
			for(int j=-maxdist;j<=+maxdist;++j) allhlst.add(h[i]+j*dh);
		}

		{
			Collections.sort(allhlst);
			int at=0;
			for(int i=0;i<allhlst.size();++i) if(at==0||!allhlst.get(at-1).equals(allhlst.get(i))) allhlst.set(at++,allhlst.get(i));
			while(allhlst.size()>at) allhlst.remove(allhlst.size()-1);
		}
		long[] allh=new long[allhlst.size()];
		for(int i=0;i<allh.length;++i) allh[i]=allhlst.get(i);
		
		long[] best=new long[allh.length];
		for(int j=0;j<allh.length;++j) best[j]=Long.MAX_VALUE;
		int si=allhlst.indexOf((long)h[0]);
		best[si]=0;
		for(int i=1;i<n;++i) {
			long[] nbest=new long[allh.length];
			int at=0;
			for(int j=0;j<allh.length;++j) {
				while(allh[j]-allh[at]>dh) ++at;
				while(at+1<allh.length&&allh[at+1]-allh[j]<=dh&&best[at+1]<=best[at]) ++at;
				nbest[j]=best[at]==Long.MAX_VALUE?Long.MAX_VALUE:best[at]+Math.abs(h[i]-allh[j]);
			}
			best=nbest;
		}
		int ei=allhlst.indexOf((long)h[n-1]);
		System.out.println(best[ei]==Long.MAX_VALUE?"impossible":""+best[ei]);
	}
	
	public static void main(String[] args) {
		scanner = new Scanner(System.in);
		int n=scanner.nextInt();
		for(int i=0;i<n;++i) run();
	}
}
