import java.util.Scanner;
import java.util.ArrayList;

public class erikjan {
	public static Scanner scanner;
	
	public static int NOTHING=0;
	public static int ONEPAIR=1;
	public static int TWOPAIR=2;
	public static int THREEKIND=3;
	public static int STRAIGHT=4;
	public static int FLUSH=5;
	public static int FULLHOUSE=6;
	public static int FOURKIND=7;
	public static int STRAIGHTFLUSH=8;
	public static int ROYALFLUSH=9;
	public static int[][] choose = {{1},{1,1},{1,2,1},{1,3,3,1},{1,4,6,4,1}};

	public static int evaluate(ArrayList<Card> cards) {
//		System.out.print("Evaluating");
//		for(int i=0;i<5;++i) System.out.print(" "+cards.get(i));
//		System.out.println();
		
		boolean allsamesuit=true;
		for(int i=1;i<cards.size();++i) if(cards.get(0).suit!=cards.get(i).suit) { allsamesuit=false; break; }
		
		int[] rankcnt=new int[13];
		for(int i=0;i<5;++i) rankcnt[cards.get(i).rank]++;
		int minrank=0; while(rankcnt[minrank]==0) ++minrank;
		int seqcnt=0; while(minrank+seqcnt<13&&rankcnt[minrank+seqcnt]==1) ++seqcnt;
		boolean straight=seqcnt==5||seqcnt==4&&minrank==0&&rankcnt[12]==1;
		
		if(allsamesuit&&straight&&minrank==8) return ROYALFLUSH;
		if(allsamesuit&&straight) return STRAIGHTFLUSH;
		
		int[] cntcnt=new int[5];
		for(int i=0;i<13;++i) cntcnt[rankcnt[i]]++;
		
		if(cntcnt[4]==1) return FOURKIND;
		if(cntcnt[3]==1&&cntcnt[2]==1) return FULLHOUSE;
		if(allsamesuit) return FLUSH;
		if(straight) return STRAIGHT;
		if(cntcnt[3]==1) return THREEKIND;
		if(cntcnt[2]==2) return TWOPAIR;
		if(cntcnt[2]==1) return ONEPAIR;
		return NOTHING;
	}
	
	public static int[] go(ArrayList<Card> cards,int atrank,long left) {
		if(cards.size()==5) {
			int[] ret=new int[10];
			ret[evaluate(cards)]=1;
			return ret;
		} else {
			int[] ret=new int[10];
			for(int rank=atrank;rank<13;++rank) {
				int have=0;
				for(int suit=0;suit<4;++suit) if((left&(1L<<new Card(rank,suit).code()))!=0) ++have;
				for(int cnt=1;cnt<=have&&cards.size()+cnt<=5;++cnt) {
					if(cnt>1) {
						for(int suit=0;suit<cnt;++suit) cards.add(new Card(rank,suit));
						int[] cur=go(cards,rank+1,left);
						for(int i=0;i<10;++i) ret[i]+=choose[have][cnt]*cur[i];
						for(int suit=0;suit<cnt;++suit) cards.remove(cards.size()-1);
					} else {
						int[] diffsuit=null;
						for(int suit=0;suit<4;++suit) {
							Card card=new Card(rank,suit);
							if((left&(1L<<card.code()))!=0) {
								cards.add(card);
								int[] cur;
								boolean allsamesuit=true;
								for(int i=1;i<cards.size();++i) if(cards.get(0).suit!=cards.get(i).suit) { allsamesuit=false; break; }
								if(allsamesuit) {
									cur=go(cards,rank+1,left);
								} else {
									if(diffsuit==null) diffsuit=go(cards,rank+1,left);
									cur=diffsuit;
								}
								for(int i=0;i<10;++i) ret[i]+=cur[i];
								cards.remove(cards.size()-1);
							}
						}
					}
				}
			}
			return ret;
		}
	}
	
	public static void run() {
		int[] payout = new int[10];
		for(int i=1;i<10;++i) payout[i]=scanner.nextInt();
		int nq=scanner.nextInt();
		for(int q=0;q<nq;++q) {
			Card[] hand = new Card[5];
			for(int i=0;i<5;++i) hand[i]=new Card(scanner);

			long left=(1L<<52)-1;
			for(int i=0;i<5;++i) left-=1L<<hand[i].code();

			double best=0;
			for(int i=0;i<(1<<5);++i) {
				ArrayList<Card> keep=new ArrayList<Card>();
				for(int j=0;j<5;++j) if((i&(1<<j))!=0) keep.add(hand[j]);
				int[] freqs=go(keep,0,left);
				int tot=0; for(int j=0;j<10;++j) tot+=freqs[j];
				int get=0; for(int j=0;j<10;++j) get+=payout[j]*freqs[j];
				double cur=1.0*get/tot;
//				System.out.println(i);
//				for(int j=0;j<10;++j) System.out.print(freqs[j]+" "); System.out.println(cur);
				if(cur>best) best=cur;
			}
			System.out.println(best);
		}
	}
	
	public static void main(String[] args) {
		scanner = new Scanner(System.in);
		int n=scanner.nextInt();
		for(int i=0;i<n;++i) run();
	}
}

class Card {
	public int rank;
	public int suit;
	public static String ranks="23456789TJQKA";
	public static String suits="cdhs";
	
	public Card(int rank,int suit) {
		this.rank=rank;
		this.suit=suit;
	}
	
	public Card(Scanner scanner) {
		String str=scanner.next();
		rank=ranks.indexOf(str.charAt(0));
		suit=suits.indexOf(str.charAt(1));
		if(rank==-1) throw new RuntimeException("Unknown rank");
		if(suit==-1) throw new RuntimeException("Unknown suit");
	}
	
	public String toString() {
		return ""+ranks.charAt(rank)+suits.charAt(suit);
	}
	
	public int code() { return suit*13+rank; }
}
