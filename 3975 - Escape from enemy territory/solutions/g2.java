import java.util.*;

class Pos implements Comparable {
  int x, y, h;
  Pos(int _x, int _y, int _h) {
    x=_x;
    y=_y;
    h=_h;
  }

public int compareTo(Object o) {
    return h-((Pos)o).h;
  }
};

public class g2 {

  static Scanner in = new Scanner(System.in);

  void go() {
    int R=in.nextInt(), C=in.nextInt(), d=in.nextInt();

    int[][] map=new int[R][C];
    int[][] been=new int[R][C];
    Pos[] heights=new Pos[R*C];
    for(int i=0; i<R; i++) for(int j=0; j<C; j++) {
      map[i][j]=in.nextInt();
      been[i][j]=-1;
      heights[i*C+j]=new Pos(i,j,map[i][j]);
    }
    Arrays.sort(heights);

    int nsummits=0;
//    Queue<Pos> q=new ArrayBlockingQueue<Pos>(4*R*C+1000);
    Queue<Pos> q=new LinkedList<Pos>();
    for(int i=R*C-1; i>=0; i--) {
      Pos s=heights[i];
      if(been[s.x][s.y]!=-1) continue;
      //nsummits++;

      int nsums=0;
      boolean summit=true;

      q.clear();
      q.offer(new Pos(s.x,s.y,s.h));
      while(q.size()>0) {
        Pos p=q.remove();
        if(been[p.x][p.y]!=-1) continue;
        if(map[p.x][p.y]==s.h) nsums++;
        been[p.x][p.y]=i;
        int[] dx={1,0,-1,0}, dy={0,1,0,-1};
        for(int k=0; k<4; k++) {
          int x=p.x+dx[k], y=p.y+dy[k];
          if(x>=0 && x<R && y>=0 && y<C && map[x][y]>s.h-d) {
            if(been[x][y]>i) summit=false;
            if(been[x][y]==-1) q.offer(new Pos(x,y, map[x][y]));
          }
        }
      }
      if(summit) nsummits+=nsums;
    }
    System.out.println(nsummits);
  }

  public static void main(String[] args) throws Exception {
    int nruns = in.nextInt();
    while (nruns-- > 0) {
      new g2().go();
    }
  }

}
