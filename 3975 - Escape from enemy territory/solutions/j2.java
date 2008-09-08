import java.util.*;

public class j2 {

	class Cross implements Comparable<Cross> {
		int h;
		long m, n;
		Point a, b;

		public int compareTo(Cross b) {
			if (this == b) return 0;
			long d = m*b.n - n*b.m;
			if (d<0) return -1;
			if (d>0) return 1;
			return 0;
		}
		public String toString() {
			return String.format("%d (%.2f %s %s)", h, ((double)m)/n, a, b);
		}
	}

	class Point {
		long x, y;
		Point() {
			x = in.nextInt();
			y = in.nextInt();
		}
		public String toString() {
			return x+" "+y;
		}
	}
	
	void go() {
		List<Cross> crossings = new ArrayList<Cross>();
		int n = in.nextInt();
		while (n --> 0) {
			int h = in.nextInt();
			int ps = in.nextInt();
			Point[] p = new Point[ps+1];
			for (int i=0; i<ps; ++i) {
				p[i] = new Point();
			}
			p[ps] = p[0];
			int cnt = 0;
			Cross lastCross = null;
			for (int i=0; i<ps; ++i) {
				long x1 = p[i].x, y1 = p[i].y;
				long x2 = p[i+1].x, y2 = p[i+1].y;
				if (0 <= y1 ^ y2 < 0) continue;
				Cross cross = new Cross();
				cross.m = x1*(y1-y2) + (x2-x1)*y1;
				cross.n = y1 - y2;
				cross.a = p[i];
				cross.b = p[i+1];
				if (cross.n < 0) {
					cross.n *= -1;
					cross.m *= -1;
				}
				if (cross.m < 0) continue;
				if (cross.m > 100000*cross.n) continue;
				if (cross.m == 0 || cross.m==100000*cross.n) {
					throw new RuntimeException("start/end point on polygon is not allowed!");
				}
				++cnt;
				if (lastCross == null || lastCross.compareTo(cross) < 0) {
					lastCross = cross;
				}
			}
			if (cnt % 2 == 1) {
				lastCross.h = h;
				crossings.add(lastCross);
			}
		}
		Collections.sort(crossings);
		System.err.println(crossings);
		int up=0, down=0;
		Integer lastH = null;
		for (Cross c : crossings) {
			if (lastH == null) lastH = c.h;
			else {
				if (c.h > lastH) up += c.h - lastH;
				else down += lastH - c.h;
				lastH = c.h;
			}
		}
		System.out.println(up+" "+down);
	}

	/*** INPUT ETC ***/

	static Scanner in = new Scanner(System.in);
	public static void main(String[] args) throws Exception {
		int t = in.nextInt();
		while (t --> 0) {
			new j2().go();
		}
	}

}
