package hw3;

// Matthew McCaughan
// I pledge my honor that I have abided by the Stevens Honor System.

public class MultiplayerGame {

	private GameEntity turnTracker;
	public GameEntity[] index;

	/*
	 * MultiplayerGame: creates a multiplayer game with n players Input: int n
	 * Creates an array of size n, and assigns each index in "index" to a new
	 * GamePiece
	 */
	public MultiplayerGame(int n) {
		if (n <= 0) {
			throw new IllegalArgumentException("invalid number of players!");
		} else {
			// index = new GameEntity[n];
			index = new GameEntity[n];

			// if there is 1 player
			if (n == 1) {
				index[0] = new GamePlayer(null, null, 0);
				index[0].next = index[0];
				index[0].prev = index[0];
				return;
			}

			// if there is more than 1 player
			else {
				index[0] = new GamePlayer(null, null, 0);

				for (int i = 1; i < n - 1; i++) {
					index[i] = new GamePlayer(null, null, i);
				}
				index[n - 1] = new GamePlayer(null, null, n - 1);
				index[n - 1].next = index[0];
				index[n - 1].prev = index[n - 2];
				index[0].next = index[1];

				index[0].next = index[1];
				index[0].prev = index[n - 1];

				for (int i = 1; i < n - 1; i++) {
					index[i].next = index[i + 1];
					index[i].prev = index[i - 1];
				}
			}
		}
	}

	// size returns the size of the game, that is, the amount of GamePieces in play.
	public int size() {
		GameEntity current = index[0].next;
		int counter = 0;

		while (current != index[0]) {
			if (current instanceof GamePiece) {
				counter++;
			}
			current = current.next;

		}
		return counter;
	}

	// addGamePiece adds a new GamePiece entity, attributes it to player "playerId",
	// with name "name" and strength "strength"
	public void addGamePiece(int playerId, String name, int strength) {

		if (playerId < 0) {
			throw new IllegalArgumentException("invalid playerId");
		}
		if (hasGamePiece(name) == true) {
			throw new IllegalArgumentException("addGamePiece: duplicate entity");
		}
		if (playerId >= index.length) {
			throw new IllegalArgumentException("addGamePiece: no such player");
		}

		GameEntity NewPiece = new GamePiece(null, null, name, strength);
		GameEntity current = index[playerId];

		// GAME OF ONE PLAYER

		// IF GAME OF ONE PLAYER IS ADDING AN ADDITIONAL PIECE
		if (index.length == 1) {
			if (current.next instanceof GamePiece) {
				while (current.next instanceof GamePiece) {
					current = current.next;
				}

				current.next = NewPiece;
				NewPiece.next = index[0];
				NewPiece.prev = current;
				return;
			}

			// IF GAME OF ONE PLAYER ADDING FIRST PIECE
			else {
				index[0].next = NewPiece;
				index[0].prev = NewPiece;
				NewPiece.next = index[playerId];
				NewPiece.prev = index[playerId];
				return;

			}
		}
		// IF A GAMEPIECE IS ALREADY EXISTING OWNED BY PLAYERID
		if (current.next instanceof GamePiece) {
			while (current.next instanceof GamePiece) {
				current = current.next;
			}
			// ADDING ANOTHER GAMEPIECE TO LAST PLAYER
			if (current.next == index[0]) {
				current.next = NewPiece;
				NewPiece.prev = index[playerId];
				NewPiece.next = index[0];
				return;

			}

			current.next = NewPiece;
			NewPiece.next = index[playerId + 1];
			NewPiece.prev = current;
			return;
		}
		// FIRST GAMEPIECE OF A PLAYER WITH MULTIPLE PLAYERS
		else {
			// IF ADDING A GAME PIECE TO THE LAST PLAYER
			if (index[playerId].next == index[0]) {
				current.next = NewPiece;
				NewPiece.prev = index[playerId];
				NewPiece.next = index[0];
				return;
			}
			index[playerId].next = NewPiece;
			NewPiece.prev = index[playerId];
			NewPiece.next = index[playerId + 1];

			return;

		}
	}

