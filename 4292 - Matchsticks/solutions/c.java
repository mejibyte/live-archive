import java.util.Scanner;
import java.util.ArrayList;

public class erikjan {
	static Scanner scanner;
	
	static ArrayList<ArrayList<Integer>> e;
	static boolean[] done;
	static int[] match;
	
	static boolean augment(int at) {
		if(done[at]) return false; else done[at]=true;
		ArrayList<Integer> cure=e.get(at);
		for(int i=0;i<cure.size();++i) {
			int to=cure.get(i);
			if(match[to]==-1||augment(match[to])) {
				match[to]=at;
				return true;
			}
		}
		return false;
	}

	public static void run() {
		int ncats=scanner.nextInt();
		int ndogs=scanner.nextInt();
		int nvoters=scanner.nextInt();
		ArrayList<Person> catlovers=new ArrayList<Person>();
		ArrayList<Person> doglovers=new ArrayList<Person>();
		for(int i=0;i<nvoters;++i) {
			String lovestr=scanner.next();
			String hatestr=scanner.next();
			int loves=Integer.parseInt(lovestr.substring(1));
			int hates=Integer.parseInt(hatestr.substring(1));
			Person p=new Person(loves,hates);
			if(lovestr.charAt(0)=='C') catlovers.add(p); else doglovers.add(p);
		}
		
		e=new ArrayList<ArrayList<Integer>>();
		for(int i=0;i<catlovers.size();++i) e.add(new ArrayList<Integer>());
		for(int i=0;i<catlovers.size();++i)
			for(int j=0;j<doglovers.size();++j)
				if(catlovers.get(i).loves==doglovers.get(j).hates||catlovers.get(i).hates==doglovers.get(j).loves)
					e.get(i).add(j);
		match=new int[doglovers.size()];
		for(int j=0;j<doglovers.size();++j) match[j]=-1;
		
		int ret=catlovers.size()+doglovers.size();
		for(int i=0;i<catlovers.size();++i) {
			done=new boolean[catlovers.size()];
			if(augment(i)) --ret;
		}
		System.out.println(ret);
	}
	
	public static void main(String[] args) {
		scanner = new Scanner(System.in);
		int n=scanner.nextInt();
		for(int i=0;i<n;++i) run();
	}
}

class Person {
	public int loves;
	public int hates;
	
	public Person(int loves,int hates) {
		this.loves=loves;
		this.hates=hates;
	}
}