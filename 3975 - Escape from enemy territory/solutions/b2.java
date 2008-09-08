import java.util.*;

public class b2 {

  static Scanner in = new Scanner(System.in);

  double jdist2;
  double[] x,y;
  int[] npeng, mjumps;

  int adj[][], cap[][];
  boolean[] used;
  
  int dfs(int n, int t, int c) {
    used[n]=true;
    if(n==t) {
      return c;
    }

    for(int i=0; i<cap.length; i++) if(!used[i] && cap[n][i]>0) {
      int pathc=dfs(i, t, Math.min(cap[n][i], c));
      if(pathc>0) {
        cap[n][i]-=pathc;
        cap[i][n]+=pathc;
        return pathc;
      }
    }
    return 0;
  }

  int maxFlow(int s, int t, int[][] _cap) {
    int flow=0;
    int pathc=0;
    int N=_cap.length;
    cap=new int[N][N];
    for(int i=0; i<N; i++) for(int j=0; j<N; j++) cap[i][j]=_cap[i][j]; // kut java
    do {
      used=new boolean[cap.length];
      pathc=dfs(s, t, 1234567890);
      flow+=pathc;
    } while(pathc!=0);
    return flow;
  }

  boolean isEdge(int m, int n) {
    double dx=x[m]-x[n], dy=y[m]-y[n];
    return dx*dx+dy*dy<jdist2;
  }

  void go() {
    int N=in.nextInt(); double jdist=in.nextDouble();
    jdist2=jdist*jdist;
    x=new double[N]; y=new double[N];
    npeng=new int[N]; mjumps=new int[N];
    for(int i=0; i<N; i++) {
      x[i]=in.nextDouble(); y[i]=in.nextDouble();
      npeng[i]=in.nextInt(); mjumps[i]=in.nextInt();
    }

    int[][] cap=new int[2*N+1][2*N+1];

    int totpeng=0;
    for(int i=0; i<N; i++) {
      totpeng+=npeng[i];
    // edges from source to in vertex ice cube (cap is num penguins)
    //  adj[2*N].PB(i); adj[i].PB(2*N);
      cap[2*N][i]=npeng[i];
    // edges from in vertex to out vertex (cap is max jumps)
    //  adj[i].PB(i+N); adj[i+N].PB(i);
      cap[i][i+N]=mjumps[i];
      for(int j=0; j<N; j++) if(i!=j && isEdge(i,j)) {
      // edges from out vertex to in vertex if jumpable (cap is infinite)
      //  adj[i+N].PB(j); adj[j].PB(i+N);
        cap[i+N][j]=1234567890;
      }
    }

    boolean first=true;
    for(int i=0; i<N; i++) if(maxFlow(2*N, i, cap)==totpeng) {
      if(!first) System.out.print(" ");
      first=false;
      System.out.print(i);
    }
    if(first) System.out.println("-1");
    else System.out.print("\n");
  }

  public static void main(String[] args) throws Exception {
    int nruns = in.nextInt();
    while (nruns-- > 0) {
      new b2().go();
    }
  }

}
