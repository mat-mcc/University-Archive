#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct Vertex Vertex;
struct Vertex {
    char name[80];
    int traversed;
    //int weight // for edges with weights
    struct Vertex* next;


};
typedef struct AdjacencyList AdjacencyList;
struct AdjacencyList {
    struct Vertex* head;
};


typedef struct Graph Graph;
struct Graph {
    struct AdjacencyList* alistArray;
};


// Queue time for BST!

typedef struct Node Node;

struct Node {
    Vertex* v;
    struct Node* next;
};

typedef struct Queue Queue;

struct Queue {
    Node* head;
    Node* tail;

};

void Enqueue(Queue* q, Vertex* v) {
    // create nnode to represent vertex in queue
    Node* toEnqueue = malloc(sizeof(Node));
    toEnqueue->v = v;
    toEnqueue->next = NULL;
    // adding first element?
    if (q->tail == NULL) {
        q->head = q->tail = toEnqueue;
        // append to end of queue
    } else {
        q->tail->next = toEnqueue;
        q->tail = toEnqueue;
    }
}

Vertex* Dequeue(Queue* q){
    if (q->head == NULL){
        return NULL;
    }
    // get the head of queue and
    //make vertex the front's vertex
    Node* toDequeue = q->head;
    Vertex* v = toDequeue->v;
    // move front of queue to next element
    q->head = q->head->next;
    if (q->head == NULL){
        q->tail = NULL;
    }
    // node not needed anymore
    free(toDequeue);
    return v;
}


void addUndirectedEdge(Graph* graph, Vertex* source, Vertex* dest, int numVertices) {
    // add dest v to source adjList
    for (int i = 0; i < numVertices; i++) {
        if (strcmp(graph->alistArray[i].head->name, source->name) == 0) {
            Vertex* prevDest = NULL;
            Vertex* currentDest = graph->alistArray[i].head->next;

            // lexicographic order
            while (currentDest != NULL && strcmp(currentDest->name, dest->name) < 0) {
                prevDest = currentDest;
                currentDest = currentDest->next;
            }

            // insert
            Vertex* newDest = malloc(sizeof(Vertex));
            newDest->traversed = 0;
            strcpy(newDest->name, dest->name);
            newDest->next = currentDest;

            if (prevDest == NULL) {
                graph->alistArray[i].head->next = newDest;
            } else {
                prevDest->next = newDest;
            }
            break;
        }
    }

    // add source v to dest adjList
    for (int i = 0; i < numVertices; i++) {
        if (strcmp(graph->alistArray[i].head->name, dest->name) == 0) {
            Vertex* prevSource = NULL;
            Vertex* currentSource = graph->alistArray[i].head->next;

            // lexicographic order of linked list
            while (currentSource != NULL && strcmp(currentSource->name, source->name) < 0) {
                prevSource = currentSource;
                currentSource = currentSource->next;
            }

            // insert
            Vertex* newSource = malloc(sizeof(Vertex));
            newSource->traversed = 0;
            strcpy(newSource->name, source->name);
            newSource->next = currentSource;
            if (prevSource == NULL) {
                graph->alistArray[i].head->next = newSource;
            } else {
                prevSource->next = newSource;
            }
            break;
        }
    }
}


// help funciton for bubblesort
void swap(AdjacencyList* a, AdjacencyList* b) {
    AdjacencyList temp = *a;
    *a = *b;
    *b = temp;
}
// Bubble sort for sorting the adjList lexicographically (classic)
// scary O(n^2)!!!
void bubbleSort(AdjacencyList* a, int numVertices) {
    for (int i = 0; i < numVertices - 1; i++) {
        for (int j = 0; j < numVertices - i - 1; j++) {
            if (strcmp(a[j].head->name, a[j + 1].head->name) > 0) {
                swap(&a[j], &a[j + 1]);
            }
        }
    }
}
// finds the vertex index of the vertices in the graph (ArrayList)
// use to enqueue the actual vertex in adjList rather than the adj vertex in linked list
// lots of words
int findVertexIndex(Graph* a, char* name, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        if (strcmp(a->alistArray[i].head->name, name) == 0) {
            return i;
        }
    }
    return -1;
}


void BreadthFirstSearch(Graph* a, Queue* q, int numVertices, char* name) {
    // travsersed isn't working out, lets mirror the vertices with a boolean list
    // um maybe no variably sized arrays
    // hopefully no more than 10K nodes to track
    bool visitationRights[10000];
    for (int i = 0; i < numVertices; i++) {
        visitationRights[i] = false;
    }

    // enqueue starting vertex
    for (int i = 0; i < numVertices; i++) {
        if (strcmp(a->alistArray[i].head->name, name) == 0) {
            Enqueue(q, a->alistArray[i].head); // enqueue head of adj list
            visitationRights[i] = true;
            break;
        }
    }

    // Now we do BFS!
    while (q->head != NULL) {
        Vertex* current = Dequeue(q);
        printf("%s ", current->name);

        // traverse adjList
        for (int i = 0; i < numVertices; i++) {
            if (strcmp(a->alistArray[i].head->name, current->name) == 0) {
                Vertex* adj = a->alistArray[i].head->next; // skip the head
                while (adj != NULL) {
                    // enqueue adj

                    // TODO add findVertexIndex function!

                    int index = findVertexIndex(a, adj->name, numVertices); 
                    if (!visitationRights[index]) {
                        Enqueue(q, adj);
                        visitationRights[index] = true; 
                        //printf("Enqueued adjacent vertex of %s: %s\n", current->name, adj->name);
                    }
                    adj = adj->next; // next!
                }
                break;
            }
        }
    }
}





