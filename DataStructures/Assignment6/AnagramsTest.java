import static org.junit.Assert.*;

import java.util.ArrayList;
import java.util.Map;
import java.util.Map.Entry;

import org.junit.Test;

public class AnagramsTest {

	@Test
	public void addWordTest() {
		Anagrams Test = new Anagrams();
		Test.addWord("a");
		Test.addWord("z");
		Test.addWord("hello");
		Test.addWord("alerts");
		
		assertTrue(Test.anagramTable.containsKey(101L));
		assertTrue(Test.anagramTable.containsKey(2L));
		assertFalse(Test.anagramTable.containsKey(3L));
		assertTrue(Test.anagramTable.containsKey(13447687L));
		assertFalse(Test.anagramTable.containsKey(13447688L));
		assertTrue(Test.anagramTable.containsKey(236204078L));
	}
	
	@Test
	public void hashcodeTest() {
		Anagrams Test = new Anagrams();
		long a = Test.myHashCode("hello");
		long b = Test.myHashCode("alerts");
		long c = Test.myHashCode("ab");
		long d = Test.myHashCode("abc");
		
		assertEquals(a, 13447687L);
		assertEquals(b, 236204078L);
		assertEquals(c, 6L);
		assertEquals(d, 30L);
		assertNotEquals(c, 3L);
		assertNotEquals(c, 30L);
		assertNotEquals(a, 2L);
		assertNotEquals(a, 0L);
		
	}
	
	@Test
	public void getMaxEntriesTest() {
		Anagrams a = new Anagrams();
				
		a.addWord("hello");
		a.addWord("llheo");
		a.addWord("helol");
		a.addWord("alerts");
		a.addWord("time");
		a.addWord("mite");
		a.addWord("beef");
		a.addWord("feeb");
		a.addWord("febe");
		a.addWord("bfee");
		a.addWord("fbee");
		a.addWord("tomorrow");
		a.addWord("happy");
		a.addWord("tomorrows");
		a.addWord("holle");
		
		ArrayList <Map.Entry <Long,ArrayList<String>>> maxEntries = a.getMaxEntries();
		//System.out.println(maxEntries);
		ArrayList <Map.Entry <Long,ArrayList<String>>> Compare = new ArrayList<Entry<Long, ArrayList<String>>>();
		Compare.add(maxEntries.get(0));
		//System.out.println(Compare);
		//System.out.println(maxEntries);
		assertEquals(maxEntries, Compare);

		

		
	}
	

}
