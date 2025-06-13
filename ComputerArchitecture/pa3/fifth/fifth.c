#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void roundBinaryFraction(int binary[], int length, int roundToBits) {
    int roundBitPos = length - roundToBits;
    
    // check for 1 at rounding spot
    //printf("%d\n", roundBitPos);
    if (binary[roundBitPos] == 1 && roundBitPos < length - 1) {
        // mark bits after rounding spot
        int significantBitsAfterRound = 0;
        for (int i = roundBitPos + 1; i < length; i++) {
            if (binary[i] == 1) {
                significantBitsAfterRound = 1;
                break;
            }
        }
        
        // ROUNDING!!!
        if (significantBitsAfterRound || (roundBitPos + 1 < length && binary[roundBitPos + 1] == 1)) {
            int carry = 1;
            int i = roundBitPos - 1;
            
            // propogate carry
            while (carry != 0 && i >= 0) {
                int sum = binary[i] + carry;
                binary[i] = sum % 2;
                //printf("%d\n", binary[i]);
                carry = sum / 2;
                i--;
            }
        }
    }
    
    // Print the rounded fraction representation
    //printf("Rounded fraction (in %d bits): ", roundToBits);
    for (int i = 0; i < roundToBits; i++) {
        printf("%d", binary[i]);
    }
    printf("\n");
}

double binaryFractionToDecimal(int binaryFraction[], int size) {
    double decimal = 0.0;
    double fraction = 0.5;
    
    for (int i = 0; i < size; i++) {
        if (binaryFraction[i] == 1) {
            decimal += fraction;
        }
        fraction = fraction / 2; 
    }
    
    return decimal;
}

