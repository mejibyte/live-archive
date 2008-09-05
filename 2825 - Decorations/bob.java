import java.util.*;
import java.io.*;

class DecB{
  public static BufferedReader in;
  public static int n, l, m, k;
  public static long[] oldgrid, newgrid;
  public static String[] combo;
  public static int[][] lookup;

  public static void main(String[] args) throws IOException {
    in = new BufferedReader(new InputStreamReader(System.in));
    String line;
    StringTokenizer st;

    while ((line = in.readLine()) != null) {
      st = new StringTokenizer(line);
      n = Integer.parseInt(st.nextToken());
      l = Integer.parseInt(st.nextToken());
      m = Integer.parseInt(st.nextToken());
      if (n == 0) break;
      combo = new String[m];
      st = new StringTokenizer(in.readLine());
      for (int i = 0; i < m; i++)
        combo[i] = st.nextToken();
      k = combo[0].length();
      lookup = new int[m][m+1];
      preprocess();
      System.out.println(answer());
    }
  }

  public static void preprocess() {
    for (int i = 0; i < m; i++) {
      int pos = 0;
      for (int j = 0; j < m; j++) {
         if (combo[i].substring(0,k-1).equals(combo[j].substring(1)))
            lookup[i][pos++] = j;
      }
      lookup[i][pos] = -1;
    }
  }

  public static long answer() {
    oldgrid = new long[m];
    if (l < k) return 0;
    for (int i = 0; i < m; i++)
       oldgrid[i] = 1;
    for (int len = k+1; len <= l; len++) {
       long newgrid[] = new long[m];
       for (int i = 0; i < m; i++) {
         newgrid[i] = 0;
         for (int j = 0; j < m && lookup[i][j] >= 0; j++)
            newgrid[i] += oldgrid[lookup[i][j]];
       }
       oldgrid = newgrid;
    }
    long sum = 0;
    for (int i = 0; i < m; i++)
       sum += oldgrid[i];
    return sum;
  }
}
