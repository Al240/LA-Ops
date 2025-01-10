/***
Matrix Multiplication Calculator

Simple C program that calculates the product of 2 matrices.

Written by Al240
EECS 22 (Winter '25) Assignment 1

ver.    Date        Changes
-------------------------------------
1.0     1/9/2025    Initial code
***/

#include <stdio.h>
#define MATRIX_SIZE 4

int main(void) {
    // Initialize 2x2 matrices A and B
    int matrA[MATRIX_SIZE];
    int matrB[MATRIX_SIZE];
    char currInput[4] = "a11\0"; // Used as label for each element in matrix

    // Input matrix A
    printf("Enter the first matrix(a) that will be multiplied:\n");
    for (int i=0; i<MATRIX_SIZE; i++) {
        printf("%s = ", currInput);
        scanf(" %d", &matrA[i]);
        if (currInput[2] == '2') {
            currInput[1] = '2';
            currInput[2] = '1';
        }
        else currInput[2] = '2';
    }

    currInput[0] = 'b'; // Prepare label for matrix B input
    currInput[1] = '1';
    currInput[2] = '1';

    // Input matrix B
    printf("\nEnter the second matrix(a) that will be multiplied:\n");
    for (int i=0; i<MATRIX_SIZE; i++) {
        printf("%s = ", currInput);
        scanf(" %d", &matrB[i]);
        if (currInput[2] == '2') {
            currInput[1] = '2';
            currInput[2] = '1';
        }
        else currInput[2] = '2';
    }

    // Calculate product and store in matrix C (C=A*B)
    int matrC[MATRIX_SIZE] = {((matrA[0] * matrB[0]) + (matrA[1] * matrB[2])), // c11
    ((matrA[0] * matrB[1]) + (matrA[1] * matrB[3])), // c12
    ((matrA[2] * matrB[0]) + (matrA[3] * matrB[2])), // c21
    ((matrA[2] * matrB[1]) + (matrA[3] * matrB[3]))};// c22

    // Display final product
    printf("\nResult:\n");
    printf("%d %d\n%d %d", matrC[0], matrC[1], matrC[2], matrC[3]);
}