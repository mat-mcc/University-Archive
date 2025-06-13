#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void TwosComplement (int value, int numBits, int binRep[]){
    for (int i = 0; i < numBits; i++){
        if (binRep[i] == 1){
            binRep[i] = 0;
            //printf("%d", binRep[i);
        }
        else if (binRep[i] == 0){
            binRep[i] = 1;
        }
    }
    if (binRep[numBits-1] == 0){
        binRep[numBits-1] = 1;
    }
    else if (binRep[numBits-1] == 1){
    int carry = 1; 

    for (int i = numBits - 1; i >= 0; i--) {
        if (binRep[i] == 0 && carry == 1) {
            binRep[i] = 1;
            //printf("%d\n", binRep[i]);
            carry = 0; 
        } else if (binRep[i] == 1 && carry == 1) {
            binRep[i] = 0;
        }
    }
}
}

void DecimalToBinary(int value, int numBits, int binRep[]){
    long one = 1;
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
    //printf("num lines: " "%d\n", lines);
    fseek(fp, Position, SEEK_SET); 

    for (int i = 0; i < lines; i++){
    long value;
    int numBits;
    int binRep[128];
    for (int i = 0; i < 128; i++){
        binRep[i] = -1;
    }

        fscanf(fp,"%ld %d\n", &value, &numBits);
        //printf("%d %d\n", value, numBits);

    //printf("%d\n", numBits);
    //printf("%d\n", (1 << numBits) -1);
            long one = 1;
            long largest = ((one << (numBits-1)) - 1);
            long smallest = -((one << (numBits-1)));

            //printf("range [%d ", smallest);
            //printf("%d]\n", largest);




    // outside of range, produce largest positive or smallest negative number
    if (value > largest || value < smallest){

        //printf("Cannot rep in range!\n");
        if (value > 0){
        //DecimalToBinary(remainder, numBits);
        //printf("%d\n", largest);
        // produce largest pos number given twos complement
        DecimalToBinary(largest, numBits,binRep);
        }
        if (value < 0){
        // produce smallest negative number given twos complement
        // opposite of smallest to binary then convert to twos complement
        DecimalToBinary(-smallest,numBits,binRep);
        
            //printf("%d\n", smallest);
        }

    } else {

        // inside range, produce value as binary with twos complement
        //printf("can rep!\n");
        if (value > 0){
            // positive, turn to binary
        DecimalToBinary(value, numBits,binRep);
        }
        else if (value < 0){
            DecimalToBinary(-value, numBits, binRep);

            if (value != smallest){
            TwosComplement(value, numBits, binRep);
        }

        }
        if (value == 0){
            DecimalToBinary(0, numBits,binRep);
        }

    }
                    for (int i = 0; i < numBits; i++){
            printf("%d", binRep[i]);
        }
        printf("\n");
    }

    return 0;
}