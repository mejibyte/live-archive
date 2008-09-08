import java.util.*;

public class d1 {
	public static Scanner in=new Scanner(System.in).useLocale(Locale.US);

	public String[] transpose(String[] x) {
		String[] ret=new String[x[0].length()];
		for(int i=0;i<x[0].length();++i) { String cur=""; for(int j=0;j<x.length;++j) cur=cur+x[j].charAt(i); ret[i]=cur; }
		return ret;
	}

	public String[] go(int h,int w) {
		String[] ret={};
		switch(h) {
			case 1: switch(w) {
				case 1: { String[] x={"E"}; ret=x; break; }
				case 2: { String[] x={"BE"}; ret=x; break; }
				case 3: { String[] x={"BEB"}; ret=x; break; }
				case 4: { String[] x={"BE.B"}; ret=x; break; }
				case 5: { String[] x={"BE..B"}; ret=x; break; }
				case 6: { String[] x={"BE...B"}; ret=x; break; }
				case 7: { String[] x={"BE....B"}; ret=x; break; }
				case 8: { String[] x={"BE.....B"}; ret=x; break; }
			} break;
			case 2: switch(w) {
				case 1: return transpose(go(w,h));
				case 2: { String[] x={"E.","BB"}; ret=x; break; }
				case 3: { String[] x={"BEB","B.B"}; ret=x; break; }
				case 4: { String[] x={"E...","BBBB"}; ret=x; break; }
				case 5: { String[] x={"E....","BBBBB"}; ret=x; break; }
				case 6: { String[] x={"E.....","BBBBBB"}; ret=x; break; }
				case 7: { String[] x={"E......","BBBBBBB"}; ret=x; break; }
				case 8: { String[] x={"E.......","BBBBBBBB"}; ret=x; break; }
			} break;
			case 3: switch(w) {
				case 1: return transpose(go(w,h));
				case 2: return transpose(go(w,h));
				case 3: { String[] x={"BBB","E..","BBB"}; ret=x; break; }
				case 4: { String[] x={"BBBB","E...","BBBB"}; ret=x; break; }
				case 5: { String[] x={"BBBBB","E....","BBBBB"}; ret=x; break; }
				case 6: { String[] x={"BBBBBB","E.....","BBBBBB"}; ret=x; break; }
				case 7: { String[] x={"BBBBBBB","E......","BBBBBBB"}; ret=x; break; }
				case 8: { String[] x={"BBBBBBBB","E.......","BBBBBBBB"}; ret=x; break; }
			} break;
			case 4: switch(w) {
				case 1: return transpose(go(w,h));
				case 2: return transpose(go(w,h));
				case 3: return transpose(go(w,h));
				case 4: { String[] x={"BBBB",
														  "E...",
														  "B.B.",
														  "B.BB"}; ret=x; break; }
				case 5: { String[] x={"BBBBB",
														  "E....",
														  "B.BB.",
														  "B.BB."}; ret=x; break; }
				case 6: { String[] x={"BBBBBB",
														  "E.....",
														  "B.BB.B",
														  "B.BB.B"}; ret=x; break; }
				case 7: { String[] x={"BBBBBBB",
														  "E......",
														  "B.BB.B.",
														  "B.BB.BB"}; ret=x; break; }
				case 8: { String[] x={"BBBBBBBB",
														  "E.......",
														  "B.BB.BB.",
														  "B.BB.BB."}; ret=x; break; }
			} break;
			case 5: switch(w) {
				case 1: return transpose(go(w,h));
				case 2: return transpose(go(w,h));
				case 3: return transpose(go(w,h));
				case 4: return transpose(go(w,h));
				case 5: { String[] x={"BBBBB",
														  "E....",
														  "B.BB.",
														  "B.BB.",
														  "B.BB."}; ret=x; break; }
				case 6: { String[] x={"BBBBBB",
														  "E.....",
														  "B.BB.B",
														  "B.BB.B",
														  "B.BB.B"}; ret=x; break; }
				case 7: { String[] x={"BBBBBBB",
														  "E......",
														  "B.BB.B.",
														  "B.BB.B.",
														  "B.BB.BB"}; ret=x; break; }
				case 8: { String[] x={"BBBBBBBB",
														  "E.......",
														  "B.BB.BB.",
														  "B.BB.BB.",
														  "B.BB.BB."}; ret=x; break; }
			} break;
			case 6: switch(w) {
				case 1: return transpose(go(w,h));
				case 2: return transpose(go(w,h));
				case 3: return transpose(go(w,h));
				case 4: return transpose(go(w,h));
				case 5: return transpose(go(w,h));
				case 6: { String[] x={"BBBBBB",
														  "E.....",
														  "B.BBBB",
														  "B.BBBB",
														  "B.....",
														  "B.BBBB"}; ret=x; break; }
				case 7: { String[] x={"BBBBBBB",
														  "E......",
														  "B.BBBBB",
														  "B.BBBBB",
														  "B......",
														  "B.BBBBB"}; ret=x; break; }
				case 8: { String[] x={"BBBBBBBB",
														  "E.......",
														  "B.BBBBBB",
														  "B.BBBBBB",
														  "B.......",
														  "B.BBBBBB"}; ret=x; break; }
			} break;
			case 7: switch(w) {
				case 1: return transpose(go(w,h));
				case 2: return transpose(go(w,h));
				case 3: return transpose(go(w,h));
				case 4: return transpose(go(w,h));
				case 5: return transpose(go(w,h));
				case 6: return transpose(go(w,h));
				case 7: { String[] x={"BBBBBBB",
														  "E......",
														  "B.BBBBB",
														  "B.BBBBB",
														  "B......",
														  "B.BB.B.",
														  "B.BB.BB",}; ret=x; break; }
				case 8: { String[] x={"BBBBBBBB",
														  "E.......",
														  "B.BBBBBB",
														  "B.BBBBBB",
														  "B.......",
														  "B.BB.BB.",
														  "B.BB.BB."}; ret=x; break; }
			} break;
			case 8: switch(w) {
				case 1: return transpose(go(w,h));
				case 2: return transpose(go(w,h));
				case 3: return transpose(go(w,h));
				case 4: return transpose(go(w,h));
				case 5: return transpose(go(w,h));
				case 6: return transpose(go(w,h));
				case 7: return transpose(go(w,h));
				case 8: { String[] x={"BBBBBBBB",
														  "E.......",
														  "B.BBBBBB",
														  "B.BBBBBB",
														  "B.......",
														  "B.BB.BB.",
														  "B.BB.BB.",
														  "B.BB.BB."}; ret=x; break; }
			} break;
		}
		return ret;
	}
	
	public void run() {
		int h=in.nextInt(),w=in.nextInt();
		String ans[]=go(h,w);
		for(int i=0;i<ans.length;++i) System.out.println(ans[i]);
	}
	
	public static void main(String[] args) {
		int n=in.nextInt(); for(int i=0;i<n;++i) new d1().run();
	}
}
