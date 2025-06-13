#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Matthew McCaughan
// Computer Archicture pa1 fourth
// February 9th
// BST (10pts)

/*
PROGRESS NOTES:
Done!
*/

/* CODE */

// Typedef of Node 
typedef struct Node Node;
// Node!
struct Node {
    Node *left; // Pointer to the left child
    Node *right; // Pointer to the right child
    int key;   // Value at Node
};

Node *root = NULL;

void insertNode(int key) {
    int height = 1;
    Node *current = root;
    Node *parent = NULL; // Keep track of the parent node for insertion

    // Create the new node
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("malloc failure!\n");
        return;
    }
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;

    // root is empty, insert as the root!
    if (root == NULL) {
        root = newNode;
        printf("inserted %d\n", height);
        return;
    }

    // Traverse the tree 
    while (current != NULL) {
        // Update parent
        parent = current; 

        // go to left child!
        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            // go to right child!
            current = current->right;
        } else {
            // already in the tree!
            printf("duplicate\n");
            // no memory leaks please!
            free(newNode); 
            return;
        }
        height++;
    }

    // Insert the new node!
    if (key < parent->key) {
        parent->left = newNode;
        printf("inserted %d\n", height);
        return;
    } else {
        parent->right = newNode;
        printf("inserted %d\n", height);
        return;
    }
}

// recursion time!!
// takes the key, the current node (starting with root), and height of node (starting with 1)

void searchNode(int key, Node *current, int height){
    if (current == NULL){
        printf("absent\n");
        return;
    }
   
   if (current->key == key){
    printf("present %d\n", height);
    return;
   }
   if (current->key < key){
    searchNode(key, current->right, height + 1);
    return;
   }
   if (current->key > key){
    searchNode(key, current->left, height + 1);
    return;
   }
}



int main (int argc, char** argv){
    FILE* fp = fopen(argv[1], "r");
     if(fp == NULL){
        printf("unable to open input file\n");
        exit(EXIT_SUCCESS);
    }

    // l is getCharacter method from file
    int l = getc(fp);
    // calculates number of lines based on number of newline characters
    // we need this since we arent given the number of instructions to run (lame!)
    // but i want to be able to iterate through them by line and stop on the last instruction
    int lines = 1;
    // EOF = end of file indicator
    while (l != EOF){
        if (l == '\n'){
            lines += 1;
        }
        l = getc(fp);  
    }
    lines -= 1;
    //printf("The file has %d lines\n", lines);

    // return file pointer to beginning with SEEK_SET
    fseek(fp, 0, SEEK_SET);

    char instruction[2];
    int value = 0;

    /*Main iterating FOR loop*/
    for (int i = 0; i < lines; i++){
    fscanf(fp,"%c %d\n", instruction, &value);
    //printf("%c %d\n", instruction[0], value);
    
    //printf("%c\n", instruction[0]);
    if (instruction[0] == 'i'){
        //printf("Inserting!\n");
        insertNode(value);
        //printf("%d\n", root->key);



    }


    if (instruction[0] == 's'){
        //printf("searching!\n");
        searchNode(value,root,1);

    }
    }
    //printf("returning!\n");

    return 0;
}
