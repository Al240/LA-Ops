/* matrix.c: Matrix-related operations for LA-Ops
Written by: Al240 // 2/14/2025

ver.    Date        Changelog
1.2     2/20/2025   [AL] Added support for augmented matrix solver
1.1     2/15/2025   [AL] Fixed some input (looping behavior) and display bugs
1.0     2/14/2025   [AL] Initial code */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

Matrix* newMatrix(int mRow, int nCol, int udef) {
    Matrix *m1 = (Matrix*)malloc(sizeof(Matrix)); // Matrix memory allocation
    if (!m1) {
        printf("ERROR: Could not allocate memory to initialize matrix (step1).\n");
        return NULL;
    }

    m1->rows = mRow;
    m1->columns = nCol;
    
    m1->entries = (double**)malloc(mRow*sizeof(double*)); // Row memory allocation
    if (!m1->entries) {
        printf("ERROR: Could not allocate memory for matrix rows (step2).\n");
        free(m1);
        return NULL;
    }

    for (int r=0; r<mRow; r++) {
        m1->entries[r] = (double*)malloc(nCol*sizeof(double)); // Memory allocation for mCol columns
        if (!m1->entries[r]) {
            printf("ERROR: Could not allocate memory for matrix columns (step3).\n");
            for (int i=0; i<r; i++) {
                free(m1->entries[r]);
            }
            free(m1->entries);
            free(m1);
            return NULL;
        }

        if (udef) { // If this is specified, user can input the entries
            for (int col=0; col<nCol; col++) {
                while (1) {
                    int numIn; // Dummy variable to store raw input
                    printf("Input an entry for the matrix (a%d%d): ", r+1, col+1);
                    int verifyInput = scanf(" %d", &numIn); //&(m1->entries[r][col])
                    if (verifyInput) { // Input validation: valid input
                        m1->entries[r][col] = numIn; // Store inputted value in the matrix
                        break; // Continue to next entry
                    }
                    else {
                        printf("ERROR: Invalid input. Please enter real numbers only!\n"); // Invalid input
                        while ((getchar()) != '\n') {} // Clear remaining chars in buffer
                    }
                }
            }
        }
    }
    if (udef) {
        printf("Your inputted matrix:\n");
        mDisp(m1);
    }
    return m1;
} // User definition of a matrix

int mDisp(Matrix *matA) {
    if (!matA) return 2;

    for (int r=0; r<matA->rows; r++) {
        for (int col=0; col<matA->columns; col++) {
            printf("%.3f ", matA->entries[r][col]);
        }
        printf("\n");
    }
    return 0;
} // Show matrix

int mRREF (Matrix * matA) {
    int i, j, k;
    
    for (i = 0; i < matA->rows; i++) {
        // Find the pivot (largest value in the current column)
        int pivot_row = i;
        for (j = i + 1; j < matA->rows; j++) {
            if (fabs(matA->entries[j][i]) > fabs(matA->entries[pivot_row][i])) {
                pivot_row = j;
            }
        }

        // Swap rows if necessary
        if (pivot_row != i) {
            double *temp = matA->entries[i];
            matA->entries[i] = matA->entries[pivot_row];
            matA->entries[pivot_row] = temp;
        }

        // Make the pivot element 1 by dividing the entire row by the pivot value
        double pivot_value = matA->entries[i][i];
        if (pivot_value != 0) {
            for (j = 0; j < matA->columns; j++) {
                matA->entries[i][j] /= pivot_value;
            }
        }

        // Make the entries below the pivot zero
        for (j = i + 1; j < matA->rows; j++) {
            double factor = matA->entries[j][i];
            if (factor != 0) {
                for (k = 0; k < matA->columns; k++) {
                    matA->entries[j][k] -= factor * matA->entries[i][k];
                }
            }
        }
    }

    // Now make the entries above the pivots zero (back substitution)
    for (i = matA->rows - 1; i >= 0; i--) {
        for (j = i - 1; j >= 0; j--) {
            double factor = matA->entries[j][i];
            if (factor != 0) {
                for (k = 0; k < matA->columns; k++) {
                    matA->entries[j][k] -= factor * matA->entries[i][k];
                }
            }
        }
    }

    printf("Your row-reduced matrix in echelon form:\n");
    mDisp(matA);
    return 0;
} // Obtain row-reduced echelon form (RREF) using Gauss-Jordan elimination

int mDim(Matrix matA) {
    int dim = 0; // Stores dimension
    mRREF(&matA);

    for (int r=0; r<matA.rows; r++) {
        int leadEntry = 0; // Does row have a non-zero leading entry?
        for (int col=0; col<matA.columns; col++) {
            if (matA.entries[r][col] != 0) {
                leadEntry = 1;
                break;
            }
        }
        if (leadEntry) dim++;
    }

    printf("dim(A) = %d", dim);
    return 0;
} // Dim(A)

