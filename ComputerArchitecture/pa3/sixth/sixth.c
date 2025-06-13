#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


double calcFrac(int f, int fractionBits){
        double half = 1;
        double decimalfromBin = 0;
   for (int i = 0; i <= fractionBits; i++){
        if (((f >> (fractionBits - i)) & 1) == true){
            decimalfromBin = decimalfromBin + half;
        }

        half = half * 0.5;

    }
    return decimalfromBin;
}
int main(int argc, char** argv){

     // firstly
    FILE* fp = fopen(argv[1], "r");

    if(fp == NULL){
        printf("unabe to open input file\n");
        exit(EXIT_SUCCESS);
    }

    int Position = ftell(fp);
    //GET lines
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
    int totalBits;
    int exponentBits;
    int fractionBits;
    
    
    char value[64];
    // CHANGE THIS VALUE


    int precision;
        fscanf(fp,"%d %d %d %s %d\n", &totalBits, &exponentBits, &fractionBits, value, &precision);
        //printf("%d %d %d %s %d\n", totalBits, exponentBits, fractionBits, value, precision);

    long int hexvalue = strtol(value,NULL,0);
    //printf("%ld\n",hexvalue);
    // grab first bit
    int s = (hexvalue >> (totalBits-1) & 1);
    // grab the middle bits!
    int exp = (hexvalue >> (totalBits -1 - exponentBits)) & ((1 << exponentBits) -1);
    // grab the end
    int f = hexvalue & ((1 << fractionBits)-1);

    //printf("%d %d %d\n", s, exp, f);

    double decimalfromBin = 0;

    // calculate fractional piece

    decimalfromBin = calcFrac(f, fractionBits);
    
    //printf("%f\n", decimalfromBin);

    // V = ((-1) ^ s) * M * (2 ^ E)
    // M = 1 + f and E = e - Bias = e - ((2 ^ (k - 1)) - 1)
    int sign = 0;
    if (s == 1){
        sign = -1;
    } else if (s == 0){
        sign = 1;
    }
    double fractionPart = 1 + decimalfromBin;
    //printf("decimal from bin: %lf\n", decimalfromBin);

    //printf("frac part: %lf\n", fractionPart);
    int IEEEbias = (((1 << exponentBits)/2)-1);
    //printf("%d\n", IEEEbias);
    int E = exp - IEEEbias;
    //printf("E: %d\n", E);
    //double powa = pow(2,E);
    //printf("powerexp: %lf\n", powa);
     double final = 0;
    if (exp !=0){
    final = sign*(fractionPart * pow(2, E));
    } else if (exp == 0){
        E = 1-IEEEbias;
        final = sign*(fractionPart-1)*pow(2,E);
    }

    //printf("%f\n", final);
    printf("%.*f\n", precision, final); 
}
return 0;
}