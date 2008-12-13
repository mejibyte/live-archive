import java.util.Scanner;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Collections;

public class erikjan {
	public static Scanner scanner;
	public static final int[] DX={-1,+1,0,0,0,0},DY={0,0,-1,+1,0,0},DZ={0,0,0,0,-1,+1};
	
	public static void uniquify(ArrayList<Integer> lst) {
		Collections.sort(lst);
		int at=0;
		for(int i=0;i<lst.size();++i) if(at==0||!lst.get(i).equals(lst.get(at-1))) lst.set(at++,lst.get(i));
		while(lst.size()>at) lst.remove(lst.size()-1);
	}

	public static void run() {
		int n=scanner.nextInt();
		Box[] boxes = new Box[n];
		for(int i=0;i<n;++i) boxes[i]=new Box(scanner);
		ArrayList<Integer> allx = new ArrayList<Integer>();
		ArrayList<Integer> ally = new ArrayList<Integer>();
		ArrayList<Integer> allz = new ArrayList<Integer>();
		for(int i=0;i<n;++i) {
			allx.add(boxes[i].x1); allx.add(boxes[i].x2);
			ally.add(boxes[i].y1); ally.add(boxes[i].y2);
			allz.add(boxes[i].z1); allz.add(boxes[i].z2);
		}
		uniquify(allx); int nx=allx.size()-1;
		uniquify(ally); int ny=ally.size()-1;
		uniquify(allz); int nz=allz.size()-1;
		boolean[][][] occupied = new boolean[nx][ny][nz];
		for(int i=0;i<n;++i) {
			int x1=allx.indexOf(boxes[i].x1),x2=allx.indexOf(boxes[i].x2);
			int y1=ally.indexOf(boxes[i].y1),y2=ally.indexOf(boxes[i].y2);
			int z1=allz.indexOf(boxes[i].z1),z2=allz.indexOf(boxes[i].z2);
			for(int x=x1;x<x2;++x) for(int y=y1;y<y2;++y) for(int z=z1;z<z2;++z) occupied[x][y][z]=true;
		}

		boolean[][][] outside = new boolean[nx][ny][nz];
		LinkedList<Integer> qx = new LinkedList<Integer>();
		LinkedList<Integer> qy = new LinkedList<Integer>();
		LinkedList<Integer> qz = new LinkedList<Integer>();
		for(int y=0;y<ny;++y) for(int z=0;z<nz;++z) {
			if(!occupied[0][y][z]&&!outside[0][y][z]) { outside[0][y][z]=true; qx.add(0); qy.add(y); qz.add(z); }
			if(!occupied[nx-1][y][z]&&!outside[nx-1][y][z]) { outside[nx-1][y][z]=true; qx.add(nx-1); qy.add(y); qz.add(z); }
		}
		for(int x=0;x<nx;++x) for(int z=0;z<nz;++z) {
			if(!occupied[x][0][z]&&!outside[x][0][z]) { outside[x][0][z]=true; qx.add(x); qy.add(0); qz.add(z); }
			if(!occupied[x][ny-1][z]&&!outside[x][ny-1][z]) { outside[x][ny-1][z]=true; qx.add(x); qy.add(ny-1); qz.add(z); }
		}
		for(int x=0;x<nx;++x) for(int y=0;y<ny;++y) {
			if(!occupied[x][y][0]&&!outside[x][y][0]) { outside[x][y][0]=true; qx.add(x); qy.add(y); qz.add(0); }
			if(!occupied[x][y][nz-1]&&!outside[x][y][nz-1]) { outside[x][y][nz-1]=true; qx.add(x); qy.add(y); qz.add(nz-1); }
		}
		while(!qx.isEmpty()&&!qy.isEmpty()&&!qz.isEmpty()) {
			int x=qx.poll(),y=qy.poll(),z=qz.poll();
			for(int k=0;k<6;++k) {
				int cx=x+DX[k],cy=y+DY[k],cz=z+DZ[k];
				if(cx<0||cx>=nx||cy<0||cy>=ny||cz<0||cz>=nz||occupied[cx][cy][cz]||outside[cx][cy][cz]) continue;
				outside[cx][cy][cz]=true; qx.add(cx); qy.add(cy); qz.add(cz);
			}
		}
		
		long area=0;
		long volume=0;
		for(int x=0;x<nx;++x) for(int y=0;y<ny;++y) for(int z=0;z<nz;++z) {
			long dx=allx.get(x+1)-allx.get(x);
			long dy=ally.get(y+1)-ally.get(y);
			long dz=allz.get(z+1)-allz.get(z);
			if(!outside[x][y][z]) volume+=dx*dy*dz;
			if(occupied[x][y][z]) for(int k=0;k<6;++k) {
				int cx=x+DX[k],cy=y+DY[k],cz=z+DZ[k];
				if(0<=cx&&cx<nx&&0<=cy&&cy<ny&&0<=cz&&cz<nz&&!outside[cx][cy][cz]) continue;
				if(DX[k]!=0) area+=dy*dz;
				if(DY[k]!=0) area+=dx*dz;
				if(DZ[k]!=0) area+=dx*dy;
			}
		}
		
		System.out.println(area+" "+volume);
	}
	
	public static void main(String[] args) {
		scanner = new Scanner(System.in);
		int n=scanner.nextInt();
		for(int i=0;i<n;++i) run();
	}
}

class Box {
	public int x1,y1,z1;
	public int x2,y2,z2;
	
	public Box(Scanner scanner) {
		x1=scanner.nextInt();
		y1=scanner.nextInt();
		z1=scanner.nextInt();
		int dx=scanner.nextInt(); x2=x1+dx;
		int dy=scanner.nextInt(); y2=y1+dy;
		int dz=scanner.nextInt(); z2=z1+dz;
	}
}