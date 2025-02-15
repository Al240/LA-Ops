/* matrix.h: Function declarations for LA-Ops (Matrices)
Written by: Al240 // 2/14/2025

ver.    Date        Changelog
1.0     2/14/2025   [AL] Initial code */

#ifndef MATRIX_H
#define MATRIX_H

typedef struct { // 3D Vector associated with a label
    int rows;
    int columns;
    double** entries;
} Matrix;

Matrix getMatrix(void); // User definition of a matrix
int ddRank(double matA); // det(A), Dim(A), and Rank(A)
int mAddSub(double matA, double matB); // [A] +/- [B]
int mMult(double matA, double matB); // [A][B]
int mNull(double matA); // Null(A), [A]x=[0]
int mSolve(double matA); // Augmented matrix solving, [A]x=[B]
int mEigen(double matA); // Eigenvalue and vector calculation

#endif