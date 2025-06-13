

// ASSIGNMENT SIX
// CS 284-E
// Matthew McCaughan
// I pledge my honor that I have abided by the Stevens Honor System.


import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

public class Anagrams {
	



// initializes primes
	final Integer[] primes = {2 , 3 , 5 , 7, 11 , 13 , 17 , 19 , 23 , 29 , 31 , 37 , 41 , 43 , 47 , 53 , 59 , 61 ,
			67 , 71 , 73 , 79 , 83 , 89 , 97 , 101};


	
	Map<Character,Integer> letterTable;
	
	Map<Long,ArrayList<String>> anagramTable;
	
	
	// Constructor, initializes buildLetterTable() and the anagramTable
	public Anagrams () {
		buildLetterTable();
		anagramTable = new HashMap<>();
	}
	
	// given method for processing a file.
	public void processFile ( String s) throws IOException {
		FileInputStream fstream = new FileInputStream (s );
		BufferedReader br = new BufferedReader ( new InputStreamReader ( fstream ));
		String strLine ;
		while (( strLine = br.readLine ()) != null ) {
		this.addWord(strLine);
		}
		br.close ();
		}
	
	// constructs letter table through the use of the primes, mapping each letter to a unique prime numbers.
	public void buildLetterTable() {
		String alphabet = "abcdefghijklmnopqrstuvwxyz";
		letterTable = new HashMap<>();
		
		for (int i = 0; i < 26; i++) {
			letterTable.put( (char) alphabet.charAt(i), primes[i]);
		}
		
		}
	// takes a String s and returns its equivalent hashcode, its representation as a long.
	public long myHashCode(String s) {
		if (s == "") {
			throw new IllegalArgumentException();
		}
		
	
		char[] stringArray = s.toLowerCase().toCharArray();
		int value = 1;
		value = value *letterTable.get(stringArray[0]);
		for (int i = 0; i < stringArray.length-1; i++) {
			value = (value*letterTable.get(stringArray[i+1]));
			
			value = Math.abs(value);
			
			
		}
		return value;
	}
	
	
	// adds the words and its computed hash code into the anagramTable.
	public void addWord(String s) {
		/*
		if (anagramTable.containsValue(s)) {
			throw new IllegalArgumentException("addWord: duplicate value.");
		}
		*/
		long hash = myHashCode(s);
		ArrayList<String> stringArray = new ArrayList<String>();
		stringArray.add(s);
		

		
		if (anagramTable.containsKey(hash)) {
			anagramTable.get(hash);
			stringArray.addAll(anagramTable.get(hash));
		}
		anagramTable.put(hash, stringArray);
		
	}
	//Returs the entries in the anagramTable that have the largest number of anagrams
	public ArrayList<Map.Entry<Long,ArrayList<String>>> getMaxEntries(){
		
		
		//arraylist of map entries with max # of anagrams
		ArrayList <Map.Entry<Long,ArrayList<String>>> max = new ArrayList <Map.Entry<Long,ArrayList<String>>> ();
		
		
		// temp stores all the entries in the anagram table
		Set<Map.Entry<Long,ArrayList<String>>> temp = anagramTable.entrySet();
		
		// maxSize stores the size of the largest list of anagrams
		int maxSize = 0;
		
		
		// create Iterator to help iterate through entrySet temp
		Iterator<Map.Entry<Long,ArrayList<String>>> I = temp.iterator();
		
		
		// Iterate through temp through the use of I
		while(I.hasNext()) {
	
			// if the length of values cooresponding to the key is greater than the current 
			Entry<Long, ArrayList<String>> A = I.next();
		if(A.getValue().size() > maxSize) {
			maxSize = A.getValue().size();
			//System.out.println(maxSize);
		
			

		
			
		}
		}
		
		
		// second iteration, iterates to element with max size, and adds to max
		Iterator<Map.Entry<Long,ArrayList<String>>> J = temp.iterator();
		while(J.hasNext()) {
			
		Entry<Long, ArrayList<String>> K = J.next();
			if(K.getValue().size() == maxSize) {
				max.add(K);
				
				}

		}
		
		// return max
		return max;
		
	}
	

	public static void main ( String [] args ) {
		Anagrams a = new Anagrams();
	
			final long startTime = System.nanoTime();
			
			try {
				a.processFile("words_alpha.txt");
			} catch(IOException e1) {
				e1.printStackTrace();
			}

			ArrayList <Map.Entry <Long,ArrayList<String>>> maxEntries = a.getMaxEntries();
			final long estimatedTime = System.nanoTime() - startTime;
			final double seconds = ((double) estimatedTime/1000000000);
			System.out.println(a.anagramTable.entrySet());
			System.out.println(" Time : "+ seconds );
			System.out.println(" List of max anagrams : "+ maxEntries );
			
			

	}
}
		





