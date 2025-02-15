/* matrix.c: Matrix-related operations for LA-Ops
Written by: Al240 // 2/14/2025

ver.    Date        Changelog
1.0     2/14/2025   [AL] Initial code */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

Matrix* getMatrix(void) {
    Matrix *m1 = (Matrix*)malloc(sizeof(Matrix)); // Matrix memory allocation
    if (!m1) {
        printf("ERROR: Could not allocate memory to initialize matrix (step1).\n");
        return 1;
    }
    int mRow, mCol;
    printf("How many rows should the matrix have? ");
    scanf(" %d", &mRow);
    printf("How many columns should the matrix have? ");
    scanf(" %d", &mCol);

    m1->rows = mRow;
    m1->columns = mCol;
    
    m1->entries = (double**)malloc(mRow*sizeof(double*)); // Row memory allocation
    if (!m1->entries) {
        printf("ERROR: Could not allocate memory for matrix rows (step2).\n");
        free(m1);
        return 1;
    }

    for (int r=0; r<mRow; r++) {
        m1->entries[r] = (double*)malloc(mCol*sizeof(double)); // Memory allocation for mCol columns
        if (!m1->entries[r]) {
            printf("ERROR: Could not allocate memory for matrix columns (step3).\n");
            for (int i=0; i<r; i++) {
                free(m1->entries[r]);
            }
            free(m1->entries);
            free(m1);
            return 1;
        }
    }

    return m1;
} // User definition of a matrix

int ddRank(double matA); // det(A), Dim(A), and Rank(A)
int mAddSub(double matA, double matB); // [A] +/- [B]
int mMult(double matA, double matB); // [A][B]
int mNull(double matA); // Null(A)
int mSolve(double matA); // Augmented matrix solving, [A]x=[B]
int mEigen(double matA); // Eigenvalue and vector calculation