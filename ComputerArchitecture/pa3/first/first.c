#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void DecimalToBinary(long value, int numBits){
    long one = 1;
    int binRep[128];
    numBits--;
    int a = numBits;
        for (int i = 0; i <= numBits; i++){
            if (one << a > value){
                //printf("  %d  ", 1 << a);
                binRep[i] = 0;
                //printf("0");
            }
            else {
                binRep[i] = 1;
                //printf("1");
                value = value - (one << a);
            }
            a--;
            //printf(" %d ", value);
        }
        //printf("\n");
        for (int i = 0; i <= numBits; i++){
            printf("%d", binRep[i]);
        }
        printf("\n");
    }

int main (int agrc, char** argv){

     // firstly
    FILE* fp = fopen(argv[1], "r");

    if(fp == NULL){
        printf("unabe to open input file\n");
        exit(EXIT_SUCCESS);
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
    //lines -= 1;
    //      printf("num lines: " "%d\n", lines);
    fseek(fp, Position, SEEK_SET); 

    for (int i = 0; i < lines; i++){
    long value;
    int numBits;
        fscanf(fp,"%ld %d\n", &value, &numBits);
        //printf("%ld %d\n", value, numBits);
    long one = 1;
    //printf("%d\n", numBits);
    //printf("%ld\n", (1 << numBitsL) -1);

    if ( (one << numBits) - 1 < value){

        //      printf("Cannot rep!\n");
        int remainder = value % (one << numBits);
        DecimalToBinary(remainder, numBits);

    } else {
        //      printf("can rep!\n");
        DecimalToBinary(value, numBits);
    }
    }
printf("\n");
    return 0;
}