// ahnentafel.c implements the conversions of numbers and genealogy!
// @author: exl2748 Erica LaBuono
// // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define MAXLENGTH 285

// mainMenu prints the main menu message when called. 
void mainMenu() {
	printf("\n1) description\n"
			"2) ahnentafel number (base 10)\n"
			"3) ahnentafel number (base 2)\n"
			"4) relation (e.g. mother's mother's father)\n"
			"5) exit\n\n> ");
}

// binaryToDecimal converts binary numbers to decimal numbers.
// @param num is a proper binary number stored as a string
// @return decimal is the converted, base 10 form
unsigned int binaryToDecimal(char binary[]) {
	unsigned int num = strtol(binary, NULL, 10);
	int decimal = 0, i = 0, remainder;
	while(num != 0) {
		remainder = num % 10;
		num = num/10;
		decimal += remainder*pow(2,i);
		i++;
	}
	return decimal;
}

// decimalToBinary converts decimal numbers into binary numbers
// adds the correct 0 or 1 remainder to the correct number place
// conversion ends when there are no more number places to fill
// @param decimal is a proper decimal stored as a string
// @return binary is converted result as unsigned integer 
unsigned int decimalToBinary(char decimal[]) {
	unsigned int num = strtol(decimal, NULL, 10);
	unsigned int binary = 0;

	int numPlace = 1;
	int remainder;
	while (num != 0) {
		remainder = num % 2;
		num = num/2;
		
		binary = binary + (remainder * numPlace); //stores 0 or 1 in the correct spot
		numPlace = numPlace * 10;
	}

	return binary;
	
}

// stringToBinary takes an input array and generates the matching binary
// using basic math starting from 1 and moving decimal places, adding 0 and 1s
// @param input is a valid string of family relations
unsigned int stringToBinary(char input[]) {
	char *token;
	unsigned int binary = 1; // we start at 1 for self
	token = strtok(input, " ");
	while (token != NULL) {
		if(strcmp(token, "mother's") == 0 || strcmp(token, "mother") == 0) {
			binary = binary * 10;
			binary = binary + 1; // add a one to the current decimal place instead of 0
		} else if (strcmp(token, "father's") == 0 || strcmp(token, "father") == 0) {
			binary = binary * 10;
		}
		
		token = strtok(NULL, " ");
	}
	return binary;
}

// checkFamilyString verifies that the input is a valid mom-dad-self string.
// @param input: a string taken from the user
// @return true if the string is valid, false otherwise
bool checkFamilyString(char input[]) {
	char inputCopy[MAXLENGTH]; // reserve the data in a new copy
	strncpy(inputCopy, input, MAXLENGTH);
	char *token;
	token = strtok(inputCopy, " ");
	while(token != NULL) {
		if (strcmp(token, "mother's") == 0 || strcmp(token, "mother") == 0 ||
			strcmp(token, "father's") == 0 || strcmp(token, "father") == 0 ||
			strcmp(token, "self") == 0) {
			// valid strings let us move on to the next token
		} else {
			return false;
		}
		token = strtok(NULL, " ");
	}
	return true;
}

// checkBinary takes a string and checks to see if it a valid binary number.
// @param input is a null-terminated string
// @return True if the string is a binary number, False otherwise
bool checkBinary(char input[]) {
	for (int j = 0; j < strlen(input); j++) {
		if (input[j] != '0' &&  input[j] != '1' && input[j] != 'b') {
			return false; // any other numbers are wrong, b is acceptable for binary numbers
		} 
	}
	return true;
}

// checkDecimal takes a string and checks to see if it is a decimal number.
// @param input is a null-terminated string
// @return True if decimal number, false otherwise
bool checkDecimal(char input[]) {
	unsigned int decimal = strtol(input, NULL, 10);
	for (int j = 0; j < strlen(input); j++) {
        if (input[j] == 'b') {
            return false; // b is acceptable for binary numbers only
        }
    }
	if (decimal == 0) { // if the string has no numbers, or is just 0
        return false;
    }
    return true;
}

// familyRelation takes a string of binary and prints the relationship
// @param binary is an array repping a proper binary number
void familyRelation(char binary[]) {
	unsigned int binaryNum = strtol(binary, NULL, 10);
	char binaryStrip[MAXLENGTH];
	sprintf(binaryStrip, "%u", binaryNum); // strips the b

	int length = strlen(binaryStrip);
	if (length > 2) { // anything greater than mother/father/self
		printf("family relation: ");
		for (int i = 1; i < (length - 1); i++) { // ignoring the 1st char, stopping before last
			if (binaryStrip[i] == '0') {
				printf("father\'s ");
			} else if (binaryStrip[i] == '1') {
				printf("mother\'s ");
			}
		}
		// last word has no apostrophe
		if (binaryStrip[length - 1] == '0') {
			printf("father\n");
		} else if (binaryStrip[length - 1] == '1') {
			printf("mother\n");
		}
	} else if (length == 2) {
		if (binaryStrip[1] == '0') {
			printf("family relation: father\n");
		} else if (binaryStrip[1] == '1') {
			printf("family relation: mother\n");
		}
	} else if (length == 1) {
		printf("self\n");
	}
}

