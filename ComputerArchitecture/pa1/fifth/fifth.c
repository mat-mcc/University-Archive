#include <stdio.h>
#include <stdlib.h>

// Matthew McCaughan
// Computer Archicture pa1 fifth
// February 9th
// Matrix determinant (nxn, n <= 20)

/*
PROGRESS NOTES:
functionally complete(?)
WAITING ON AUTOGRADER
*/

/*
a b
c d


a b c
d e f
g h i 
*/


// |A| = A
// |A| = ad - bc
// |A| = a(ei − fh) − b(di − fg) + c(dh − eg)

// base case, determinant of matrix n <= 3 can actually be calculated
int calcDet(int* matrix, int dimension) {
    if (dimension == 1){
        return matrix[0];
    }
    if (dimension == 2){
        int det = (matrix[0]*matrix[3]) - (matrix[1]*matrix[2]);
        return det;

    }
    if (dimension == 3){
        int comp1 = matrix[0]*(matrix[4]*matrix[8] - matrix[5]*matrix[7]);
        int comp2 = matrix[1]*(matrix[3]*matrix[8] - matrix[6]*matrix[5]);
        int comp3 = matrix[2]*(matrix[3]*matrix[7] - matrix[4]*matrix[6]);
        int det = comp1 - comp2 + comp3;
        return det;
    }

    return 0;


}


// recursive matrix determinant calculator! (takes a matrix and dimension of such matrix)
int determinant(int *matrix, int dimension) {
    int det = 0;

    // base cases dimension <= 3
    if (dimension == 1){
        det = calcDet(matrix,1);
        return det;
    }
    if (dimension == 2){
        det = calcDet(matrix, 2);
        return det;
    }
    if (dimension == 3) {
        // 3x3 matrix base case
        det = calcDet(matrix,3);
        return det;
    } else {
        // RECURSION TIME!
        // greater than 3x3 matrix, break down into row expansion until 3x3 (hopefully)
        for (int j = 0; j < dimension; j++) {
            int *minor = malloc((dimension - 1) * (dimension - 1) * sizeof(int));
            // Calculate minor matrix excluding current row and column
            int minor_index = 0;
            for (int i = dimension; i < dimension * dimension; i++) {
                // is i the column index?
                if (i % dimension != j) {
                    minor[minor_index++] = matrix[i];
                }
            }
            // sign of minor matrix (row expansion after all)
            int sign = 0;
            if (j % 2 == 0){
                sign = 1;
            } else {
                sign = -1;
            }
            // Recursive call!!
            det += sign * matrix[j] * determinant(minor, dimension - 1);

            // important!
            free(minor);
        }
    }
    return det;
}

int main (int argc, char** argv){

    // file time!
    FILE* fp = fopen(argv[1], "r");

    if(fp == NULL){
        printf("unable to open input file\n");
        exit(EXIT_SUCCESS);
    }

    // dimension of matrix?
    int matrixDim;
    fscanf(fp,"%d\n", &matrixDim);

    // allocate the matrix!
    int *mat = malloc(matrixDim*matrixDim*sizeof(int));

    // read from file and place into matrix
    int temp = 0;
    for (int i = 0; i < matrixDim; i++){
        for (int j = 0; j < matrixDim; j++){
            fscanf(fp,"%d", &temp);
            mat[i * matrixDim + j] = temp;
        }
    }
    // call the function!
    int resulant = determinant(mat, matrixDim);
    printf("%d\n", resulant);
    // most importantly!
    free(mat);
    return 0;
}
