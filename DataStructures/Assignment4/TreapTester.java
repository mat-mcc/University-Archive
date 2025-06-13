import static org.junit.Assert.*;

import org.junit.Test;

public class TreapTester {

	@Test
	public void addTest() {
		Treap<Integer> testTree = new Treap<Integer>();
		// example tree from pdf
		assertTrue(testTree.add(4,19));
		assertTrue(testTree.add(2,31));
		assertTrue(testTree.add(6,70));
		assertTrue(testTree.add(1, 84));
		assertTrue(testTree.add(3,12));
		assertTrue(testTree.add(5,83));
		assertTrue(testTree.add(7,26));
	}

	@Test
	public void removeTest() {
		Treap<Integer> testTree = new Treap<Integer>();
		assertTrue(testTree.add(4,19));
		assertTrue(testTree.delete(4));
		assertTrue(testTree.add(6,70));
		assertTrue(testTree.add(5,83));
		assertTrue(testTree.delete(6));
		assertFalse(testTree.delete(9));
	}
	
	@Test
	public void findTest() {
		Treap<Integer> testTree = new Treap<Integer>();
		assertTrue(testTree.add(4,19));
		assertTrue(testTree.add(6,70));
		assertTrue(testTree.add(5,83));
		assertTrue(testTree.find(5));
		assertTrue(testTree.find(4));
		assertTrue(testTree.find(6));
		assertFalse(testTree.find(9));
	}
	
	@Test 
	public void combinedTest() {
		Treap<Integer> testTree = new Treap<Integer>();
		assertTrue(testTree.add(4,19));
		assertTrue(testTree.add(6,70));
		assertTrue(testTree.add(5,83));
		assertTrue(testTree.find(5));
		assertTrue(testTree.delete(5));
		assertFalse(testTree.find(5));
		assertFalse(testTree.add(4,31));
		assertTrue(testTree.find(4));
	}
}
