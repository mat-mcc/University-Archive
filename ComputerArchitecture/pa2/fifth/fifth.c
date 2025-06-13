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
            return i; // Return the index if the vertex is found
        }
    }
    return -1; // Return -1 if the vertex is not found
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
            // recursion!
            DepthFirstSearchHelper(a, numVertices, current->name, visitationRights);
        }
        current = current->next;
    }
}

// goes through all vertices ensuring connected graph
void DepthFirstSearch(Graph* a, int numVertices, bool visitationRights[], char* vertex) {
    // start with vertex we want 
    DepthFirstSearchHelper(a,numVertices,vertex,visitationRights);
    // iterate through all vertices
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
        distance[i] = 1000000000; // this is "infinity" INTMAX was giving me issues
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
    //lines1 -= 1;
    //printf("num lines: " "%d\n", lines1);

    char vert[80];
    bool visitationRights[10000];
    fseek(fp1, 0,SEEK_SET); 

    // MAIN SOLUTION FOR LOOP!
    for (int i = 0; i < lines1; i++){
    fscanf(fp1,"%s\n", vert);
    //printf("%s\n", vert);
    //printf("%s\n", vert);
    
    //printf("depth first search with %s!\n", );
    for (int i = 0; i < sizeof(visitationRights); i++){
        visitationRights[i] = false;
    }
    for (int i = 0; i < 1000; i++){
        distance[i] = 0;
    }
    counter = 0;
    memset(visitedVertices, 0, sizeof(visitedVertices));
    /*
    for (int i =0; i < sizeof(visitedVertices); i ++){
        visitedVertices[i] = "_";
    }
    */
           DepthFirstSearch(a, numVertices, visitationRights, vert);
           for (int i =0; i < numVertices; i++){
            //printf("%s ", visitedVertices[i]);
           }
            //printf("\n");
    if (i == 0){
    printf("\n");
    }
    DAGSSP(a, vert,numVertices);
    printf("\n");
    }

    


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