	// removeGamePiece removes a gamepiece owned by "playerId", with name "name".
	public void removeGamePiece(int playerId, String name) {
		GameEntity current = index[playerId];
		GameEntity LastPlayer = index[index.length - 1];

		if (playerId < 0) {
			throw new IllegalArgumentException("invalid playerId");
		}
		if (playerId > index.length) {
			throw new IllegalArgumentException("removeGamePiece: no such player");
		}
		if (hasGamePiece(name) == false) {
			throw new IllegalArgumentException("removeGamePiece: entity does not exist");
		}

		// IF GAME IS ONE PLAYER (ANY AMOUNT OF PIECES):

		if (index.length == 1) {
			current = index[playerId].next;
			while (current != index[0]) {
				if (current.getName() == name) {
					current = current.prev;
					current.next = current.next.next;
				}
				current = current.next;
			}
			return;
		}

		// IF GAME MORE THAN ONE PLAYER:
		if (index.length > 1) {
			// IF PLAYER IS LAST PLAYER
			if (current == LastPlayer) {
				current = index[playerId];
				while (current != index[0]) {
					if (current.next.getName() == name) {
						current.next = current.next.next;
					}
					current = current.next;
				}
				return;
			}
			// IF PLAYER IS NOT LAST PLAYER
			else {
				current = index[playerId];
				while (current != index[playerId + 1]) {
					if (current.next.getName() == name) {
						current.next = current.next.next;
					}
					current = current.next;
				}
				return;
			}
		}
	}

	// hasGamePiece returns true if any Player has a GamePiece with name "name"
	public boolean hasGamePiece(String name) {
		GameEntity current = index[0].next;

		while (current != index[0]) {
			if (current.getName() == name) {
				return true;
			}
			current = current.next;

		}
		return false;
	}

	// removeAllGamePieces revmoes all GamePiece entities owned by playerId.
	public void removeAllGamePieces(int playerId) {
		if (playerId < 0) {
			throw new IllegalArgumentException("removeAllGamePieces: no such player");
		}
		if (playerId > index.length) {
			throw new IllegalArgumentException("removeAllGamePieces: no such player");
		}

		GameEntity current = index[playerId];
		GameEntity LastPlayer = index[index.length - 1];

		// PLAYER IS LAST PLAYER
		if (current == LastPlayer) {
			while (current != index[0]) {
				if (current instanceof GamePiece) {
					removeGamePiece(playerId, current.getName());
				}
				current = current.next;
			}

			return;
		}
		// PLAYER IS NOT LAST PLAYER
		else {

			while (current != index[playerId + 1]) {
				if (current instanceof GamePiece) {
					removeGamePiece(playerId, current.getName());

				}

				current = current.next;
			}
			return;
		}

	}

	// increaseStrength increases the strength of every GamePiece owned by playerId,
	// by n.
	public void increaseStrength(int playerId, int n) {
		if (playerId < 0) {
			throw new IllegalArgumentException("increaseStrength: no such player");
		}
		if (playerId > index.length) {
			throw new IllegalArgumentException("increaseStrength: no such player");
		}
		GameEntity current = index[playerId];
		GameEntity LastPlayer = index[index.length - 1];
		if (current == LastPlayer) {
			while (current != index[0]) {
				if (current instanceof GamePiece) {
					((GamePiece) current).updateStrength(n);

				}
				current = current.next;
			}
			return;

		} else {
			while (current != index[playerId + 1]) {
				if (current instanceof GamePiece) {
					((GamePiece) current).updateStrength(n);

				}
				current = current.next;
			}
			return;
		}
	}

