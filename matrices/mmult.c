// mmult.c implements the functionality of matrix multiplication
// @author exl2748: Erica LaBuono
// // // // // // // // // // // // // // // //

#include "mmult.h"
#include <string.h>

/// xalloc allocates a r x c matrix of doubles, assigning 0.0 initially
double **xalloc(int r, int c) {
	double **m;
	int i, j, k;

	m = (double **) malloc(r * sizeof(double *)); // allocate space for double * rows

	for (i = 0; i < r; i++) {
		m[i] = (double *) malloc(c * sizeof(double)); // allocate the double * cols
	}

	// initialize zeroes in all slots of m[j][k]
	for (j = 0; j < r; j++) {
		for (k = 0; k < c; k++) {
			m[j][k] = 0.0;
		}
	}
	
	return m;
}

/// xfree frees the allocated memory for a 2D array A
void xfree(int r, double **A) {
	int i;
	for (i = 0; i < r; i++) {
		free(A[i]);
	}

	free(A);
}


/// mmult creates and returns a matrix of A * B, size rA x cB 
double **mmult(int rA, int cA, double **A, int rB, int cB, double **B) {
	double **AB = xalloc(rA, cB);
	int i, j, k;
	(void) rB;
	for (i = 0; i < rA; ++i) {
		for (j = 0; j < cB; ++j) {
			for (k = 0; k < cA; ++k) {
				AB[i][j] += A[i][k] * B[k][j];
			}
		}
	}

	return AB;
}

/// mread reads a matrix in row-major order from a file
double **mread(FILE *fp, int *r, int *c) {
	double **m = xalloc(*r, *c);
	char *buf = NULL;
	char *pch;
	size_t linelen = 0;
	int i, j;
	for (i = 0; i < *r; i++) {
		getline(&buf, &linelen, fp);
		pch = strtok(buf, " ");
		for(j = 0; j < *c; j++) {
			m[i][j] = strtod(pch, NULL);
			pch = strtok(NULL, " ");
		}
	}
	free(buf);
	return m;
} 

/// mwrite writes matrix A into an a file
void mwrite(FILE *fp, int rA, int cA, double **A) {
	int i, j;
	fprintf(fp, "%d %d\n", rA, cA); // print row and col
	for (i = 0; i < rA; i++) {
		for (j = 0; j < cA; j++) {
			fprintf(fp, "%8.2lf", A[i][j]); // when do we need a newline?
		}
		fprintf(fp, "\n");
	}
}