// main handles user input for executing various functionality of ahnentafel
// when there are no command arguments, a menu is shown and waits for user
// the interaction closes when the user enters '5'
// when there are command arguments, the program reads in and determines the type
// of conversion necessary to give results to the user
// @param argc: num of arguments in argv
// @param argv: array of arguments
// @return EXIT_SUCCESS on complete run
int main(int argc, char* argv[]) {
	if (argc < 2) {
		char buff[MAXLENGTH];
		while (1) {
			mainMenu();
			fgets(buff, MAXLENGTH, stdin);

			if (strcmp(buff, "1\n") == 0) { 
				printf("The Ahnentafel number is used to determine the relation\n"
						"between an individual and each of his/her direct ancestors.\n");
			} else if (strcmp(buff, "2\n") == 0) {
				printf("Enter the ahnentafel number in base-10: ");
				char input[MAXLENGTH];
                fgets(input, MAXLENGTH, stdin);
				unsigned int decimal = strtol(input, NULL, 10);
				if (decimal != 0) { // testing if the string actually has numbers in it
					unsigned int binary = decimalToBinary(input);
					printf("ahnentafel number in binary: %u\n", binary);
					char binaryStr[MAXLENGTH];
					sprintf(binaryStr, "%u", binary); // turning it back to a string for conversion
					familyRelation(binaryStr);
					double generations = floor(log(decimal)/log(2.0));
                    printf("generations back: %.f\n", generations);
				} else {
					fprintf(stderr, "Invalid string!\n");
				}
			} else if (strcmp(buff, "3\n") == 0) {
				printf("Enter the ahnentafel number in binary: ");
				char input[MAXLENGTH];
				fgets(input, MAXLENGTH, stdin);

				unsigned int binaryStrip = strtol(input, NULL, 10);
				char binary[MAXLENGTH];
				sprintf(binary, "%u", binaryStrip);
				if (checkBinary(binary)) {
					if(binaryStrip == 0) {
						fprintf(stderr, "Invalid string!\n");
						continue;
					}
					unsigned int decimal = binaryToDecimal(binary);
					printf("base-10 value: %u\n", decimal);
					familyRelation(binary);
					double generations = floor(log(decimal)/log(2.0));
					printf("generations back: %.f\n", generations);
				} else {
					fprintf(stderr, "Invalid string!\n");
				}
			} else if (strcmp(buff, "4\n") == 0) {
				printf("Enter family relation (e.g.) \"father's mother\": ");
				char input[MAXLENGTH];
				fgets(input, MAXLENGTH, stdin);
				input[strcspn(input, "\n")] = 0; // removes the pesky \n character
				if (checkFamilyString(input)) {
					unsigned int binary = stringToBinary(input);
					printf("ahnentafel number in binary: %u\n", binary);

					char binaryStr[MAXLENGTH];
					sprintf(binaryStr, "%u", binary); // convert the binary into string
					unsigned int decimal = binaryToDecimal(binaryStr); //use string to get decimal
					printf("ahnentafel number in base-10: %u\n", decimal);
					double generations = floor(log(decimal)/log(2.0));
                    printf("generations back: %.f\n", generations);
				} else {
					fprintf(stderr, "Invalid string!\n");
				}
			} else if (strcmp(buff, "5\n") == 0) {
				printf("Goodbye.\n");
                return EXIT_SUCCESS;
			} else {
				fprintf(stderr, "Unknown operation!\n");
			}
		}
	} else if(argc >= 2) {
		char input[MAXLENGTH];
		strcpy(input, argv[1]);

		for (int i = 2; i < argc; i++) {
			strcat(input, " ");
			strcat(input, argv[i]);
		}

		if(!checkFamilyString(input)) {
			
			if (checkDecimal(input)) {
                unsigned int binary = decimalToBinary(input);
                printf("ahnentafel number in binary: %u\n", binary);
                char binaryStr[MAXLENGTH];
                sprintf(binaryStr, "%u", binary); // turning it back to a string for conversion
                familyRelation(binaryStr);

				unsigned int decimal = strtol(input, NULL, 10); // conversion for gen math
                double generations = floor(log(decimal)/log(2.0));
                printf("generations back: %.f\n", generations);
                return EXIT_SUCCESS;
            } else if (checkBinary(input)) {
				unsigned int decimal = binaryToDecimal(input);
                printf("base-10 value: %u\n", decimal);
                familyRelation(input);
                double generations = floor(log(decimal)/log(2.0));
                printf("generations back: %.f\n", generations);
				return EXIT_SUCCESS;
			}

			fprintf(stderr, "Invalid string!\n");
			return EXIT_FAILURE;
		} else if (checkFamilyString(input)) {
			unsigned int binary = stringToBinary(input);
            printf("ahnentafel number in binary: %u\n", binary);
            char binaryStr[MAXLENGTH];
            sprintf(binaryStr, "%u", binary); // convert the binary into string
            unsigned int decimal = binaryToDecimal(binaryStr); //use string to get decimal
            printf("ahnentafel number in base-10: %u\n", decimal);
            double generations = floor(log(decimal)/log(2.0));  
            printf("generations back: %.f\n", generations);
			return EXIT_SUCCESS;
		} else {
			fprintf(stderr, "Invalid string!\n");			
		}	
	}

}
