/*
 * ASSIGNMENT FOUR
 * 
 * MATTHEW MCCAUGHAN
 * APRIL 8TH 2022
 */

import java.util.Random;
import java.util.Stack;

public class Treap<E extends Comparable<E>> {
	
	
	private static class Node<E>{
		
	public E data;
	public int priority;
	public Node<E> left;
	public Node<E> right;
		
		public Node(E data, int priority) {
			
			if (data == null) {
				throw new IllegalArgumentException();
			}
			
			
			this.data = data;
			this.priority = priority;
			left = null;
			right = null;
		}
		
		
		// helper toString for when Tree toString calls on Node toString to represent a node
		public String toString() {
			return "[KEY: " + data + " PRIORITY: " + priority + "]";
		}
		
		// right rotation, returns reference to the new root
		Node<E> rotateRight(){
			
			Node<E> oldRoot = this; // gotta grab the node!
			Node<E> newRoot = oldRoot.left; // gets left child to be the new "root"
			Node<E> switcher = oldRoot.left.right; // get the node to bring to left side
			oldRoot.left = switcher; // attches swither as a child 
			newRoot.right = oldRoot; // sets new root as newRoot, and makes the oldRoot the right child of the new root
			return newRoot;
			
			
			
		}
		// left rotation, returns reference to the new root
		Node<E> rotateLeft(){
			
			Node<E> oldRoot = this; // gotta grab the node!
			Node<E> newRoot = oldRoot.right;  // gets right child to be new "root"
			Node<E> switcher = oldRoot.right.left; // gets the node to bring to the right side
			oldRoot.right = switcher; // attaches switcher as a child of the old root
			newRoot.left = oldRoot; // sets new root as newRoot, and makes the oldRoot the left child of the new root
			return newRoot;
			
			
		}
		
	}

	// TREAP CLASS:
	
	// DATA
	
	private Random priorityGenerator;
	
	private Node<E> root;
	// E is comparable (E extends Comparable<E>>)
	
	
	
	// CONSTRUCTORS
	
	
	// Empty Treap, random priority
	public Treap() {
		root = null;
		priorityGenerator = new Random();
		
	}
	
	// Empty Treap, priority given by seed
	public Treap(long seed) {
		root = null;
		priorityGenerator = new Random(seed);
		
	}
	
	
	
	// WRAPPER ADD FUNCTION: adds node with key and random number between 0 and 100
	boolean add(E key) {
		int generatedNumber = priorityGenerator.nextInt(101);
		int[] numList = new int[100];
		
		
		// intiial check if the value already exists within the list (a node already exists with this priority)
		for (int i = 0; i < numList.length; i++) {
			if (numList[i] == generatedNumber) {
				return false;
			}
		}

		// shifts all other elements to the right once to occomodate new value to check
		for (int i = numList.length; i <= 0 ; i--) {
			numList[i+1] = numList[i];
		}
		
		// adds priority to existing list of priorities to check
		numList[0] = generatedNumber;
		

		return add(key, generatedNumber);
		
		
	}
	