int main(int agrc, char** argv){
    // firstly
    FILE* fp = fopen(argv[1], "r");

    if(fp == NULL){
        printf("unabe to open input file\n");
        exit(EXIT_SUCCESS);
    }


    // NUMBER VERTICES
    int numVertices;
    fscanf(fp,"%d\n", &numVertices);
    //printf("num vertices: %d\n", numVertices);

    // initialize Graph
    Graph* a = malloc(sizeof(Graph));
    a->alistArray = malloc(numVertices*sizeof(AdjacencyList));
    
    // initialize graph vertices
    char vertexName[80];
    for (int i = 0; i < numVertices; i++){
        fscanf(fp,"%s\n", vertexName);
        //printf("%s\n", vertexName);
        // allocate each vertex as head
        a->alistArray[i].head = malloc(sizeof(Vertex));
        a->alistArray[i].head->traversed = 0;

        // assign its name and next (vertex structure);
        strcpy(a->alistArray[i].head->name, vertexName);
        a->alistArray[i].head->next = NULL;

    }
    // SORT VERTICES
    bubbleSort(a->alistArray, numVertices);
    /*
    for (int i = 0; i < numVertices; i++){
        printf("%s\n", a->alistArray[i].head->name);
    }
    */

    int Position = ftell(fp);
    //GET EDGES
    // l is getCharacter method from file
    int l = getc(fp);
    // calculates number of lines based on number of newline characters
    int lines = 1;
    // EOF = end of file indicator
    while (l != EOF){
        if (l == '\n'){
            lines += 1;
        }
        l = getc(fp);  
    }
    lines -= 1;
    //printf("num lines: " "%d\n", lines);
    fseek(fp, Position, SEEK_SET); 

    char source[80];
    char dest[80];
    // iterate to add all edges
    for (int i = 0; i < lines; i++){
        fscanf(fp,"%s %s\n", source, dest);
        //printf("%s %s\n", source, dest);
        Vertex* s = malloc(sizeof(Vertex));
        Vertex* d = malloc(sizeof(Vertex));
        strcpy(s->name,source);
        strcpy(d->name,dest);
        s->next = NULL;
        d->next = NULL;
        addUndirectedEdge(a,s,d,numVertices);
        free(s);
        free(d);
    }

//printf("%s\n", a->alistArray[0].head->name);
for (int i = 0; i < numVertices; i++) {
Vertex* current = a->alistArray[i].head; // start from head
while (current != NULL) {
    //printf("%s\n", current->name);
    current = current->next;
}
//printf("\n");
}fseek(fp, 0, SEEK_SET); 
    fclose(fp);


    // open up query
    FILE* fp1 = fopen(argv[2], "r");
     if(fp1 == NULL){
        printf("unable to open second input file\n");
        exit(EXIT_SUCCESS);
    }


    //GET EDGES
    // l is getCharacter method from file
    int l1 = getc(fp1);
    // calculates number of lines based on number of newline characters
    int lines1 = 1;
    // EOF = end of file indicator
    while (l1 != EOF){
        if (l1 == '\n'){
            lines1 += 1;
        }
        l1 = getc(fp1);  
    }
    lines1 -= 1;
    //printf("num lines: " "%d\n", lines1);


    //INITIALIZE QUEUE
    Queue* q = malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;

    // read second file
    char vert[80];

    fseek(fp1, 0,SEEK_SET); 
    for (int i = 0; i < lines1; i++){
    fscanf(fp1,"%s\n", vert);
    //printf("%s\n", vert);
    BreadthFirstSearch(a,q,numVertices, vert);
    printf("\n");
    /*
    //

    if (strcmp(ins, "d") == 0){
        //printf("ding!\n");
        Degree(a, vert, numVertices);

    }
    if (strcmp(ins, "a") == 0){
        //printf("aing!\n");
        Adjacenct(a, vert, numVertices);

    }
    */
    }





   //freeGraph(a,numVertices);
    //freeing!


while (q->tail != NULL) {
        Vertex* v = Dequeue(q);
        free(v);
        
    }
    free(q);

for (int i = 0; i < numVertices; i++) {
    Vertex* current = a->alistArray[i].head;
        while (current != NULL) {
            Vertex* nextVertex = current->next; 
            free(current); 
            current = nextVertex; 
        }
    a->alistArray[i].head = NULL; 
    }
    free(a->alistArray);
    free(a);



    return 0;
}

