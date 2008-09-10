/*
  Robado de: http://www.informatik.uni-leipzig.de/~paxton/algorithmics/week11/HourGlass/
*/
import java.util.Hashtable;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Vector;

class Hourglass {
    static int hg1abs;
    static int hg2abs;
    static int targetTime;
    static boolean solved;
    static Vector<TimePoint> cue = new Vector<TimePoint>();
    static Hashtable hash = new Hashtable();
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out);

        while (in.hasNext()) {
            hg1abs = in.nextInt();
            hg2abs = in.nextInt();
            targetTime = in.nextInt();
            if ( ((hg1abs | hg2abs) | targetTime) == 0) break;
            solved = false;
            cue.clear();
            hash.clear();
            cue.add(new TimePoint(hg1abs, hg2abs, 0, new String("0: " + hg1abs + "," + hg2abs + "\n")));
            out.print(solve());
        }
        out.close();
    }

    private static String solve()
    {
        int cTime;
        while(cue.size() > 0)
            {
                TimePoint current = cue.get(0);
                cue.remove(0);
                if (current.time == targetTime)
                    {
                        return current.solution + "----------\n";
                    }
                if (current.time < targetTime )
                    {
                        // hourglass 1 running out before houglass 2
                        if ((current.hg1 < current.hg2) && (current.hg1 != 0))
                            {
                                cTime = current.time + current.hg1;
                                solvAux(0, current.hg2 - current.hg1, cTime, current.solution, 0); // no action
                                solvAux(hg1abs, current.hg2 - current.hg1, cTime, current.solution, 1); // flip 1
                                solvAux(0, hg2abs - (current.hg2 - current.hg1), cTime, current.solution, 2); // flip 2
                                solvAux(hg1abs, hg2abs - (current.hg2 - current.hg1), cTime, current.solution, 3); // flip both
                            }
                        // hourglass 2 running out before houglass 1
                        if ((current.hg1 > current.hg2) && (current.hg2 != 0))
                            {
                                cTime = current.time + current.hg2;
                                solvAux(current.hg1 - current.hg2, 0, cTime, current.solution, 0); // no action
                                solvAux(hg1abs - (current.hg1 - current.hg2), 0, current.time + current.hg2,
                                        current.solution, 1); // flip 1
                                solvAux(current.hg1 - current.hg2, hg2abs , cTime,
                                        current.solution, 2); // flip 2
                                solvAux(hg1abs - (current.hg1 - current.hg2), hg2abs, cTime,
                                        current.solution, 3); // flip both
                            }
                        // both running out at same time
                        if  ((current.hg1 == current.hg2))
                            {
                                cTime = current.time + current.hg2;
                                solvAux(hg1abs - (current.hg1 - current.hg2), 0, cTime,
                                        current.solution, 1); // flip 1
                                solvAux(0, hg2abs - (current.hg2 - current.hg1), cTime,
                                        current.solution, 2); // flip 2
                                solvAux(hg1abs - (current.hg1 - current.hg2), hg2abs - (current.hg2 - current.hg1), cTime,
                                        current.solution, 3); // flip both
                            }
                        // one hourglas running out, the other idle
                        if (current.hg1 == 0 || current.hg2 == 0)
                            {
                                cTime = current.time + current.hg1 + current.hg2;
                                solvAux(hg1abs, 0, cTime,
                                        current.solution, 1); // flip 1
                                solvAux(0, hg2abs , cTime,
                                        current.solution, 2); // flip 2
                                solvAux(hg1abs, hg2abs, cTime,
                                        current.solution, 3); // flip both
                            }
                    }

            }

        return "Impossible!\n----------\n";
    }

    private static void solvAux(int hg1, int hg2, int cTime, String cSolution, int flag)
    {
        if (cTime == targetTime)
            {
                cue.clear();
                cue.add(new TimePoint(0, 0, cTime, cSolution));
                return;
            }
        String hashKey = new String(cTime + "" + hg1 + "" + hg2);
        if (hash.containsKey(hashKey)) return;
        hash.put(hashKey, 0);
        String sg1 = "";
        String sg2 = "";
        String commaString = "";
        if (flag == 1 || flag == 3) sg1 = hg1abs + "";
        if (flag == 2 || flag == 3) sg2 = hg2abs + "";
        if (flag == 3) commaString = ",";
        String newPart = new String (cTime + ": " + sg1 + commaString + sg2 + "\n");
        if (flag == 0) newPart = "";
        cue.add(new TimePoint(hg1, hg2, cTime, cSolution + newPart));
    }

}
class TimePoint
{
    int time;
    int hg1;
    int hg2;
    String solution;
    TimePoint (int hg1, int hg2, int time, String solution)
    {
        this.hg1 = hg1;
        this.hg2 = hg2;
        this.time = time;
        this.solution = solution;
    }
}