int calcBias(int exponentBits){
    return (((1 << exponentBits)/2)-1);
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
    int exponentBits;
    int fractionBits;

        fscanf(fp,"%lf %d %d %d\n", &value, &numBits, &exponentBits, &fractionBits);
        //printf("%lf %d %d %d\n", value, numBits, exponentBits, fractionBits);

    //printf("%d\n", numBits);
    //printf("%d\n", (1 << numBits) -1);
        //decimalToBinary(value, numBits, exponentBits, fractionBits);

    // CALCULATE BITS NEEDED TO REPRESENT NON FRACTION PART
    int BitsNeeded = 0;
    while (1 << BitsNeeded <= abs(value)){
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
            //printf("%d", fracRep[i]);
        }
        //printf("\n");
        
int exponent = BitsNeeded - 1;
int fractionArray[128];
for (int i = 0; i < 128; i++){
    fractionArray[i] = 0;
}
    int fractionArrayindex = 0;


// IF EXPONENT IS NEGATIVE
if (exponent < 0){
    int oneTracker = 0;
    while (fracRep[oneTracker] == 0){
        oneTracker++;
        exponent--;
        //printf("Exponent: %d\n", exponent);

    }

    //fractionArray[0] = 1;//fracRep[oneTracker]; 
    //printf("%d", fracRep[oneTracker]);
    //printf(".");
    int counter = numBits;
    //fractionArrayindex++;
    for (int i = oneTracker+1; i < BitsNeededF; i++){
        //fractionArray[fractionArrayindex] = fracRep[i];
        fractionArrayindex++;
        //printf("%d", fracRep[i]);
        counter--;
        if (counter == 0){
            break;
        }
    }        fractionArrayindex--;

    while (counter != 0){
        //fractionArray[fractionArrayindex] = 0;
        fractionArrayindex++;
        //printf("%d", 0);
        counter--;
    }
int offset = 0;
for (int i = 0; i < BitsNeeded; i++){
            fractionArray[i] = binRep[i];
            offset++;
            //printf("%d", binRep[i]);
        }
        //printf(" ");

 for (int i = 1; i < BitsNeededF; i++){
    fractionArray[i-1] = fracRep[i+oneTracker];
    if (fracRep[i+oneTracker] == -1 || fracRep[i+oneTracker] == 4){
        fractionArray[i-1] = 0;
    }
            //printf("%d", fracRep[i]);
        }
}

// ELSE EXPONENT IS POSITIVE
    else {  
        //fractionArray[0] = 9; 
//printf("%d", binRep[0]);
//printf(".");
int counter = numBits;
int arrayOffset = 0;
for (int i = 1; i < BitsNeeded; i++){

    fractionArrayindex++;

    //printf("%d", binRep[i]);
    arrayOffset++;
    counter--;
    if (counter == 0){
        break;
    }
}
//printf("z");

if (counter != 0){
for (int i = 0; i < BitsNeededF; i++){
    fractionArrayindex++;
    //printf("%d", fracRep[i]);
    counter--;
    if (counter == 0){
        break;
    }
}
}
while (counter != 0){
    //printf("%d", 0);
    counter--;
}
int offset = 0;
for (int i = 1; i < BitsNeeded; i++){
            fractionArray[i-1] = binRep[i];
            offset++;
            //printf("%d", binRep[i]);
        }
        //printf(" ");

 for (int i = 0; i < BitsNeededF; i++){
    fractionArray[i+offset] = fracRep[i];
        if (fracRep[i] == -1 || fracRep[i] == 4){
        fractionArray[i+offset] = 0;
    }
            //printf("%d", fracRep[i]);
        }
        //printf("\n");
}
//printf(" %d", exponent);
//printf("\n");

//printf("fractional part with array representation: ");
//for (int i = 0; i < BitsNeededF+BitsNeeded-1; i++){
    //printf("%d", fractionArray[i]);
//}
//printf("\n");
//double fractionRepDecimal = binaryFractionToDecimal(fractionArray, BitsNeededF+BitsNeeded);
//printf("fractional part as decimal: %lf\n", fractionRepDecimal);

// I-EEE REP

int Bias = calcBias(exponentBits);
//printf("Bias: %d\n", Bias);
int IEEEexp = Bias + exponent;
//printf("IEEEexp: %d\n", IEEEexp);

// calculate for subnormal value;
int oneTracker = 0;
    while (fracRep[oneTracker] == 0){
        oneTracker++;
        //printf("Exponent: %d\n", exponent);

    }
if (IEEEexp == 0){
    int offset = 0;
for (int i = 0; i < BitsNeeded; i++){
            fractionArray[i] = binRep[i];
            offset++;
            //printf("%d", binRep[i]);
        }
        //printf(" ");

 for (int i = 0; i < BitsNeededF; i++){
    fractionArray[i] = fracRep[i+oneTracker];
    if (fracRep[i] == -1 || fracRep[i] == 4){
        fractionArray[i] = 0;
    }
            //printf("%d", fracRep[i]);
        }
}

int signBit = 4;

if (value > 0){
    signBit = 0;
}
else if (value < 0) {
    signBit = 1;
}

//printf("Sign Bit: %d\n", signBit);

int binaryExponent[128];

DecimalToBinary(IEEEexp,exponentBits,binaryExponent);
//printf("IEEE exponent in binary Rep: ");
                for (int i = 0; i < exponentBits; i++){
            //printf("%d", binaryExponent[i]);
        }
        //printf("\n");

//int binExpP1[128];
//int binExpS1[128];

for (int i = 0; i < 128; i++){
    //binExpP1[i] = binaryExponent[i];
    //binExpS1[i] = binaryExponent[i];
}

// FINAL PRINTING
printf("%d",signBit); // SIGN BIT
        
// EXPONENT BITS
                for (int i = 0; i < exponentBits; i++){
            printf("%d", binaryExponent[i]);
        }


// FRACTION BIT

// ADD CHECK WHERE IF NUMBER OF BITS IN FRACITON IS GREATER THAN SPECIFIED
// LENGTH, OTHERWISE WILL ROUND UNCESSECARILY

//printf("rounding to %d digits: ", fractionBits);
//printf("\n");

//printf("%d\n", fractionBits);
//printf("%d\n", BitsNeeded + BitsNeededF);
if (fractionBits <= BitsNeeded + BitsNeededF){
roundBinaryFraction(fractionArray, BitsNeeded+BitsNeededF, fractionBits);
//roundBinaryFraction(fractionArray, BitsNeeded+BitsNeededF, fractionBits);

}
else {
    //printf("No need to round!\n");
    for (int i = 0; i < fractionBits; i++) {
        //printf("%d", fractionArray[i]);
    }
}




//printf("\n");


} // end of loop for each line of input



    return 0;
} 

