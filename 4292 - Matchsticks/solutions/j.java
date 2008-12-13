import java.util.Scanner;
import java.util.ArrayList;

public class erikjan {
	public static Scanner scanner;
	
	public static void run() {
		int n = scanner.nextInt();
		int len = scanner.nextInt();
		int[] order = new int[len];
		for(int i=0;i<len;++i) { order[i]=scanner.nextInt(); --order[i]; }
		
		int m=1+(len+n-1)/n;
		int[][] cnt=new int[m][n];
		for(int i=0;i<len;++i) cnt[1+i/n][order[i]]++;
		int errors=0;
		for(int i=0;i<m;++i) for(int j=0;j<n;++j) if(cnt[i][j]>1) ++errors;
		
		int ret=0;
		for(int offset=0;offset<n;++offset) {
//			System.out.println("offset="+offset+", errors="+errors);
//			for(int i=0;i<m;++i) for(int j=0;j<n;++j) System.out.print(cnt[i][j]+(j==n-1?(i==m-1?"\n":"|"):" "));
			if(errors==0) ++ret;
			for(int i=offset;i<len;i+=n) {
				cnt[1+i/n][order[i]]--;
				if(cnt[1+i/n][order[i]]==1) --errors;
				if(cnt[i/n][order[i]]==1) ++errors;
				cnt[i/n][order[i]]++;
			}
		}
		System.out.println(ret);
	}
	
	public static void main(String[] args) {
		scanner = new Scanner(System.in);
		int n=scanner.nextInt();
		for(int i=0;i<n;++i) run();
	}
}