	// toString constructs a string representation of the MultiplayerGame, incluidng
	// players and the pieces they own.
	public String toString() {

		StringBuilder sb = new StringBuilder();

		sb.append("[ ");
		// IF LENGTH IS ONE;
		if (index.length == 1) {
			GameEntity current = index[0].next;
			sb.append(index[0].toString());
			sb.append("; ");
			while (current != index[0]) {
				sb.append(current.toString());
				sb.append("; ");
				current = current.next;
			}
			sb.append("]");
			return sb.toString();
			// IF MORE THAN ONE PLAYER
		} else {
			GameEntity current = index[0].next;
			sb.append(index[0].toString());
			sb.append("; ");
			while (current != index[0]) {
				sb.append(current.toString());
				sb.append("; ");
				current = current.next;
			}

			sb.append("]");
			return sb.toString();

		}

	}

	// sets turnTracker to the first player
	public void initializeTurnTracker() {
		GameEntity current = index[0];
		turnTracker = current;

	}

	// sets turnTracker to the next player
	public void nextPlayer() {
		GameEntity current = turnTracker;
		current = current.next;
		while (true) {

			if (current instanceof GamePlayer) {
				turnTracker = current;
				return;
			}
			current = current.next;
		}

	}

	// sets turnTracker to the next entity, either a player or piece
	public void nextEntity() {
		GameEntity current = turnTracker;
		current = current.next;
		turnTracker = current;
	}

	// sets turnTracker to the previous player
	public void prevPlayer() {
		GameEntity current = turnTracker;
		current = current.prev;
		while (true) {

			if (current instanceof GamePlayer) {
				turnTracker = current;
				return;
			}
			current = current.prev;
		}
	}

	// constructs the toString representation of the turnTracker
	public String currentEntityToString() {
		StringBuilder sb = new StringBuilder();
		sb.append("Tracker Current is: ");
		GameEntity currentTurn = turnTracker;
		sb.append(currentTurn);

		return sb.toString();
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		/*
		 * // test game! MultiplayerGame g = new MultiplayerGame(3); g.addGamePiece(0,
		 * "ZEROTH PIECE", 1); g.addGamePiece(0, "FIRST PIECE", 2); g.addGamePiece(1,
		 * "SECOND PIECE", 2); g.addGamePiece(1, "THIRD PIECE", 2);
		 * 
		 * g.increaseStrength(0, -1); System.out.println(g.toString());
		 * g.initializeTurnTracker(); System.out.println(g.currentEntityToString());
		 * g.prevPlayer(); System.out.println(g.currentEntityToString());
		 * g.prevPlayer(); System.out.println(g.currentEntityToString());
		 * g.nextEntity(); System.out.println(g.currentEntityToString());
		 * System.out.println(g.turnTracker); //
		 * System.out.println(index[index.length-1]);
		 * 
		 * /* g.removeGamePiece(1, "SECOND PIECE"); g.removeGamePiece(1, "THIRD PIECE");
		 * g.removeGamePiece(0, "ZEROTH PIECE"); g.removeGamePiece(0, "FIRST PIECE");
		 */
		// g.removeGamePiece(1, "ZEROTH PIECE");

		// System.out.println(index.length);
		// System.out.println(index[0].next.next);

		// System.out.println(index.length);
		/*
		 * System.out.println(g.toString()); System.out.println(index[0].next);
		 * System.out.println(index[0].next.next);
		 * System.out.println(index[0].next.next.next);
		 * System.out.println(index[5].next); System.out.println(index[0].prev);
		 */

		// System.out.println(index[0].next);
		// System.out.println(index[0].next.next);
		// System.out.println(g.hasGamePiece("FIRST PIECE"));
		// System.out.println(index[0]);
		// System.out.println(index[1]);
		// System.out.println(index[0].prev);
		// System.out.println(index[0].next);
		// System.out.println(g.size());
		// System.out.println(index[0].next instanceof GamePiece);

		// System.out.println(index[1].next);
		// System.out.println(index[1].prev);
		// System.out.println(index[2].next);

	}
}