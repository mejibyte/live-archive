import java.util.*;

public class h1 {
	public static Scanner in=new Scanner(System.in).useLocale(Locale.US);


	public void run() {
		boolean[] singles=new boolean[26];
		Map<String,String>[][] words=new Map[26][26];
		for(int i=0;i<26;++i) for(int j=0;j<26;++j) words[i][j]=new HashMap<String,String>();
		Set<String>[][] doublewords=new Set[26][26];
		for(int i=0;i<26;++i) for(int j=0;j<26;++j) doublewords[i][j]=new HashSet<String>();
		String s=in.next();
		int n=in.nextInt();
		for(int i=0;i<n;++i) {
			String word=in.next();
			if(word.length()==1) {
				singles[word.charAt(0)-'a']=true;
			} else {
				int a=word.charAt(0)-'a',b=word.charAt(word.length()-1)-'a';
				char[] letters=word.substring(1,1+word.length()-2).toCharArray();
				Arrays.sort(letters);
				if(words[a][b].containsKey(new String(letters))) doublewords[a][b].add(new String(letters)); else words[a][b].put(new String(letters),word);
			}
		}
		String[] prev=new String[s.length()+1];
		int[] ways=new int[s.length()+1]; ways[0]=1;
		for(int i=0;i<s.length();++i) if(ways[i]>0) {
			if(singles[s.charAt(i)-'a']) { ways[i+1]=Math.min(2,ways[i+1]+ways[i]); prev[i+1]=""+s.charAt(i); }
			for(int len=2;i+len<=s.length() && len<=100;++len) {
				int a=s.charAt(i)-'a',b=s.charAt(i+len-1)-'a';
				char[] letters=s.substring(i+1,i+1+len-2).toCharArray();
				Arrays.sort(letters);
				String word=new String(letters);
				if(doublewords[a][b].contains(word)) ways[i+len]=Math.min(2,ways[i+len]+2*ways[i]);
				else if(words[a][b].containsKey(word)) { ways[i+len]=Math.min(2,ways[i+len]+ways[i]); prev[i+len]=words[a][b].get(word); }
			}
		}
		if(ways[s.length()]==0) System.out.println("impossible");
		else if(ways[s.length()]==2) System.out.println("ambiguous");
		else {
			List<String> ret=new ArrayList<String>();
			for(int i=s.length();i!=0;i-=prev[i].length()) ret.add(prev[i]);
			Collections.reverse(ret);
			for(int i=0;i<ret.size();++i) {
				if(i!=0) System.out.print(" ");
				System.out.print(ret.get(i));
			}
			System.out.println();
		}
		
	}
	
	public static void main(String[] args) {
		int n=in.nextInt(); for(int i=0;i<n;++i) new h1().run();
	}
}
