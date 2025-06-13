#include <stdio.h>
#include <stdlib.h>

// Matthew McCaughan
// Computer Archicture pa1 second
// February 9th
// Ordered Linked List (10pts)

/*
PROGRESS NOTES:
FUNCTIONALLY COMPLETE
test edge cases?
*/

/* CODE */

// Typedef of Node 
typedef struct Node Node;
// Node!
struct Node {
    Node *next; // Pointer to the next Node
    int data;   // Value at Node
};

// global head node for beginning of the list!
Node *head = NULL;

// prints the list by iterating through it, starting with the head
void printList(){
    Node *current = head;
    //printf("%d ", current->data);

    while (current != NULL){
        printf("%d " , current->data);
        current = current->next;
    }
    printf("\n");
    return;

}


// insert the node into the linked list (given data to insert)
void insertNode(int data) {
    // allocate memory for the new node
    Node *toInsert = malloc(sizeof(Node));
    if (toInsert == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    // initialize the node to insert
    toInsert->data = data;
    toInsert->next = NULL;

    // new node equals head? skip!
    if (head != NULL){
    if (head->data == data){
        free(toInsert);
        return;
    }
    }

    // check if the list is empty or if the new data is smaller than the current head
    if (head == NULL || data < head->data) {
        // new node becomes the new head
        toInsert->next = head;
        head = toInsert;
        return;
    }

    // traverse the list to find the correct position for insertion
    Node *current = head;
    while (current->next != NULL && data > current->next->data) {
        current = current->next;
    }

    // check for duplicate value
    if (current->next != NULL && data == current->next->data) {
        free(toInsert);
        return;
    }

    // Insert the new node after the current node
    toInsert->next = current->next;
    current->next = toInsert;
}






/*
        while (data > current->next->data || current->next != NULL) 
        { 

            prev = current;
            printf("prev in while loop is %d\n", prev->data);
            current = current->next;
        }
          
            */

            /*current problem, current.next is null if inserting at the end of the linked list
            will throw an error */
            /*
            prev = current;
            printf("prev in while loop is %d\n", prev->data);
            printf("head in while loop is %d\n", head->data);
            current = current->next;
            //printf("current in while loop is %d\n", current->data);
        }   
            toInsert = malloc(sizeof(Node));
            toInsert-> data = data;

            printf("current data = %d\n", current->data);
            prev = current;
            current = current->next;
            current = toInsert;
            printf("toInsert = %d\n", current->data);
            printf("prev = %d\n", prev->data);
            current->next = prev->next;
            prev->next = current;
            printf("head data %d\n", head->data);
            printf("prev data %d\n", prev->data);
            printf("current data %d\n", current->data);




            
            //printf("current DATA IS %d ",current->data);
            //printf("prev data is %d", prev->data);

            current = toInsert;
            //current->next = prev->next;
            //prev->next = current;
            //free(toInsert);
            */
        
// opposite of insert (duh), deletes the node with the data given
void deleteNode(int data){
    Node *current = head;
    Node *prev = NULL;
    // nothing even in the head? List is empty!
    if (head == NULL){
        printf("EMPTY");
        return;
    }
    // looking at the head for edge cases
    if (head->data == data){

        head = head->next;
        free(current);
        // is it now empty after unassigning head?
        if (head == NULL)
        {
            printf("EMPTY");
        }
        return;
    }
    // iterate through linked list to find value to delete
    while(current->data != data && current->next != NULL){
        prev = current;
        current = current->next;
    }
    // ignore! (as per output instructions)
    if (current->next == NULL){
        //printf("node not found\n");
        //printf("end of list is %d\n", current->data);
    }
    // found it!
    if(current->data == data){
        //printf("node FOUND\n");
        // set previous node to point towards next node
        prev->next = current->next;
        free(current);

    }



}

int main (int argc, char** argv){

     // file time!
    FILE* fp = fopen(argv[1], "r");
     if(fp == NULL){
        printf("unable to open input file\n");
        exit(EXIT_SUCCESS);
    }

     
    

    // c is getCharacter method from file
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
    //printf("The file has %d lines\n", lines);

    // return file pointer to beginning with SEEK_SET
    fseek(fp, 0, SEEK_SET);

    // dont forget the terminator!
    char instruction[7];
    int value = 0;

    /*Main iterating FOR loop*/
    for (int i = 0; i < lines; i++){
    fscanf(fp,"%s %d\n", instruction, &value);
    //printf("%s %d\n", instruction, value);

    //inserting node
    if (instruction[0] == 'I') {
        //printf("Inserting!\n");
        insertNode(value);
        printList();

    }
    // deleting node
    else if (instruction[0] == 'D'){
        //printf("Deleting!\n");
        deleteNode(value);
        printList();

    }
    //printf("%c", instruction[0]);
    }
// close the file (finally!)
fclose(fp);

}