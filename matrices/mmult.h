// mmult.h declares the functionality for matrix multiplication
// @author exl2748: Erica LaBuono

#ifndef _MMULT_H_
#define _MMULT_H_
#include <stdio.h>
#include <stdlib.h>

/// mmult creates a new matrix A*B, performing multiplication and allocating a rAxcB matrix
/// @params rA, cA represent the amt. of rows and cols of matrix A
/// @params rB, cB represent the amt. of rows and cols of matrix B
/// @params A, B are the matrices, a 2D array of doubles
/// @return a 2D array of doubles, size rA x cB
double **mmult(int rA, int cA, double **A, int rB, int cB, double **B);

/// xalloc allocates an r x c matrix of doubles, initialized as zeroes
/// @params r, c are integers representing the row and col of the matrix
/// @return a 2D array of doubles, size r x c
double **xalloc(int r, int c);

/// xfree frees all the memory allocated for the matrix.
/// @param r is an int representing the rows of the matrix
/// @param A is the matrix, a 2D array of doubles
void xfree(int r, double **A);

/// mread reads a matrix in row-major order from a file
/// mread assumes the precondition that the correct num of rows, cols exist in file
/// @params r, c are ints representing the row and col of the matrix
/// @param fp is the file pointer being read
/// @return a 2D array of doubles, size r x c
double **mread(FILE *fp, int *r, int *c);

/// mwrite writes matrix A into an already open file
/// @params rA, cA are ints representing the row and col of the matrix
/// @param fp is the file pointer being written to
/// @param A is the matrix, a 2D array of doubles
void mwrite(FILE *fp, int rA, int cA, double **A);

#endif
