// mmult-driver.c is the driver for taking input of matrices and performing multiplication
// @author exl2748: Erica LaBuono
// // // // // // // // // // // // // // // //

#include "mmult.h"

/// main takes input from stdin to create and multiply matrices
/// Preconditions assume that the input is a valid format of:
/// 	nonnegative number of matrices with valid row, col values
/// @param argc number of args
/// @param argv arguments passed into
int main(int argc, char *argv[]) {
	if(argc > 1) {
		return 0;
	} else {
		char *buf = NULL;
		size_t len = 0;
		getline(&buf, &len, stdin); // first line of num of matrices
		int matrices = strtol(buf, NULL, 10);
		
		if(matrices == 1) {
			getline(&buf, &len, stdin); // routine for making a matrix
			int r = buf[0] - '0';
			int c = buf[2] - '0';
			double **m = mread(stdin, &r, &c);
			mwrite(stdout, r, c, m);
			free(buf);
			xfree(r, m);
			return 0;
		}

		double **mA;
		double **mB; 
		double **mProduct;
		
		if(matrices > 1) {
			getline(&buf, &len, stdin); // routine for making a matrix
            int rA = buf[0] - '0';
            int cA = buf[2] - '0';
            mA = mread(stdin, &rA, &cA);
			
			for(int i = 1; i < matrices; i++) {
				mProduct = NULL;
				getline(&buf, &len, stdin); // routine for making a matrix
            	int rB = buf[0] - '0';
            	int cB = buf[2] - '0';
            	mB = mread(stdin, &rB, &cB);

				mProduct = mmult(rA, cA, mA, rB, cB, mB); // store the product

				xfree(rA, mA);
				xfree(rB, mB);
				
				// Modify the col value for copying and copy the matrix into A
				cA = cB;

				mA = xalloc(rA, cA);
				for(int i = 0; i < rA; i++) {
					for(int j = 0; j < cA; j++) {
						mA[i][j] = mProduct[i][j];
					}
				}

				// Free the product now that it's in A
				xfree(rA, mProduct);
			}

			mwrite(stdout, rA, cA, mA);
			xfree(rA, mA);

		}
		
		// make sure all the memory is freed
		if(buf != NULL) free(buf);
		
	}
}
