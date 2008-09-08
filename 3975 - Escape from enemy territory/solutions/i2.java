import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Scanner;

/**
 * TowerParking solution NWERC 2007
 * 
 * @author Mathijs Vogelzang
 * 
 */
public class i2 {

	public static void main(String[] args) {
		int runs;
		Scanner in = new Scanner(System.in);
		runs = in.nextInt();
		for (int r = 0; r < runs; r++) {
			int height = in.nextInt(), width = in.nextInt();
			int carpos[] = new int[height * width];
			int maxCar = 0;
			for (int i = 0; i < height; i++)
				for (int j = 0; j < width; j++) {
					int car = in.nextInt();
					if (car != -1) {
						carpos[car - 1] = i * 10000 + j;
						maxCar = Math.max(maxCar, car);
					}
				}

			int bandPos[] = new int[height];
			int T = 0;
			for (int i = 0; i < maxCar; i++) {
				int y = carpos[i] / 10000, x = carpos[i] % 10000;
				T += y * 2 * 10;
				T += Math.min((x - bandPos[y] + width) % width,
						(bandPos[y] - x + width) % width) * 5;
				bandPos[y] = x;
			}
			System.out.println("" + T);
		}
		in.close();
	}
}
