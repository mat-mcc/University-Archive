#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int readAsSigned(int numBits, int binRep[]){
    int sum = 0;
    int a = numBits -1;
    if (binRep[0] == 1){
    sum = sum - (1 << a);
    }
    a--;
    for (int i = 1; i < numBits; i++){
        if (binRep[i] == 1){
            sum += 1 << a;
        }
        a--;
    }

    return sum;
}

int readAsUnsigned(int numBits, int binRep[]){
    int sum = 0;
    int a = numBits -1;
    for (int i = 0; i < numBits; i++){
        if (binRep[i] == 1){
            sum += 1 << a;
            //printf("%d\n", sum);
        }
        a--;
    }
    return sum;
}

void DecimalToBinary(int value, int numBits, int binRep[]){

    numBits--;
    int a = numBits;
        for (int i = 0; i <= numBits; i++){
            if (1 << a > value){
                //printf("  %d  ", 1 << a);
                binRep[i] = 0;
                //printf("0");
            }
            else {
                binRep[i] = 1;
                //printf("1");
                value = value - (1 << a);
            }
            a--;
            //printf(" %d ", value);
        }
        //printf("\n");
    }

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
    int value;
    int numBits;
    int binRep[128];
    char source[2];
    char castTo[2];
    for (int i = 0; i < 128; i++){
        binRep[i] = -1;
    }

        fscanf(fp,"%d %d %s %s\n", &value, &numBits, source, castTo);
        //printf("%d %d\n", value, numBits);

    //printf("%d\n", numBits);
    //printf("%d\n", (1 << numBits) -1);


        // READING AS A SIGNED FROM UNSIGNED
        if (strcmp(source, "u") == 0){
            //printf("Unsigned\n");
            DecimalToBinary(value,numBits, binRep);
        int result = readAsSigned(numBits, binRep);
        printf("%d\n", result);
        }

        // READING AS AN UNSIGNED FROM SIGNED
        else {



            int largest = ((1 << (numBits-1)) - 1);
            int smallest = -((1 << (numBits-1)));

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
                //for (int i = 0; i < numBits; i++){
            //printf("%d", binRep[i]);
        //}
        //printf("\n");
            if (value != smallest){
            TwosComplement(value, numBits, binRep);
        }
        }
        if (value == 0){
            DecimalToBinary(0, numBits,binRep);
        }

    }
                    int result = readAsUnsigned(numBits, binRep);
        printf("%d\n", result);
    }

    }

    return 0;
}