import java.util.Arrays;
import java.util.LinkedList;
import java.util.Scanner;

/**
 * Escape, NWERC 2007
 * Runtime: 6.9s on AMD 3500+ with java 1.6
 *
 * @author Mathijs Vogelzang
 */
public class e3 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int runs = in.nextInt();
        for (int r = 0; r < runs; r++) {
            int bases = in.nextInt(), X = in.nextInt(), Y = in.nextInt();
            int startx = in.nextInt(), starty = in.nextInt(), endx = in
                .nextInt(), endy = in.nextInt();
            int[] basex = new int[bases], basey = new int[bases];
            for (int i = 0; i < bases; i++) {
                basex[i] = in.nextInt();
                basey[i] = in.nextInt();
            }

            // determine distance of every cell to an enemy base
            LinkedList<Integer> q = new LinkedList<Integer>();
            int[][] dist = new int[X][Y];
            int maxDist = X + Y + 10;
            for (int x = 0; x < X; x++)
                Arrays.fill(dist[x], maxDist);
            for (int i = 0; i < bases; i++) {
                q.add(basex[i] * 10000 + basey[i]);
                dist[basex[i]][basey[i]] = 0;
            }
            int dx[] = new int[] { 0, 0, 1, -1 }, dy[] = new int[] { -1, 1, 0,
                                                                     0 };
            while (q.size() != 0) {
                int x = q.peek() / 10000, y = q.poll() % 10000;
                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i], ny = y + dy[i];
                    if (nx >= 0 && nx < X && ny >= 0 && ny < Y
                        && dist[nx][ny] == maxDist) {
                        dist[nx][ny] = dist[x][y] + 1;
                        q.add(nx * 10000 + ny);
                    }
                }
            }

            // determine the minimum distance for a path to the end
            q.add(startx * 10000 + starty);
            int[][] distPath = new int[X][Y];
            for (int x = 0; x < X; x++)
                Arrays.fill(distPath[x], -1);
            distPath[startx][starty] = dist[startx][starty];
            while (q.size() != 0) {
                int x = q.peek() / 10000, y = q.poll() % 10000;
                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i], ny = y + dy[i];
                    if (nx >= 0 && nx < X && ny >= 0 && ny < Y
                        && distPath[nx][ny] < Math.min(distPath[x][y],dist[nx][ny])) {
                        if(dist[nx][ny] >= distPath[x][y])
                            q.addFirst(nx * 10000 + ny);
                        else
                            q.add(nx*10000 + ny);
                        distPath[nx][ny] = Math.min(distPath[x][y], dist[nx][ny]);
                    }
                }
            }

            int minDist = distPath[endx][endy];

            // determine shortest path
            q.add(startx * 10000 + starty);
            for (int x = 0; x < X; x++)
                Arrays.fill(distPath[x], 10000000);
            distPath[startx][starty] =0;
            while (q.size() != 0) {
                int x = q.peek() / 10000, y = q.poll() % 10000;
                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i], ny = y + dy[i];
                    if (nx >= 0 && nx < X && ny >= 0 && ny < Y
                        && dist[nx][ny] >= minDist && distPath[nx][ny] > distPath[x][y]+1) {
                        q.add(nx*10000 + ny);
                        distPath[nx][ny] = distPath[x][y]+1;
                    }
                }
            }

            System.out.println(minDist + " " + distPath[endx][endy]);
        }
    }
}
