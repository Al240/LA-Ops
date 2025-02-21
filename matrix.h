/* matrix.h: Function declarations for LA-Ops (Matrices)
Written by: Al240 // 2/14/2025

ver.    Date        Changelog
1.2     2/20/2025   [AL] Added support for augmented matrix solver and eigenvalue solver
1.0     2/14/2025   [AL] Initial code */

#ifndef MATRIX_H
#define MATRIX_H

typedef struct { // 3D Vector associated with a label
    int rows;
    int columns;
    double** entries;
} Matrix;

Matrix* newMatrix(int mRow, int nCol, int udef); // Creates a new matrix of size mRowxnCol
int mDisp(Matrix *matA); // Display matrix
int mRREF(Matrix *matA); // Row-reduced echelon form
int mDim(Matrix matA); // Dim(A)
int mAddSub(Matrix matA, Matrix matB); // [A] +/- [B]
int mMult(Matrix matA, Matrix matB); // [A][B]
int mDet(Matrix matA); // det(A), currently limited to matrices up to 3x3
int mSolver(Matrix matA, Matrix vecB); // Solve [A]x=[B] using augmented matrix & row ops
int mEigen(Matrix matA); // Eigenvalue solver

#endif