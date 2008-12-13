import java.util.Scanner;
import java.util.ArrayList;
import java.util.Stack;

public class erikjan {
	static Scanner scanner;
	
	static int visitnr;
	static ArrayList<ArrayList<Integer>> e;
	static int[] visit;
	static int[] lowlink;
	static Stack<Integer> stack;
	static int ncomp;
	static int[] comp;
	
	public static void tarjan(int at) {
		visit[at]=lowlink[at]=visitnr++;
		stack.add(at);
		ArrayList<Integer> cure=e.get(at);
		for(int i=0;i<cure.size();++i) {
			int to=cure.get(i);
			if(visit[to]==-1) {
				tarjan(to);
				lowlink[at]=Math.min(lowlink[at],lowlink[to]);
			} else if(comp[to]==-1) {
				lowlink[at]=Math.min(lowlink[at],visit[to]);
			}
		}
		if(lowlink[at]==visit[at]) {
			while(true) {
				int now=stack.pop();
				comp[now]=ncomp;
				if(now==at) break;
			}
			++ncomp;
		}
	}

	public static void run() {
		int n=scanner.nextInt();
		int m=scanner.nextInt();
		e=new ArrayList<ArrayList<Integer>>();
		for(int i=0;i<n;++i) e.add(new ArrayList<Integer>());
		for(int i=0;i<m;++i) {
			int a=scanner.nextInt(); --a;
			int b=scanner.nextInt(); --b;
			e.get(a).add(b);
		}
		
		visitnr=0;
		visit=new int[n];
		lowlink=new int[n];
		stack=new Stack<Integer>();
		ncomp=0;
		comp=new int[n];
		for(int i=0;i<n;++i) visit[i]=comp[i]=-1;
		for(int i=0;i<n;++i) if(visit[i]==-1) tarjan(i);
		if(ncomp==1) {
			System.out.println(0);
			return;
		}
		
		int[] outdeg=new int[ncomp];
		int[] indeg=new int[ncomp];
		for(int at=0;at<n;++at) {
			ArrayList<Integer> cure=e.get(at);
			for(int i=0;i<cure.size();++i) {
				int to=cure.get(i);
				if(comp[at]==comp[to]) continue;
				outdeg[comp[at]]++;
				indeg[comp[to]]++;
			}
		}
		
		int nhead=0,ntail=0;
		for(int i=0;i<ncomp;++i) {
			if(outdeg[i]==0) ++ntail;
			if(indeg[i]==0) ++nhead;
		}
		System.out.println(Math.max(nhead,ntail));
	}
	
	public static void main(String[] args) {
		scanner = new Scanner(System.in);
		int n=scanner.nextInt();
		for(int i=0;i<n;++i) run();
	}
}