	// adds a node given a key and a priority to the tree, then calls on reheap to ensure tree is heaped correctly
	boolean add(E key, int priority) {
		
		// IF KEY ALREADY EXISTS RETURN FALSE
		if (find(key) == true) {
			return false;
		}
		
		// makes a new node given the arguments to be added to the tree
		Node<E> newNode = new Node<E>(key, priority);
		
		// initialize the stack to store each node in the path from the root to the spot where it is inserted
		// push will add a node in the path to trace
		// pop/peek will allow for referencing the trace
		Stack<Node<E>> pathTrace = new Stack<Node<E>>();
		
		Node<E> currentRoot = root;
		
		// EMPTY TREE
		if (root == null) {
			root = newNode;
			return true;
		}
		
		else {
			while(currentRoot.left != null || currentRoot.right != null) {
				
				int comparison = key.compareTo(currentRoot.data);
			

				// key of newNode is smaller than current data, so newNode must go to the left
				if(comparison<0) {
					
					// and if the left spot is empty, newNode goes here and breaks
					if (currentRoot.left == null) {
						break;
					}
					
					// adds the currentRoot to the path, iterates to the left child
					pathTrace.push(currentRoot);
					currentRoot=currentRoot.left;
				}
				
				// key of newNode is greater than current data, so newNode must go to the right
				else if(comparison>0) {
					// and if the right spot is empty, newNode goes here and breaks
					if (currentRoot.right == null) {
						break;
					}
					// adds the currentRoot to the path, iterates to the right child
					pathTrace.push(currentRoot);
					currentRoot=currentRoot.right;
				}
				// else case where the data is equal to the key we're adding (cant have duplicate nodes):
				else {
					return false;
				}

			}
			
			// adding newNode to the tree
			int cmpResult = key.compareTo(currentRoot.data);
			
			// newNode key is less than the currentRoot, add to the left
			if(cmpResult<0) {
				currentRoot.left = newNode;
			}
			// newNode key is greater than the currentRoot, add to the left
			else if(cmpResult>0) {
				currentRoot.right = newNode;
			}
			// another case where neither is applicable (duplicate node)
			else {
				return false;
			}
			
			pathTrace.push(currentRoot);
			// reheap time!
			reheap(pathTrace, newNode);
			return true;
		}
		
	}
	// Goes through the pathtrace stack to make sure priorities are maintained through the tree
	public void reheap(Stack<Node<E>> pathTrace, Node<E> newNode) {		
		while(!pathTrace.isEmpty()) {
			
			
			// sets current to the top of the stack, starting with the parent of newNode
			Node<E> current = pathTrace.pop();
			
			
			// case 1: the child node has a higher priority
			if(current.priority < newNode.priority) {
				
				
				
				// key of current is greater than added node
				if(current.data.compareTo(newNode.data) > 0) {
					newNode = current.rotateRight();
				}
				
				// key of current is less than added node
				else {
					newNode = current.rotateLeft();
				}
				// actual node insertion using the stack
				if(!pathTrace.isEmpty()) {
					if (pathTrace.peek().left == current) {
						pathTrace.peek().left = newNode;
					}
					else {
						pathTrace.peek().right = newNode;
					}
				}
				
				
				
				
				else {
					this.root = newNode;
				}
			}
			
			// case 2: child has a lesser priority (correct heap)
			else {
				break;
			}
		}
		
	}

/*
	// Goes through the pathtrace stack to make sure priorities are maintained through the tree
	private void reheap(Stack<Treap.Node<E>> pathTrace, Treap.Node<E> newNode) {
		while(!pathTrace.isEmpty()) {
			
			// sets current to the top of the stack, starting with the parent of newNode
			Node<E> current = pathTrace.pop();
			
			// case 1: the child node has a higher priority
			if(newNode.priority > current.priority) {
				int compare = current.data.compareTo(newNode.data);
				// key of current is greater than added node
				if(compare > 0) {
					newNode = current.rotateRight();
				
				}
				// key of current is less than added node
				else {
					newNode  = current.rotateLeft();
					
				}
				
				if (!pathTrace.isEmpty()) {
					if (pathTrace.peek().left == current) {
						pathTrace.peek().left = current;
					}
					else {
						pathTrace.peek().right = current;
					}
					
				}
				else {
					this.root = newNode;
				}
			}
			
			// case 2: child has a lesser priority (correct heap)
			else {
				break;
			}
		}

		
	}

	*/
	boolean delete(E key) {
		// key has to be in the tree in order to be deleted!
		if (find(key) == false) {
			return false;
		}
		Node<E> deletion = root;
		Node<E> pointerNode = null;
		
		Stack<Node<E>> deleteTrace = new Stack<Node<E>>();
		
		// while loop iterates deletion node to search for the node equal to key
		while(deletion.data != key) {

			pointerNode = deletion;
			deleteTrace.push(pointerNode);
			if(key.compareTo(deletion.data)>0) {
				deletion = deletion.right;
			}
			else {
				deletion = deletion.left;
			}
			
		}
		// at node to be deleted, rotates to ensure that deleted node will be a leaf
		if (deletion.equals(root)) {
			if (deletion.left == null && deletion.right == null) {
				root = null;
				return true;
			}
			else if(deletion.left == null) {
				pointerNode = deletion.rotateLeft();
				root = pointerNode;
			}
			else if (deletion.right == null){
				pointerNode = deletion.rotateRight();
				root = pointerNode;
			}
			else if (deletion.right.priority > deletion.left.priority) {
				pointerNode = deletion.rotateLeft();
				root = pointerNode;
			}
			else {
				pointerNode = deletion.rotateRight();
				root = pointerNode;
			}
			deleteTrace.push(pointerNode);
		}
		while(true) {
			// checks through the treap to ensure heap prirotiies are maintained 
		
			// both children references empty, jumps to removal
			if (deletion.right == null & deletion.left == null) {
				break;
			}
			
			// priority maintenance
			else if (deletion.right == null && deletion.left != null) {
				if(deleteTrace.peek().left != null && deleteTrace.peek().left.equals(deletion)) {
					deleteTrace.peek().left = deletion.left;
				}
				else {
					deleteTrace.peek().right = deletion.left;
				}
				pointerNode = deletion.rotateRight();
				deleteTrace.push(pointerNode);
			}
			else if(deletion.left == null && deletion.right != null){
				if(deleteTrace.peek().left != null && deleteTrace.peek().left.equals(deletion)) {
					deleteTrace.peek().left = deletion.right;
				}
				else {
					deleteTrace.peek().right = deletion.right;
				}
				pointerNode = deletion.rotateLeft();
				deleteTrace.push(pointerNode);
			}
			else if(deletion.right.priority > deletion.left.priority) {
				if(deleteTrace.peek().left != null && deleteTrace.peek().left.equals(deletion)) {
					deleteTrace.peek().left = deletion.right;
				}
				else {
					deleteTrace.peek().right = deletion.right;
				}
				pointerNode = deletion.rotateLeft();
				deleteTrace.push(pointerNode);
			}
			else {
				if(deleteTrace.peek().left != null && deleteTrace.peek().left.equals(deletion)) {
					deleteTrace.peek().left = deletion.left;
				}
				else {
					deleteTrace.peek().right = deletion.left;
				}
				pointerNode = deletion.rotateRight();
				deleteTrace.push(pointerNode);
			}
		}
		// leaf condition, deletes node
		if(pointerNode.left != null && pointerNode.left.equals(deletion)) {
			
			pointerNode.left = null;
		}
		else {
			pointerNode.right = null;
		}
		
		return true;
	}
	