int mDet(Matrix matA) {
    if (matA.rows != matA.columns) {
        printf("ERROR: Determinants can only be calculated for nxn (square) matrices.\n");
        return 2;
    }
    else {
        if (matA.rows > 3) {
            printf("Determinant operation currently only supports up to 3x3 matrices :(\n");
            return 2;
        }
        if (matA.rows == 2) {
            double detA = (matA.entries[0][0]*matA.entries[1][1]) - (matA.entries[0][1]*matA.entries[1][0]); // det(A) = a11a22 - a12a21
            printf("\nThe determinant of your 2x2 matrix is: %.4f\n", detA);
        }
        if (matA.rows == 3) {
            double detA = (matA.entries[0][0]*(matA.entries[1][1]*matA.entries[2][2]-matA.entries[1][2]*matA.entries[2][1]))    // +a11(a22a33 - a23a32)
            -(matA.entries[0][1]*(matA.entries[1][0]*matA.entries[2][2]-matA.entries[1][2]*matA.entries[2][0]))                 // -a12(a21a33 - a23a31)
            +(matA.entries[0][2]*(matA.entries[1][0]*matA.entries[2][1]-matA.entries[1][1]*matA.entries[2][0]));                // +a13(a21a32 - a22a31)
            printf("\nThe determinant of your 3x3 matrix is: %.4f\n", detA);
        }
    }
    return 0;
} // det(A)

int mAddSub(Matrix matA, Matrix matB) {
    if ((matA.rows != matB.rows) || (matA.columns != matB.columns)) {
        printf("ERROR: A matrix can only be added to another one of the same dimensions.\n");
        return 2;
    }
    else {
        Matrix* result = newMatrix(matA.rows, matB.columns, 0);
        if (!result) return 1;
        int adding = 1;
        char addChoice;
        while (adding) {
            printf("Select Add A+B (+) or Subtract A-B (-): ");
            scanf(" %c", &addChoice);
            switch (addChoice) {
                case '+': case 'A': case 'a': // Addition
                    for (int r=0; r<matA.rows; r++) {
                        for (int col=0; col<matA.columns; col++) {
                            result->entries[r][col] = matA.entries[r][col] + matB.entries[r][col];
                        }
                    }
                    adding = 0;
                    break;
                
                case '-': case 'S': case 's': case 'M': case 'm': // Subtraction
                    for (int r=0; r<matA.rows; r++) {
                        for (int col=0; col<matA.columns; col++) {
                            result->entries[r][col] = matA.entries[r][col] - matB.entries[r][col];
                        }
                    }
                    adding = 0;
                    break;

                default:
                    printf("ERROR: Invalid option.\n"); // input validation
                    while ((getchar()) != '\n') {} // clear input buffer
                    break;
            }
        }
        printf("\nThe addition/subtraction result is:\n");
        mDisp(result);
        return 0;
    }
} // [A] +/- [B]

int mMult(Matrix matA, Matrix matB) {
    if ((matA.rows != matB.columns) || (matA.columns != matB.rows)) {
        printf("ERROR: Unsupported matrices. To multiply A and B, A must be of size m x n while B is n x m.\n");
        return 2;
    }
    else {
        Matrix* mProd = newMatrix(matA.rows, matB.columns, 0);
        if (!mProd) return 1;
        for (int r=0; r<matA.rows; r++) {
            for (int col=0; col<matB.columns; col++) {
                mProd->entries[r][col] = 0; // Initialize product to [0]
            }
        }

        for (int r=0; r<matA.rows; r++) {
            for (int col=0; col<matB.columns; col++) {
                for (int col2=0; col2<matA.columns; col2++)
                mProd->entries[r][col] += matA.entries[r][col2]*matB.entries[col2][col];
            }
        }
        printf("\nThe product of A and B is:\n");
        mDisp(mProd);
        return 0;
    }
} // [A][B]

int mSolver(Matrix matA, Matrix vecB) {
    if (vecB.rows > 1) {
        printf("ERROR: Second matrix B is NOT a valid vector (more than 1 column)!\n");
    }
    else {
        Matrix* Aug = newMatrix(matA.rows+1, matA.columns, 0);
        for (int r=0; r<matA.rows-1; r++) {
            for (int c=0; c<matA.columns; c++) {
                Aug->entries[r][c] = matA.entries[r][c]; // Initialize augmented matrix w/ [A]
            }
        }

        for (int augC=0; augC<Aug->columns; augC++) {
            Aug->entries[matA.rows+1][augC] = vecB.entries[augC][0]; // Initialize B in augmented matrix
        }

        printf("Solution (after RREF): \n");
        mRREF(Aug);
    }
    return 0;
} // Ax=B

int mEigen(Matrix matA) {
    printf("Note: This function is still in beta and currently only supports up to 3x3 matrices.\n");
    if (matA.columns != matA.rows) {
        printf("ERROR: Input matrix must be a square (nxn) matrix!\n");
        return 1;
    }
    else {
        if (matA.rows > 3) {
            printf("ERROR: Eigenvalue solver currently supports up to 3x3 matrices.\n");
            return 1;
        }
        else {
            if (matA.rows == 2) {
                double e1 = (matA.entries[0][0]+matA.entries[1][1]) + sqrt(pow(matA.entries[0][0]+matA.entries[1][1], 2)+(4*(matA.entries[0][0]*matA.entries[1][1] - matA.entries[0][1]*matA.entries[1][0])));
                double e2 = (matA.entries[0][0]+matA.entries[1][1]) - sqrt(pow(matA.entries[0][0]+matA.entries[1][1], 2)+(4*(matA.entries[0][0]*matA.entries[1][1] - matA.entries[0][1]*matA.entries[1][0])));

                printf("\nEigenvalues: %.4f, %.4f\n", e1, e2);
            }
            else if (matA.rows == 3) {
                // 3x3
                printf("3x3 Coming soon!\n");
            }
        }
    }
    return 0;
} // Eigenvalue solver