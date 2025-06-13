#include <stdio.h>
#include <stdlib.h>

// Matthew McCaughan
// Computer Archicture pa1 first
// February 9th
// Is the input a Product of 2 or 3 Given Numbers? (5pts)

/*
PROGRESS NOTES:

Functionally complete
WAITING ON AUTOGRADER
*/


int main (int argc, char** argv){
    
    // firstly
    FILE* fp = fopen(argv[1], "r");

    if(fp == NULL){
        printf("unabe to open input file\n");
        exit(EXIT_SUCCESS);
    }
    // how long is the array?
    int arrayLength;
    fscanf(fp,"%d\n", &arrayLength);


    //printf("Array is %d ints long\n", arrayLength);

    // scary!
    int* numsArray = malloc(arrayLength*sizeof(int));

    //printf("Contains:\n");

    //
    for (int i =0; i < arrayLength; i++){
        fscanf(fp,"%d", &numsArray[i]);
        //printf("%d ", numsArray[i]);
    }
    //printf("\n");

        //grab number of Queries
    int inputsQueried = 0;
    fscanf(fp,"\n %d \n", &inputsQueried);
    //printf("%d Queries tested:\n", inputsQueried);

        // grab the things we're testing
    for (int j = 0; j < inputsQueried; j++){
        int product = 0;
        int combo = 0;
        fscanf(fp, "%d %d", &product, &combo);
        //printf("%d %d \n", product, combo);

        // actual algorithm time
        // iterates through list combo times to check every combination of nums
        // yes? result will be 1 else result is 0
        int result = -1;

        // product of 2 nums
        if (combo == 2){

            for (int a = 0; a < arrayLength; a++){
                for (int b = 1; b < arrayLength; b++){
                    if (numsArray[a]*numsArray[b] == product){
                        result = 1;
                        break;
                    } else {
                        continue;

                    }

                }
            }
            if (result == 1){
                printf("yes\n");
            } else {
                printf("no\n");
            }

        // product of 3 nums
        } else if (combo == 3){
            for (int a = 0; a < arrayLength; a++){
                for (int b = 1; b < arrayLength; b++){
                    for (int c = 2; c < arrayLength; c++){
                        if (numsArray[a] * numsArray[b] * numsArray[c] == product){
                            result = 1;
                            break;
                        } else {
                            continue;
                        }
                    }
                    
            }
        }
        if (result == 1){
                printf("yes\n");
            } else {
                printf("no\n");
            }

    }
    }

    // All done! (finally);
    free(numsArray);
    fclose(fp);
    return EXIT_SUCCESS;
}
