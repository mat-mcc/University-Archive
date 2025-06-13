#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>




// Initializes 3D array Cache (cache[i][j][k])
int*** initCache(int cacheSize, int setSize, int blockSize) {
    int numSets = cacheSize / (setSize * blockSize);
    int*** c = malloc(sizeof(int**)*numSets);
    for (int i = 0; i < numSets; i++) {
        c[i] = malloc(sizeof(int*)*setSize);

        for (int j = 0; j < setSize; j++) {
            // malloc, but for all zeros!
            c[i][j] = calloc(3, sizeof(int));
        }
    }

    return c;
}


int memRead = 0;
int memWrite = 0;
int cacheHit = 0;
int cacheMiss = 0;

void FIFO(int*** cache, int cacheSize, int setSize, int blockSize, long address, int currentTime) {
    // nightmarish bitwise operations ;(
    int bL = log2(blockSize);
    int sL = log2(cacheSize / (setSize * blockSize));
    long tag = address >> (bL + sL);
    long setIndex = (address >> bL) & ((1 << sL) - 1);

    // hit check!
    int hit = 0;
    for (int i = 0; i < setSize; i++) {
            // if tag matches AND valid bit is 1:
        if (cache[setIndex][i][1] == tag && cache[setIndex][i][0] == 1) {
            hit = 1;
            break;
        }
    }

    // hit?
    if (hit) {
        cacheHit++;
    } else {
        cacheMiss++;
        memRead++;

        // FIFO replacement(check for first line available)
        // first as in placed first!!! not actual first line!
        // no wonder first iteration wasn't working
        int replaceIndex = 0;
        for (int i = 1; i < setSize; i++) {
            if (cache[setIndex][i][2] < cache[setIndex][replaceIndex][2]) {
                replaceIndex = i;
            }
        }

        // Replace line
        cache[setIndex][replaceIndex][0] = 1;
        cache[setIndex][replaceIndex][1] = tag;
        cache[setIndex][replaceIndex][2] = currentTime;
    }
}

void LRU(int*** cache, int cacheSize, int setSize, int blockSize, long address, int currentTime) {
    // more nightmarish bitwise operations!
    int bL = log2(blockSize);
    int sL = log2(cacheSize / (setSize * blockSize));
    long tag = address >> (bL + sL);
    long setIndex = (address >> bL) & ((1 << sL) - 1);

    // hit check part 2!
    int hit = 0;
    int hitIndex = -1;
    for (int i = 0; i < setSize; i++) {
        if (cache[setIndex][i][1] == tag && cache[setIndex][i][0] == 1) {
            hit = 1;
            hitIndex = i;
            break;
        }
    }

    // hit?
    if (hit) {
        cacheHit++;
        // increment age of each line time
        for (int i = 0; i < setSize; i++) {
            if (i != hitIndex && cache[setIndex][i][2] < cache[setIndex][hitIndex][2]) {
                cache[setIndex][i][2]++;
            }
        }
        cache[setIndex][hitIndex][2] = 0; // Reset access time for the hit line
        // no hit!
    } else {
        cacheMiss++;
        memRead++;

        // replace with LRU
        int replaceIndex = 0;
        for (int i = 1; i < setSize; i++) {
            if (cache[setIndex][i][2] > cache[setIndex][replaceIndex][2]) {
                replaceIndex = i;
            }
        }

        // Replace line
        cache[setIndex][replaceIndex][0] = 1;
        cache[setIndex][replaceIndex][1] = tag;
        // increment time for every line!
        for (int i = 0; i < setSize; i++) {
            if (i != replaceIndex) {
                cache[setIndex][i][2]++;
            }
        }
        cache[setIndex][replaceIndex][2] = 0; // Reset access time for the replaced line
    }
}

int main(int argc, char** argv) {
    if (argc != 6) {
        printf("Usage: ./first <cachesize> <assoc:n> <cache policy> <block size> <trace file>\n");
        return -1;
    }

    int cacheSize = atoi(argv[1]);
    char* assoc = strchr(argv[2], ':');
    int setSize = atoi(assoc + 1);
    char* policy = argv[3];
    int blockSize = atoi(argv[4]);

    // cache time!
    int*** cache = initCache(cacheSize, setSize, blockSize);
    int currentTime = 0;

    // let me in please!
    FILE* traceFilePointer = fopen(argv[5], "r");
    if (traceFilePointer == NULL) {
        printf("Unable to open trace file\n");
        return -1;
    }

    char address[18];
    char instruction[3];
    // main while loop for every line
    while (fscanf(traceFilePointer, "%s %s", instruction, address) != EOF) {
        long hexvalue = strtol(address, NULL, 0);
        currentTime++; // Increment time for each instruction
        if (strcmp(policy, "fifo") == 0) {
            FIFO(cache, cacheSize, setSize, blockSize, hexvalue, currentTime);
        } else if (strcmp(policy, "lru") == 0) {
            LRU(cache, cacheSize, setSize, blockSize, hexvalue, currentTime);
        } else {
            printf("Invalid cache policy\n");
            exit(EXIT_FAILURE);
        }
        if (instruction[0] == 'W'){
            memWrite++;
        }
    }

    printf("memread:%d\n", memRead);
    printf("memwrite:%d\n", memWrite);
    printf("cachehit:%d\n", cacheHit);
    printf("cachemiss:%d\n", cacheMiss);

    // goodbye cache!
    for (int i = 0; i < cacheSize / (setSize * blockSize); i++) {
        for (int j = 0; j < setSize; j++) {
            free(cache[i][j]);
        }
        free(cache[i]);
    }
    free(cache);

    return 0;
}



