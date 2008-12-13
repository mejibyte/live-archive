import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class erikjan {
	public static Scanner scanner;
	
	public static int parse(String s,int pos,int depth,ArrayList<Long> roots) {
		if(pos>=s.length()) throw new RuntimeException("unexpected end");
		if(s.charAt(pos)=='[') {
			++pos;
			pos=parse(s,pos,depth+1,roots);
			if(pos>=s.length()||s.charAt(pos++)!=',') throw new RuntimeException("expected `,`");
			pos=parse(s,pos,depth+1,roots);
			if(pos>=s.length()||s.charAt(pos++)!=']') throw new RuntimeException("expected `,`");
		} else {
			long cur=0;
			while(pos<s.length()&&Character.isDigit(s.charAt(pos))) {
				cur=cur*10+Character.digit(s.charAt(pos++),10);
			}
			if(cur==0) throw new RuntimeException("weight cannot be 0");
			roots.add(cur<<depth);
		}
		return pos;
	}
	
	public static void run() {
		String s = scanner.next();
		ArrayList<Long> roots = new ArrayList<Long>();
		int pos=parse(s,0,0,roots);
		if(pos!=s.length()) throw new RuntimeException("extra characters found after parsing");
		Collections.sort(roots);
		int ret=0;
		for(int i=0;i<roots.size();) {
			int j=i+1;
			while(j<roots.size()&&roots.get(i).equals(roots.get(j))) ++j;
			if(j-i>ret) ret=j-i;
			i=j;
		}
		System.out.println(roots.size()-ret);
	}
	
	public static void main(String[] args) {
		scanner = new Scanner(System.in);
		int n=scanner.nextInt();
		for(int i=0;i<n;++i) run();
	}
}