import java.util.*;

public class e2 {

	static Scanner in = new Scanner(System.in);

	public static void main(String[] args) {
		int T = in.nextInt();
		for (int t=1; t<=T; ++t) {
			new e2();
		}
	}

	static final int INF = 999999;
	int N = in.nextInt();
	int X = in.nextInt();
	int Y = in.nextInt();

	short[][] baseDist = new short[X][Y];
	int[][] len = new int[X][Y];
	static short[] qx = new short[1000000];
	static short[] qy = new short[1000000];
	int b;
	int c;

	final void visit(short x, short y, short v) {
		if (v>=baseDist[x][y]) return;
		baseDist[x][y] = v;
		qx[b] = x;
		qy[b] = y;
		++b;
	}

	final void visit2(short x, short y, int l) {
		if (l>=len[x][y]) return;
		if (baseDist[x][y]<c) return;
		len[x][y] = l;
		qx[b] = x;
		qy[b] = y;
		++b;
	}

	oyvind2() {
		short xi = in.nextShort();
		short yi = in.nextShort();
		short xr = in.nextShort();
		short yr = in.nextShort();
		for (short[] s : baseDist) Arrays.fill(s, (short)9999);
		for (int i=0; i<N; ++i) {
			qx[i] = in.nextShort();
			qy[i] = in.nextShort();
			baseDist[qx[i]][qy[i]] = 0;
		}
		int a = 0;
		b = N;
		while (a<b) {
			short x = qx[a];
			short y = qy[a];
			short v = (short)(baseDist[x][y] + 1);
			if (x>0) visit((short)(x-1), y, v);
			if (x+1<X) visit((short)(x+1), y, v);
			if (y>0) visit(x, (short)(y-1), v);
			if (y+1<Y) visit(x, (short)(y+1), v);
			++a;
		}
		int min = 0;
		int max = Math.min(baseDist[xi][yi], baseDist[xr][yr]);

		int bestD = -1;
		int bestLen = 0;

		while (max>bestD) {
			c = (min+max+1)/2;
			for (int[] s : len) Arrays.fill(s, INF);
			len[xi][yi] = 0;
			a = 0;
			b = 1;
			qx[0] = xi;
			qy[0] = yi;
			int foundD = -1;
			int foundLen = INF;
			while (a<b) {
				short x = qx[a];
				short y = qy[a];
				int l = len[x][y];
				if (x==xr && y==yr) {
					foundLen = l;
					foundD = c;
					break;
				}
				l += 1;
				if (x>0) visit2((short)(x-1), y, l);
				if (x+1<X) visit2((short)(x+1), y, l);
				if (y>0) visit2(x, (short)(y-1), l);
				if (y+1<Y) visit2(x, (short)(y+1), l);
				++a;
			}
			if (foundD > bestD) {
				bestD = foundD;
				bestLen = foundLen;
				min = c+1;
			} else {
				max = c-1;
			}
		}
		System.out.println(bestD+" "+bestLen);
	}

}