/*
void printCache(int ***c, int numSets) {
    int i;
    for (i = 0; i < numSets; i++) {
        printf("%d: %d, %d, %d\n",i,c[i][0][0], c[i][0][1], c[i][0][2]);
    }
}

int searchAddress(int*** c, int setIndex, int tag, int assoc) {
    for (int a = 0; a < assoc; a++) {
        if (c[setIndex][a][0] == 1 && c[setIndex][a][1] == tag) {
            printf("found at:\n block %d\n matching tag %d\n index: %d\n", a, c[setIndex][a][1], setIndex);
            return 1;
        }
    }
    printf("not found\n");
    return 0;
}


void storeAddress(int*** c, int setIndex, int tag, int assoc, int numSets, char* policy){
    int available = 0;
    int availableLine = 0;
    for (int a = 0; a < assoc; a++){
        if (c[setIndex][a][0] == 0 && c[setIndex][a][1] == 0){
            printf("can store at block %d of set %d\n", a, setIndex);
            available = 1;
            availableLine = a;
            break;
        }
    }
    if (available){
        printf("stored at block %d of set %d\n", availableLine, setIndex);
        c[setIndex][availableLine][0] = 1;
        c[setIndex][availableLine][1] = tag;
        c[setIndex][availableLine][2] = 0;

    } else {
        if (strcmp(policy, "fifo") == 0){
            printf("fifo\n");
            printf("replacing tag %d with %d\n", c[setIndex][0][1], tag);
            c[setIndex][0][0] = 1;
            c[setIndex][0][1] = tag;
            c[setIndex][0][2] = 0;
        }
        if (strcmp(policy, "lru") == 0){
        printf("lru\n");
            int max = 0;
            int index = 0;
        for (int a = 0; a < assoc; a++){
            int current = c[setIndex][a][2];
            if (current > max){
                max = current;
                index = a;
            }
        }
        c[setIndex][index][0] = 1;
        c[setIndex][index][1] = tag;
        c[setIndex][index][2] = 0;
        }
    }



}



int main(int argc, char** argv){
    if (argc != 6){
        printf("Usage: ./first <cachesize> <assoc:n> <cache policy> <block size> <trace file>\n");
    }

    int cacheSize = atoi(argv[1]);
    char* as = argv[2];
    int assoc = atoi(as+6);
    char* policy = argv[3];
    int blockSize = atoi(argv[4]);

    int numBlocks = cacheSize/blockSize;
    int numSets = numBlocks/assoc;
    int blocksPerSet = numBlocks/numSets;
 
    long bL = log2(blockSize);
    long sL = log2(numSets)+1;


    printf("%d\n", cacheSize);
    printf("Assoc: %d\n", assoc);
    printf("Policy: %s\n", policy);
    printf("Blocksize: %d\n", blockSize);
    printf("# sets: %d\n", numSets);
    printf("# blocks: %d\n", numBlocks);
    printf("Blocks per Set: %d\n", blocksPerSet);
    printf("Bits for block: %ld  Bits for set Index: %ld\n", bL,sL);

   FILE* traceFilePointer = fopen(argv[5], "r");
    if(traceFilePointer == NULL){
        printf("Unable to open trace file\n");
        exit(EXIT_SUCCESS);
    }

    char address[18];
    char instruction[3];

    int*** c = malloc(sizeof(int**)*numSets);
        for (int i = 0; i < numSets; i++){
        c[i] = malloc(sizeof(int*)*assoc);
        }
    for (int i = 0; i < numSets; i++){
            for (int j = 0; j < blocksPerSet; j++){
                c[i][j] = malloc(sizeof(long)*3);
                c[i][j][0] = 0; // valid bit
                c[i][j][1] = 0; // tag
                c[i][j][1] = 0; // time since last access?
        }
    }

    int memRead = 0;
    int memWrite = 0;
    int cacheHit = 0;
    int cacheMiss = 0;

    while (fscanf(traceFilePointer,"%s %s",instruction,address) != EOF){
        long int hexvalue = strtol(address,NULL,0);
        //printf("%ld\n", hexvalue);
        printf("%s %ld\n", instruction,hexvalue);

        // nightmarish bitwise logic!
        long blockOffset = hexvalue & ((1<<(bL))-1);
        long setIndex = (hexvalue & ((1<<(bL+sL)))) >> (sL);
        long tag = hexvalue >> (bL+sL);
        printf("blockOffset: %ld setIndex: %ld Tag: %ld\n", blockOffset,setIndex,tag);
        int search = searchAddress(c, setIndex, tag, assoc);

        if (search == 1){
            cacheHit++;
                        printf("cacheHit+\n");

            if (instruction[0] == 'W'){
            
            memWrite++;
            printf("memWrite+\n");
                                //printCache(c, numSets);
      }  
        } else if (search == 0) {
            cacheMiss++;
                                    printf("cacheMiss+\n");

            memRead++;
                                    printf("memRead+\n");

            //store 
            storeAddress(c,setIndex,tag,assoc,numSets, policy);
            if (instruction[0] == 'W'){
            memWrite++;
                        printf("memWrite+\n");

            }  
        }

     // update time since last usage
      for (int i = 0; i < numSets; i++){
            for (int j = 0; j < blocksPerSet; j++){
                if (c[i][j][0] != 0 && c[i][j][1] != 0){
                c[i][j][2]++;
                }
            }
      }       
            printf("\n");

      }  

printf("memread: %d\n", memRead);
printf("memwrite: %d\n", memWrite);
printf("cachehit: %d\n", cacheHit);
printf("cachemiss: %d\n", cacheMiss);
    


    // freeing!
    for (int i = 0; i < numSets; i++){
        for (int j = 0; j < blocksPerSet; j++){
            free(c[i][j]);
        }
        free(c[i]);
    }
    free(c);

    return 5;
}

// ./first 512 assoc:1 fifo 16 trace.txt
*/