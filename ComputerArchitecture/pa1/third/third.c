#include <stdio.h>
#include <stdlib.h>

// Matthew McCaughan
// Computer Archicture pa1 third
// February 9th
// Matrix Exponentiation (10pts)

/*
PROGRESS NOTES:
*/

/* CODE */


// real meat of the algorithm!
// takes the matrix, its dimension, power being raised to, and then an accumulating result matrix for tracking
void matrixExponentiation(int *matrix, int dim, int power, int *result) {

    // do we even need this? if n == 0 , print the identity matrix
if (power == 0){
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                if (i==j){
                    result[i * dim + j] = 1;
                } else {
                    result[i*dim+j] = 0;
                }
        }
    }
    return;
    }
    // copy the input matrix to the result matrix
    for (int i = 0; i < dim * dim; i++) {
        result[i] = matrix[i];
    }

    // perform exponentiation (main loop magic!)
    for (int p = 2; p <= power; p++) {
        // temp matrix for holding the product
        int *temp = malloc(dim * dim * sizeof(int));

        // Initialize the temp matrix to zeros
        for (int i = 0; i < dim * dim; i++) {
            temp[i] = 0;
        }
        // Multiply result by matrix
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                for (int k = 0; k < dim; k++) {
                    temp[i * dim + j] += result[i * dim + k] * matrix[k * dim + j];
                }
            }
        }

        // Copy temp to result
        for (int i = 0; i < dim * dim; i++) {
            result[i] = temp[i];
        }

        free(temp);
    }
}


// Function to print a matrix (for debugging purposes (not anymore actually))
void printMatrix(int *matrix, int dimension) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if(j == dimension-1){
                printf("%d", matrix[i*dimension + j]);
                break;
            }
            printf("%d\t", matrix[i * dimension + j]);
        }
        printf("\n");
    }
}



int main (int agrc, char** argv){
// file time!
    FILE* fp = fopen(argv[1], "r");

    if(fp == NULL){
        printf("unable to open input file\n");
        exit(EXIT_SUCCESS);
    }

    // dimension of matrix?
    int matrixDim;
    fscanf(fp,"%d\n", &matrixDim);
    //printf("%d", matrixDim);

    // allocate the matrix!
    // using a regular array to represent a 2D matrix because I love torturing myself!
    int *mat = malloc(matrixDim*matrixDim*sizeof(int));

    // allocate the result matrix (gotta store it somewhere!)
    int *result = malloc(matrixDim*matrixDim*sizeof(int));

    // read from file and place into matrix
    int temp = 0;
    for (int i = 0; i < matrixDim; i++){
        for (int j = 0; j < matrixDim; j++){
            fscanf(fp,"%d", &temp);
            mat[i * matrixDim + j] = temp;
            //printf("%d", mat[i * matrixDim + j]);
        }
    }
    // grab the power
    int power;
    fscanf(fp,"%d\n", &power);
    //printf("%d\n", power);

    // Actual algorithm time!
    matrixExponentiation(mat, matrixDim, power, result);
    // Print the result
    printMatrix(result, matrixDim);
    // most importantly!
    free(result);
    free(mat);
    return 0;

}
