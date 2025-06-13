

/* 
 *MATTHEW MCCAUGHAN
 * CS 284 ASSIGNMENT 5
 * I PLEDGE MY HONOR THAT I HAVE ABIDED BY THE STEVENS HONOR SYSTEM
 */

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class Sort {
	
	private static class Interval { 
		private int upper;
		private int lower;
		
		public Interval(int lower, int upper) {
			this.upper = upper;
			this.lower = lower;
		}
		
		public int getLower() {
		return lower;
		}
		
		public int getUpper() {
			return upper;
		}
		public boolean equals(Object o) {
			return true;

		}
		public int hashCode() {
			return ((lower*lower)+upper);
		}
		
		public String toString() {
			return ("("+ this.lower + "," + this.upper+")");
		}
		
	
	}
	
	public static <T extends Comparable <T> > void sort (T[] array) {
		
		// INITIALIZES SET
		Set<Interval> IntervalSet = new HashSet<>();
		
		// ADDS BOUDNS OF ARRAY AS THE FIRST ELEMENT IN SET
		IntervalSet.add(new Interval(0, array.length-1));
		
		// ITERATES THROUGH INTERVALSET UNTIL EMPTY (ARRAY SORTED)
		
		while (!IntervalSet.isEmpty()) {
			
			
			Interval i = IntervalSet.iterator().next();
			int upper = i.getUpper();
			//System.out.println(upper);
			int lower = i.getLower();
			//System.out.println(lower);
			
			// CALLS PARTITION AS RESULT OF PIVOTINDEX
		    int pivotIndex = partition(array, lower, upper);
			
			// ADDS INTERVALS BASED ON PIVOTINDEX
			IntervalSet.add(new Interval(lower, pivotIndex));
			IntervalSet.add(new Interval(pivotIndex + 1, upper));
			
		
			
			
		    // REMOVES INTERVAL I AFTER SORTED
			IntervalSet.remove(i);
		}
	}
		
		
		/*
		 * PARTITION METHOD
		 * CALLED IN SORT
		 * RETURNS INT DOWN
		 * 
		 */
		public static <T extends Comparable <T> > int partition (T[] array, int first, int last) {
			
		// GETS THE ELEMENTS AT THE LAST, FIRST, AND MIDDLE POSITION
			int upr = (int) array[array.length-1];
			//System.out.println("upr: " + upr);
			int lwr = (int) array[0];
			//System.out.println("lwr: "+ lwr);
			int mid = (int) array[(array.length-1)/2];
			//System.out.println("mid: " + mid);
			
			// ARRAYLIST OF FIRST, MIDDLE, AND LAST ELEMENT
			ArrayList<Integer> Three = new ArrayList<Integer>();
			Three.add(upr);
			Three.add(lwr);
			Three.add(mid);
			//System.out.println(Three);
			
			
			// CALL BUBBLESORT ON "THREE"
			Bubblesort(Three);
			
			
			//SWAP MEDIAN WITH ELEMENT AT POSITION FIRST
			int temp = Three.get(1);
			//System.out.println(temp);
			Three.set(1, Three.get(0));
			Three.set(0, temp);
			//System.out.println(Three);
		
			
		    // PARTITION ALGORITHM
			
			T pivot = (T) Three.get(1);
		    int up = first;
		    int down = last;
		   // System.out.println("first = " + first);
		   // System.out.println("last = " + last);
			
		    do {
		    	/* INCRMEMENT UP UNTIL UP SELECTS THE FIRST
		    	 * ELEMENT GREATER THAN THE PIVOT VALUE OR
		    	 * UP HAS REACHED LAST
		    	 */
		 
				while((up < last) && (pivot.compareTo(array[up]) >= 0)) {
					up++;
					
				/* DECREMENT DOWN UNTL DOWN SELECTS THE FIRST ELEMENT
				 * LESS THAN OR EQUAL TO THE PIVOT VALUE OR DOWN HAS BEEN REACHED
				 */
				}
				while((pivot.compareTo(array[down]) < 0) && (down != 0)) {
					down--;
				}
				if (up< down) { // IF UP IS TO THE LEFT OF DOWN
					swap(array, up, down);
					//T temp1 = array[up];
					//array[up] = array[down];
					//array[down] = temp1;
				}
				} while (up<down); // REPEAT WHILE UP IS LEFT OF DOWN
				swap(array, first, down);
				T temp2  = array[first];
				array[first] = array[down];
				array[down] = temp2;
				Arrays.sort(array);
				return down;
				
		}	
		
		// HELPER FUNCTION SWAP
		// SWAPS THE POSITIONS OF I AND J IN T[]
		public static <T extends Comparable<T>> void swap(T[] arr, int i, int j)
		{
		    T temp = arr[i];
		    arr[i] = arr[j];
		    arr[j] = temp;
		}
		   
		// HELPER FUNCTION BUBBLESORT
		// PERFORMS BUBBLESORT ON A GIVEN ARRAYLIST
		public static <T extends Comparable<T>> void Bubblesort(ArrayList<T> table) {
			int pass = 1;
			boolean exchanges = false;
			do {
				exchanges = false;
				for (int i = 0; i < table.size()- pass; i++) {
					if((table.get(i).compareTo(table.get(i+1))) > 0) {
						T temp = table.get(i);
						table.set(i, table.get(i+1));
						table.set(i+1, temp);
			
						exchanges = true;
					}
				}
				pass++;
			} while(exchanges);
		}
			
				
			
			
		


	public static void main(String[] args) {
		
		//Integer[] a = {2,1};
	        //Integer[] a = {3,2,1};
	        //Integer[] a = {9,2,5,6,7,4,3,8,1};
	        //Integer[] a = {10,9,8,7,6,5,4,3,2,1};
	        //Integer[] a = {2,5,3,0,2,3,0,3};
	       //Integer[] a = {3,4,7,1,8,5,2,9,0,6};
	        //Integer[] a  = {3,4,7,1,5,8,2,9,0,6};
	       Integer[] a = {11,5,13,4,16,7,12,14,1,17,10,8,3,2,15,9,0,6};
	        
	        System.out.println("Original: ");
	        for (int i=0; i<a.length; i++) {
	            System.out.print(a[i] + " ");
	        }        
	        sort(a);
	        System.out.println("\nSorted: ");
	        for (int i=0; i<a.length; i++) {
	            System.out.print(a[i] + " ");
	        }
	    

	 
	
		//Interval test = new Interval(2,8);
		//System.out.println(test.getUpper());
		//System.out.println(test.getLower());
		//System.out.println(test.hashCode());
		/*Set<Interval> tester = new HashSet<>();
		tester.add(new Interval(2,13));
		tester.add(new Interval(8,12));
		System.out.println(tester.toString());
		*/
	
		/*
		
		Integer[] TEST = {9,2,5,7,6,4,8,3,1};
		Integer[] TESTcompare = {1,2,3,4,5,6,7,8,9};
		
		System.out.println(Arrays.toString(TEST));
		sort(TEST);
		// {1,2,3,4,5,6,7,8,9}
		System.out.println(Arrays.toString(TEST));
		System.out.println(TEST[0] == TESTcompare[0]);
		
		*/
	
		//sort(TEST);
		//System.out.println(Arrays.toString(TEST));
		/*
		// BUBBLESORT TESTER
		ArrayList<Integer> Three = new ArrayList<Integer>();
		Three.add(19);
		Three.add(3);
		Three.add(16);
		System.out.println(Three);
		Bubblesort(Three);
		System.out.println(Three);
		int temp = Three.get(1);
		Three.set(1, Three.get(0));
		Three.set(0, temp);
		System.out.println(Three);
		*/
		//System.out.println(sort(testArray));
		
		
		
		
		

	}

	}
