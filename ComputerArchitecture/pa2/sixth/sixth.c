#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
typedef struct Vertex Vertex;
struct Vertex {
    char name[80];
    int weight;
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
// min-priority queue structs
typedef struct Node Node;
struct Node {
    int prio;
    char name[80];

};

typedef struct minPrioQueue minPrioQueue;
struct minPrioQueue {
    int size;
    Node* heap[1000000000];
};


void addDirectedEdge(Graph* graph, Vertex* source, Vertex* dest, int numVertices, int weight) {
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
            strcpy(newDest->name, dest->name);
            newDest->next = currentDest;
            newDest->weight = weight;

            if (prevDest == NULL) {
                graph->alistArray[i].head->next = newDest;
            } else {
                prevDest->next = newDest;
            }
            break;
        }
    }
}


void Adjacenct(Graph* graph, char* comp, int numVertices){
    for (int i = 0; i < numVertices; i++) {
        // add dest vertex only to source vertex list
        if (strcmp(graph->alistArray[i].head->name, comp) == 0) {
            Vertex* current = graph->alistArray[i].head->next;
            while (current != NULL){
                printf("%s ", current->name);
                current = current->next;
            }
            printf("\n");

        }
    }

}
void outDegree(Graph* graph, char* comp, int numVertices){
    int sum = 0;
    for (int i = 0; i < numVertices; i++) {
        // add dest vertex only to source vertex list
        if (strcmp(graph->alistArray[i].head->name, comp) == 0) {
            Vertex* current = graph->alistArray[i].head->next;
            while (current != NULL){
                //printf("%s ", current->name);
                current = current->next;
                sum +=1;
            }
            printf("%d\n", sum);

        }
    }

}

void inDegree(Graph* graph, char* comp, int numVertices){
    int sum = 0;
    for (int i = 0; i < numVertices; i++) {
        // add dest vertex only to source vertex list
        if (strcmp(graph->alistArray[i].head->name, comp) != 0) {
            Vertex* current = graph->alistArray[i].head->next;
            while (current != NULL){
                if (strcmp(current->name, comp) == 0){
                //printf("%s ", current->name);
                sum +=1;
                }
                current = current->next;
            }


        }
    }
            printf("%d\n", sum);
}

