
import java.util.Arrays;
import java.util.Random;

// Matthew McCaughan
// I pledge my honor that I have abided by the Stevens Honor System

public class CoinPurse {

	// data fields
	private int Galleons;
	private int Sickles;
	private int Knuts;

	// Constructor
	public CoinPurse(int Galleons, int Sickles, int Knuts) {
		if (Galleons > 256 || Sickles > 256 || Knuts > 256) {
			throw new IllegalArgumentException("Can only hold 256 coins of a type!");
		}

		this.Galleons = Galleons;
		this.Sickles = Sickles;
		this.Knuts = Knuts;

	}

	// String: ToString method
	public String toString() {
		return "This Coinpurse has " + Galleons + " Galleons, " + Sickles + " Sickles, and " + Knuts + " Knuts";
	}

	// DEPOSITS: Deposits Galleons, Sickles, and Knuts.

	public void depositGalleons(int n) {
		int current = Galleons;
		if (n + current > 256) {
			throw new IllegalArgumentException("Adding this amount will exceed 256!");
		}
		if (n < 0) {
			throw new IllegalArgumentException("Cannot add negative coins!");
		}
		Galleons = n + Galleons;

	}

	public void depositSickles(int n) {
		int current = Sickles;
		if (n + current > 256) {
			throw new IllegalArgumentException("Adding this amount will exceed 256!");
		}
		if (n < 0) {
			throw new IllegalArgumentException("Cannot add negative coins!");
		}
		Sickles = n + Sickles;

	}

	public void depositKnuts(int n) {
		int current = Knuts;
		if (n + current > 256) {
			throw new IllegalArgumentException("Adding this amount will exceed 256!");
		}
		if (n < 0) {
			throw new IllegalArgumentException("Cannot add negative coins!");
		}
		Knuts = n + Knuts;
	}

	// WITHDRAWAL: Withdraws Galleons, Sickles, and Knuts.

	public void withdrawGalleons(int n) {
		int current = Galleons;
		if (n < 0) {
			throw new IllegalArgumentException("Cannot remove negative coins!");
		}
		if (current - n < 0) {
			throw new IllegalArgumentException("Removing this many coins will result in a negative balance!");
		}
		Galleons = Galleons - n;

	}

	public void withdrawSickles(int n) {
		int current = Sickles;
		if (n < 0) {
			throw new IllegalArgumentException("Cannot remove negative coins!");
		}
		if (current - n < 0) {
			throw new IllegalArgumentException("Removing this many coins will result in a negative balance!");
		}
		Sickles = Sickles - n;
	}

	public void withdrawKnuts(int n) {
		int current = Knuts;
		if (n < 0) {
			throw new IllegalArgumentException("Cannot remove negative coins!");
		}
		if (current - n < 0) {
			throw new IllegalArgumentException("Removing this many coins will result in a negative balance!");
		}
		Knuts = Knuts - n;
	}

	// Cumulative Operations

	public int numCoins() {
		return Galleons + Sickles + Knuts;
	}

	public int totalValue() {
		return 493 * Galleons + (29 * Sickles) + Knuts;
	}

	public boolean exactChange(int n) { /*
										 * exactChange iterates through every combination of Galleons, Sickles, and
										 * Knuts, if some combination matches the value of the exact change, then the
										 * function returns true (else false).
										 */

		for (int a = 0; a < Galleons; a++) {
			for (int b = 0; b < Sickles; b++) {
				for (int c = 0; c < Knuts; c++) {
					if (n == 493 * a + (29 * b) + c)

						return true;

				}
			}
		}
		return false;
	}

	public int[] withdraw(int n) { /*
									 * withdraw iterates through every combination of Galleons, Sickles, and Knuts
									 * to determine an exact match and displays the number of coins for this match.
									 */

		if (493 * Galleons + (29 * Sickles) + Knuts < n) {
			throw new IllegalArgumentException("This value exceeds the total value!");
		}
		int[] solution = new int[3];
		for (int a = 0; a < Galleons; a++) {
			for (int b = 0; b < Sickles; b++) {
				for (int c = 0; c < Knuts; c++) {
					if (n == 493 * a + (29 * b) + c) {
						solution[0] = a;
						solution[1] = b;
						solution[2] = c;
						return solution;
					}
				}
			}

		}
		return solution;
	}

	// A Game of Chance

	public int drawRandCoin() { /*
								 * draws a coin based on values from 0 to 2, PROPORTIONAL to how much of each
								 * type of coin exists in the purse
								 */

		int a = Galleons;
		int b = Sickles;
		int c = Knuts;
		double sum = (a + b + c);
		double asum = a / sum;
		double bsum = b / sum;
		double csum = c / sum;
		double d = Math.random();
		if (0 < d & d < asum)
			return 2; // Returns 2 for Galleons

		if (asum < d & d < asum + bsum)
			return 1; // returns 1 for Sickles

		if (asum + bsum < d & d < asum + bsum + csum)
			return 0; // returns 0 for Knuts
		return -1;
	}

	public int[] drawRandSequence(int n) { // Draws random sequence of n numbers.
		if (Galleons == 0 || Sickles == 0 || Knuts == 0) {
			throw new IllegalArgumentException("Cannot draw from no coins!");
		}

		int[] sequence = new int[n]; // for loop that creates the array
		for (int i = 0; i < n; i++) {
			sequence[i] = drawRandCoin();

		}
		return sequence;
	}

	public static int compareSequences(int[] coinSeq1, int[] coinSeq2) { // compares coinSeq1 to coinSeq2
		if (coinSeq1.length != coinSeq2.length) {
			throw new ArrayIndexOutOfBoundsException("Sequences are not the same length!");
		} else {
			int counter = 0; // create variable counter that tracks who "wins".
			for (int i = 0; i < coinSeq1.length; i++) {
				if (coinSeq1[i] == coinSeq2[i]) {
					continue;
				}
				if (coinSeq1[i] > coinSeq2[i]) {
					counter += 1;
				}
				if (coinSeq1[1] < coinSeq2[i]) {
					counter -= 1;
				}
				int result = 0; // creates variable result that looks at the sign of counter.

				if (counter > 0) {
					result = 1;
				}
				if (counter < 0) {
					result = -1;
				}
				if (counter == 0) {
					result = 0;
				}
				return result;
			}
		}
		return 0;
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		/*
		 * CoinPurse TESTING = new CoinPurse(2, 5, 10); System.out.println(TESTING);
		 * System.out.println(TESTING.numCoins());
		 * System.out.println(TESTING.totalValue());
		 * System.out.println(TESTING.toString());
		 * System.out.println(TESTING.exactChange(559));
		 * System.out.println(TESTING.drawRandCoin());
		 * System.out.println(TESTING.exactChange(564));
		 * System.out.println((Arrays.toString(TESTING.drawRandSequence(4)))); int
		 * array1[] = { 1, 2, 3, 4 }; int array2[] = { 1, 2, 3, 5 };
		 * System.out.println(CoinPurse.compareSequences(array1, array2));
		 * System.out.println((Arrays.toString(TESTING.withdraw(559))));
		 * 
		 * }
		 */

	}
}
