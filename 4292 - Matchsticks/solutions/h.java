import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class erikjan {
	public static Scanner scanner;
	
	public static final int[] need = {6,2,5,5,4,5,6,3,7,6};
	
	public static int compare(String a,String b) {
		if(a.length()!=b.length()) return a.length()<b.length()?-1:+1;
		for(int i=0;i<a.length();++i) if(a.charAt(i)!=b.charAt(i)) return a.charAt(i)<b.charAt(i)?-1:+1;
		return 0;
	}

	public static void run() {
		int n=scanner.nextInt();
		String[] l=new String[n+1];
		String[] h=new String[n+1];
		for(int j=1;j<10;++j) if(need[j]<=n) {
			if(l[need[j]]==null||compare(""+j,l[need[j]])<0) l[need[j]]=""+j;
			if(h[need[j]]==null||compare(""+j,h[need[j]])>0) h[need[j]]=""+j;
		}
		for(int i=0;i<=n;++i) for(int j=0;j<10;++j) if(i+need[j]<=n) {
			if(l[i]!=null&&(l[i+need[j]]==null||compare(l[i]+j,l[i+need[j]])<0)) l[i+need[j]]=l[i]+j;
			if(h[i]!=null&&(h[i+need[j]]==null||compare(h[i]+j,h[i+need[j]])>0)) h[i+need[j]]=h[i]+j;
		}
		System.out.println(l[n]+" "+h[n]);				
	}
	
	public static void main(String[] args) {
		scanner = new Scanner(System.in);
		int n=scanner.nextInt();
		for(int i=0;i<n;++i) run();
	}
}