// help funciton for bubblesort
void swap(AdjacencyList* a, AdjacencyList* b) {
    AdjacencyList temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble sort for sorting vertices lexicographically
void bubbleSort(AdjacencyList adjList[], int numVertices) {
    for (int i = 0; i < numVertices - 1; i++) {
        for (int j = 0; j < numVertices - i - 1; j++) {
            if (strcmp(adjList[j].head->name, adjList[j + 1].head->name) > 0) {
                swap(&adjList[j], &adjList[j + 1]);
            }
        }
    }
}
/*


procedure DFS(G, v) is
    label v as discovered
    for all directed edges from v to w that are in G.adjacentEdges(v) do
        if vertex w is not labeled as discovered then
            recursively call DFS(G, w)
*/
// apparently this isn't a matrix?
// each index has max size of 80 chars and whole array is max 1000 length
char visitedVertices[1000][80];
int counter;
int distance[1000];
bool cycleCheck[1000];


int findVertexIndex(Graph* a, char* name, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        if (strcmp(a->alistArray[i].head->name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// WONT WORK FOR DISCONNECTED GRAPHS
/*
void DepthFirstSearch(Graph* a, int numVertices, char* name, bool visitationRights[]) {
    int ind = 0;

    // Find the index of the starting vertex
    for (int i = 0; i < numVertices; i++) {
        if (strcmp(a->alistArray[i].head->name, name) == 0) {
            visitationRights[i] = true;
            printf("%s marked as visited at index %d\n", a->alistArray[i].head->name, i);
            ind = i;
            break;
        }
    }

    Vertex* current = a->alistArray[ind].head->next;
    //printf("%s\n", current->name);
    
    while (current != NULL) {
        int indexAdj = findVertexIndex(a, current->name, numVertices);
        
        if (visitationRights[indexAdj] == false) {
            // Recursively call DFS for unvisited adjacent vertices
            DepthFirstSearch(a, numVertices, current->name, visitationRights);
        }

        // Move to the next adjacent vertex
        current = current->next;
        //printf("%s\n", current->name);
    }
}
*/
// Iterates through adjList of current vertex and recurively calls them until done with adjList of vertex
void DepthFirstSearchHelper(Graph* a, int numVertices, char* name, bool visitationRights[]) {
    int ind = findVertexIndex(a, name, numVertices);
    visitationRights[ind] = true;
    cycleCheck[ind] = true;
            // already did this node? cycle!
        if (cycleCheck[ind] == true){
            //printf("cycle!");

        }
    strcpy(visitedVertices[counter],name);
    counter = counter +1;
    //printf("%s ", name);

    Vertex* current = a->alistArray[ind].head->next;
    
    while (current != NULL) {
        int indexAdj = findVertexIndex(a, current->name, numVertices);
        
        if (!visitationRights[indexAdj]) {
            // Recursively call DFS for unvisited adjacent vertices
            DepthFirstSearchHelper(a, numVertices, current->name, visitationRights);
        }
        // Move to the next adjacent vertex
        current = current->next;
    }
}

// goes through all vertices ensuring connected graph
void DepthFirstSearch(Graph* a, int numVertices, bool visitationRights[], char* vertex) {
    // start with vertex we want 
    DepthFirstSearchHelper(a,numVertices,vertex,visitationRights);
    for (int i = 0; i < numVertices; i++) {
        if (visitationRights[i]== false) {
            char* name = a->alistArray[i].head->name;
            //printf("Starting DFS from vertex: %s\n", name);
            // dfs on unvisited vertex
            DepthFirstSearchHelper(a, numVertices, name, visitationRights);
        }
    }
}
/*
procedure DAG-SSP(G, src)
    T ← T opologicalSort(G)
    foreach vertex v in Graph G do
        distance[v] ← inf
    end
    distance[src] ← 0
    foreach vertex u in topologically sorted order T do
        foreach vertex v ∈ u.Adjacent do
            if distance[v] > distance[u] + weight(u, v) then
            distance[v] ← distance[u] + weight(u, v)
        end
    end
*/

void DAGSSP(Graph* a, char* name, int numVertices){
    for (int i =0; i < numVertices; i++){
        distance[i] = 1000000000;
    }
    int ind = findVertexIndex(a, name, numVertices);
    distance[ind] = 0;

    for (int i = 0; i< numVertices; i++){
        //printf("%d ", distance[i]);
    }
    //printf("\n");
    for (int z = 0; z < numVertices; z++){

    }
    // iterate vertices through DFS
    for (int uIndex = 0; uIndex < numVertices; uIndex++) {
        // Iterate through the adjacent vertices of u
        Vertex* currentVertex = a->alistArray[uIndex].head->next;
        while (currentVertex != NULL) {
            int vIndex = findVertexIndex(a, currentVertex->name, numVertices);
            // ppdate distance of v if u is a shorter path
            if (distance[vIndex] > distance[uIndex] + currentVertex->weight) {
                distance[vIndex] = distance[uIndex] + currentVertex->weight;
            }
            currentVertex = currentVertex->next;
        }
    }
        // unreachable node!
        for (int i = 0; i < numVertices; i++) {
        if (distance[i] == 1000000000){
            printf("%s INF\n", a->alistArray[i].head->name);
        }
        else 
        printf("%s %d\n", a->alistArray[i].head->name, distance[i]);
    }
}
// swap helper functin for mpq
void swapmpq(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

// add a node with priority to the priority queue
void addWithPriority(minPrioQueue* mpq, char* name, int priority) {
    Node* newNode = malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->prio = priority;

    // add to end of queue
    mpq->heap[mpq->size] = newNode;

    // sort!
    int currentIndex = mpq->size;
    while (currentIndex > 0 && mpq->heap[currentIndex]->prio < mpq->heap[(currentIndex - 1) / 2]->prio) {
        //printf("reheap!");
        swapmpq(mpq->heap[currentIndex], mpq->heap[(currentIndex - 1) / 2]);
        currentIndex = (currentIndex - 1) / 2;
        //printf("currentIndex is %d\n", currentIndex);
    }

    mpq->size++;
}
void decreasePriority(minPrioQueue* mpq, char* name, int newPrio) {
    for (int i = 0; i < mpq->size; i++) {
        if (strcmp(mpq->heap[i]->name, name) == 0) {
            mpq->heap[i]->prio = newPrio;

            // reheap to maintain the min-proirity queue!
            while (i > 0 && mpq->heap[i]->prio < mpq->heap[(i - 1) / 2]->prio) {
                swapmpq(mpq->heap[i], mpq->heap[(i - 1) / 2]);
                i = (i - 1) / 2;
                //printf("i is %d\n", i);
            }
            return;
        }
    }
}
// return the node that is the min extracted
Node* extractMin(minPrioQueue* mpq) {

    Node* minNode = mpq->heap[0];
    // bring min to "front"
    mpq->heap[0] = mpq->heap[mpq->size - 1];
    //printf("heap front: %s", mpq->heap[0]->name);
    mpq->size--;

    /*           -->
    ||  ||  ||  ||  ||  ||  ||  ||
    */

    // more painful iteration of list
    int currentIndex = 0;
    while (true) {
        int aLeft = 2 * currentIndex + 1;
        int aRight = 2 * currentIndex + 2;
        int smallest = currentIndex;

        if (aLeft < mpq->size && mpq->heap[aLeft]->prio < mpq->heap[smallest]->prio) {
            smallest = aLeft;
        }

        if (aRight < mpq->size && mpq->heap[aRight]->prio < mpq->heap[smallest]->prio) {
            smallest = aRight;
        }

        if (smallest != currentIndex) {
            swapmpq(mpq->heap[currentIndex], mpq->heap[smallest]);
            currentIndex = smallest;
        } else {
            break;
        }
    }
    return minNode;
}

/*
1  function Dijkstra(Graph, source):
2      dist[source] ← 0                           // Initialization
3
4      create vertex priority queue Q
5
6      for each vertex v in Graph.Vertices:
7          if v ≠ source
8              dist[v] ← INFINITY                 // Unknown distance from source to v
9              prev[v] ← UNDEFINED                // Predecessor of v
10
11         Q.add_with_priority(v, dist[v])
12
13
14     while Q is not empty:                      // The main loop
15         u ← Q.extract_min()                    // Remove and return best vertex
16         for each neighbor v of u:              // Go through all v neighbors of u
17             alt ← dist[u] + Graph.Edges(u, v)
18             if alt < dist[v]:
19                 dist[v] ← alt
20                 prev[v] ← u
21                 Q.decrease_priority(v, alt)
22
23     return dist, prev
*/



void Dijkstra(Graph* a, char* name, int numVertices, minPrioQueue* mpq) {
    int dist[1000]; // distance array for distances (duh!)

    // initialize!
    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX;
    }

    // distance of source vertex is 0
    int sourceIndex = findVertexIndex(a, name, numVertices);
    dist[sourceIndex] = 0;

    //  Q.add_with_priority(v, dist[v])
    addWithPriority(mpq, name, 0);

    // main loop
    while (mpq->size != 0) {
        // u ← Q.extract_min()  
        Node* minNode = extractMin(mpq);
        int u = findVertexIndex(a, minNode->name, numVertices);
        free(minNode);

        // iterate through adjList of u
        Vertex* currentVertex = a->alistArray[u].head->next;
        while (currentVertex != NULL) {
            int v = findVertexIndex(a, currentVertex->name, numVertices);
            int alt = dist[u] + currentVertex->weight;

            // update distance if a shorter path is found
            if (alt < dist[v]) {
                dist[v] = alt;
                // update priority queue
                decreasePriority(mpq, currentVertex->name, alt);
            }
            currentVertex = currentVertex->next;
        }
    }
    // print the shortest distances (queue should be empty!)
    if (mpq->size != 0){
    for (int i = 0; i < numVertices; i++) {
        if (dist[i] == INT_MAX) {
            printf("%s INF\n", a->alistArray[i].head->name);
        } else {
            printf("%s %d\n", a->alistArray[i].head->name, dist[i]);
        }
    }
    }
    // debug fallback return answer
    //printf("debug answer:\n");
    DAGSSP(a,name,numVertices);
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
        a->alistArray[i].head->weight = -1;

        // assign its name and next (vertex structure);
        strcpy(a->alistArray[i].head->name, vertexName);
        // set weight to value we hopefully wont access
        a->alistArray[i].head->next = NULL;

    }
    // SORT VERTICES
    bubbleSort(a->alistArray, numVertices);
    
    for (int i = 0; i < numVertices; i++){
        //printf("%s\n", a->alistArray[i].head->name);
    }
    

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
    int wt;
    // iterate to add all edges
    for (int i = 0; i < lines; i++){
        fscanf(fp,"%s %s %d\n", source, dest,&wt);
        //printf("%s %s %d\n", source, dest,wt);
        Vertex* s = malloc(sizeof(Vertex));
        Vertex* d = malloc(sizeof(Vertex));
        strcpy(s->name,source);
        strcpy(d->name,dest);
        s->next = NULL;
        d->next = NULL;
        addDirectedEdge(a,s,d,numVertices,wt);
        free(s);
        free(d);
    }

//printf("%s\n", a->alistArray[0].head->name);
for (int i = 0; i < numVertices; i++) {
Vertex* current = a->alistArray[i].head; // start from head
while (current != NULL) {
    //printf("%s\n", current->name);
    //printf("%d\n", current->weight);
    current = current->next;
}
//printf("\n");
    //printf("\n");
}

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

    char vert[80];
    //bool visitationRights[10000];
    fseek(fp1, 0,SEEK_SET); 

    // MAIN SOLUTION FOR LOOP!
    minPrioQueue* mpq = malloc(sizeof(minPrioQueue));
    mpq->size = 0;

    for (int i = 0; i < lines1; i++){
    fscanf(fp1,"%s\n", vert);
    DAGSSP(a,vert,numVertices);
    //Dijkstra(a, vert,numVertices, mpq);
    printf("\n");
    }
    free(mpq);
    /*
    if (strcmp(ins, "a") == 0){
        //printf("aing!\n");
        Adjacenct(a, vert, numVertices);
    }

        if (strcmp(ins, "i") == 0){
        //printf("ding!\n");
        inDegree(a, vert, numVertices);

    }

        if (strcmp(ins, "o") == 0){
        //printf("ding!\n");
        outDegree(a, vert, numVertices);
        }
    }
    */
   //freeGraph(a,numVertices);
    //freeing!
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

