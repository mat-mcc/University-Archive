package hw3;

import static org.junit.Assert.assertThrows;
import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class MultiplayerGameTest {
	@Test
	public void testAdd() {
		MultiplayerGame ex = new MultiplayerGame(2);
		ex.addGamePiece(0, "PIECE ONE", 4);
		assertEquals(ex.size(), 1);
	}
		
	@Test
	public void testInvalidPiece1() {
		assertThrows( IllegalArgumentException.class, () -> {
			MultiplayerGame ex2 = new MultiplayerGame(2);
			ex2.addGamePiece(-1, "This better not work!", 4);
			
		});
}
	
	@Test
	public void testInvalidPiece2() {
		assertThrows( IllegalArgumentException.class, () -> {
			MultiplayerGame ex2 = new MultiplayerGame(2);
			ex2.addGamePiece(2, "This also better not work!", 4);
			
		});
}
	@Test
	public void testDuplicateAdditions() {
		assertThrows( IllegalArgumentException.class, () -> {
			MultiplayerGame ex2 = new MultiplayerGame(2);
			ex2.addGamePiece(1, "These are the same!", 4);
			ex2.addGamePiece(1, "These are the same!", 4);
			
		});
}
	@Test
	public void testRemove() {
		MultiplayerGame ex = new MultiplayerGame(2);
		ex.addGamePiece(0, "PIECE ONE", 4);
		ex.addGamePiece(1, "PIECE TWO", 4);
		ex.addGamePiece(1, "PIECE THREE", 4);
		ex.removeGamePiece(1, "PIECE TWO");
		assertEquals(ex.size(), 2);

	
	
	
}
	
	@Test
	public void testNonexistantRemoval() {
		assertThrows( IllegalArgumentException.class, () -> {
			MultiplayerGame ex2 = new MultiplayerGame(2);
			ex2.removeGamePiece(1, "This Piece doesn't exist! You can't remove it!");

			
		});
}
	@Test
	public void testNonexistantRemoval2() {
		assertThrows( IllegalArgumentException.class, () -> {
			MultiplayerGame ex2 = new MultiplayerGame(2);
			ex2.addGamePiece(1, "PIECE ONE", 4);
			ex2.removeGamePiece(1, "This Piece doesn't exist!");

			
		});
}
	@Test
	public void testRemoveAllFromPlayer() {
		MultiplayerGame ex = new MultiplayerGame(2);
		ex.addGamePiece(0, "PIECE ONE", 4);
		ex.addGamePiece(1, "PIECE TWO", 4);
		ex.addGamePiece(1, "PIECE THREE", 4);
		ex.removeAllGamePieces(1);
		assertEquals(ex.size(), 1);
		
	}
	@Test
	public void testRemoveEverything() {
		MultiplayerGame ex = new MultiplayerGame(2);
		ex.addGamePiece(0, "PIECE ONE", 4);
		ex.addGamePiece(1, "PIECE TWO", 4);
		ex.addGamePiece(1, "PIECE THREE", 4);
		ex.removeAllGamePieces(1);
		ex.removeAllGamePieces(0);
		assertEquals(ex.size(), 0);
		
	}
	@Test
	public void testHasGamePiece() {
		MultiplayerGame ex = new MultiplayerGame(2);
		ex.addGamePiece(0, "PIECE ONE", 4);
		ex.addGamePiece(1, "PIECE TWO", 4);
		ex.addGamePiece(1, "PIECE THREE", 4);
		assertTrue(ex.hasGamePiece("PIECE TWO"));
		
	}
	
	@Test
	public void testIncreaseStrength() {
		MultiplayerGame ex = new MultiplayerGame(2);
		ex.addGamePiece(0, "PIECE ONE", 4);
		ex.addGamePiece(1, "PIECE TWO", 4);
		ex.addGamePiece(1, "PIECE THREE", 4);
		ex.increaseStrength(0, 1);
		GameEntity current = ex.index[0];
		current = current.next;
		assertEquals(((GamePiece) current).getStrength(), 5);
	}
	


		
		
	}

