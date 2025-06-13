#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



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
    double value;
    int numBits;
    int binRep[128];
    for (int i = 0; i < 128; i++){
        binRep[i] = -1;
    }
    int fracRep[128];
    for (int i =0; i < 128; i++){
        fracRep[i] = -1;
    }

        fscanf(fp,"%lf %d\n", &value, &numBits);
        //printf("%lf %d\n", value, numBits);

    //printf("%d\n", numBits);
    //printf("%d\n", (1 << numBits) -1);


    // CALCULATE BITS NEEDED TO REPRESENT NON FRACTION PART
    int BitsNeeded = 0;
    while (1 << BitsNeeded <= value){
        BitsNeeded++;
    }
    //printf("Int bits needed: %d\n", BitsNeeded);

    int valueI = value;
    DecimalToBinary(valueI, BitsNeeded, binRep);
    //GET FRACTION PART
    double fractionPart = value - valueI;
    int BitsNeededF = 0;
    double remainder = fractionPart;
    while (remainder > 0) {
        remainder *= 2;
        BitsNeededF++;
        if (remainder >= 1){
            remainder -= 1;
        }
    }
    //printf("Fraction Bits needed: %d\n", BitsNeededF);
    double half = 0.5;
     for (int i = 0; i < BitsNeededF; i++) {
        if (fractionPart > half){
            fracRep[i] = 1;
            fractionPart = fractionPart - half;
        }
        else if (half > fractionPart){
            fracRep[i] = 0;
            fractionPart = half - (half - fractionPart);
            //printf("%lf\n", fractionPart);
        }
        else {
            fracRep[i] = 1;
        }
        half = half * 0.5;
    }

    //FractionToBinary(fractionPart, )
    
 for (int i = 0; i < BitsNeeded; i++){
            //printf("%d", binRep[i]);
        }
        //printf(" ");

 for (int i = 0; i < BitsNeededF; i++){
            //rintf("%d", fracRep[i]);
        }
        //printf("\n");
        
int exponent = BitsNeeded - 1;

// IF EXPONENT IS NEGATIVE
if (exponent < 0){
    int oneTracker = 0;
    while (fracRep[oneTracker] == 0){
        oneTracker++;
        exponent--;
        //printf("Exponent: %d\n", exponent);

    }
    printf("%d", fracRep[oneTracker]);
    printf(".");
    int counter = numBits;
    for (int i = oneTracker+1; i < BitsNeededF; i++){
        printf("%d", fracRep[i]);
        counter--;
        if (counter == 0){
            break;
        }
    }
    while (counter != 0){
        printf("%d", 0);
        counter--;
    }
}
// ELSE EXPONENT IS POSITIVE
    else {   
printf("%d", binRep[0]);
printf(".");
int counter = numBits;
for (int i = 1; i < BitsNeeded; i++){
    printf("%d", binRep[i]);
    counter--;
    if (counter == 0){
        break;
    }
}
if (counter != 0){
for (int i = 0; i < BitsNeededF; i++){
    printf("%d", fracRep[i]);
    counter--;
    if (counter == 0){
        break;
    }
}
}
while (counter != 0){
    printf("%d", 0);
    counter--;
}
    }
printf(" %d", exponent);
printf("\n");
//printf("\n");


}


    return 0;
}