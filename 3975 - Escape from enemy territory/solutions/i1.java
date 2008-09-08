import java.util.*;

public class i1 {
	public static Scanner in=new Scanner(System.in).useLocale(Locale.US);

	public class Car implements Comparable<Car> {
		int level,pos,name;
		public Car(int level,int pos,int name) { this.level=level; this.pos=pos; this.name=name; }
		public int compareTo(Car c) {
			if(name<c.name) return -1;
			if(name>c.name) return +1;
			return 0;
		}
	}
	
	public void run() {
		int towerheight=in.nextInt(),beltlen=in.nextInt();
		List<Car> cars=new ArrayList<Car>();
		for(int i=0;i<towerheight;++i) for(int j=0;j<beltlen;++j) {
			int cur=in.nextInt();
			if(cur!=-1) cars.add(new Car(i,j,cur));
		}
		Collections.sort(cars);
		int[] rot=new int[towerheight];
		int ret=0;
		for(int i=0;i<cars.size();++i) {
			Car car=cars.get(i);
			ret+=10*2*car.level;
			int diff=Math.abs(rot[car.level]-car.pos);
			ret+=5*Math.min(diff,beltlen-diff);
			rot[car.level]=car.pos;
		}
		System.out.println(ret);
	}
	
	public static void main(String[] args) {
		int n=in.nextInt(); for(int i=0;i<n;++i) new i1().run();
	}
}