	private boolean find(Node<E> root, E key) {
		
		// tree is empty
		if (root == null) {
			return false;
		}
		
		// compareTo variable
		int cmpResult = root.data.compareTo(key);
		
		// if the data is equal to the key
		if (cmpResult == 0) {
			return true;
		}
		// if the key is greater than the data (must search right)
		if (cmpResult < 0){
			return find(root.right, key);
					
		}
		// if the key is less than the data (must search left)
		else {
			return find(root.left,key);
		}
		
	}
	
	public boolean find(E key) {
		return find(root, key);
		
	}
	
	// wrapper toString method
	public String toString() {
		return toString(root,0);
		
	}
	
	
	// BTree method of toString (from lecture) When representing the current node, calls on helper toString in node class.
	private String toString(Node<E> current, int depth) {
		StringBuilder sb = new StringBuilder();
		for (int i=0; i<depth;i++) {
		sb.append("--");
		}
		if (current==null) {
		sb.append("null\n");
		} else {
		sb.append(current.toString()+"\n");
		sb.append(toString(current.left, depth+1)); //
		sb.append(toString(current.right,depth+1));
		}
		return sb.toString();
		}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		/*
		Treap<Integer> testTree = new Treap<Integer>();
		System.out.println(testTree.add(4,19));
		System.out.println(testTree.add(4,19));
		
		testTree.add(2);
		testTree.add(6);
		testTree.add(1);
		testTree.add(3);
		testTree.add(5);
		testTree.add(7);
		System.out.println(testTree);
		testTree.delete(1);
		System.out.println(testTree);
		*/
		
	}

}
