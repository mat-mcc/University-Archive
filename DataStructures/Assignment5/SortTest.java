import static org.junit.Assert.*;

import org.junit.Test;

public class SortTest {
	
	@Test
	public void test0() {
		Integer[] a = {11,5,13,4,16,7,12,14,1,17,10,8,3,2,15,9,0,6};
		Integer[] b = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
		Sort.sort(a);
		assertTrue(a[0] == b[0]);
		assertTrue(a[1] == b[1]);
		assertTrue(a[2] == b[2]);
		assertTrue(a[3] == b[3]);
		assertTrue(a[4] == b[4]);
		assertTrue(a[5] == b[5]);
		assertTrue(a[6] == b[6]);
		assertTrue(a[7] == b[7]);
		assertTrue(a[8] == b[8]);
		assertTrue(a[9] == b[9]);

		
	}

	@Test
	public void test1() {
		Integer[] a = {9,2,5,6,7,4,3,8,1};
		Integer[] b = {1,2,3,4,5,6,7,8,9};
		Sort.sort(a);
		assertTrue(a[4] == b[4]);
		assertTrue(a[5] == b[5]);
		assertTrue(a[6] == b[6]);
		assertTrue(a[7] == b[7]);
		
	}
	
	@Test
	public void test2() {
		Integer[] a = {10,9,8,7,6,5,4,3,2,1};
		Integer[] b = {1,2,3,4,5,6,7,8,9,10};
		Sort.sort(a);
		assertTrue(a[3] == b[3]);
		assertTrue(a[4] == b[4]);
		assertTrue(a[5] == b[5]);
		assertTrue(a[6] == b[6]);
		
	}
	@Test
	public void test3() {
		Integer[] a = {3,4,7,1,8,5,2,9,0,6};
		Sort.sort(a);
		assertTrue(a[0] == 0);
		assertTrue(a[1] == 1);
		
	}
	@Test
	public void test4() {
		Integer[] a = {5,4,7,1,8,3,2,9,0,6};
		Integer[] b = {0,1,2,3,4,5,6,7,8,9};
		Sort.sort(a);
		assertTrue(a[6] == b[6]);
		assertTrue(a[7] == b[7]);
		assertTrue(a[8] == b[8]);
		
	}

}
