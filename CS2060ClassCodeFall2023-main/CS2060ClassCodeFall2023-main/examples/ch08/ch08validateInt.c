
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define LENGTH 20

void  exploreValidateInt(const char* buff);
bool validateInt(char* buff, int* const validInt);
void printLimits();

int main(void)
{
	char inputStr[LENGTH]; // create char arintray
	size_t inputLength = 0;

	printLimits();

	for (unsigned int counter = 1; counter < 6; counter++)
	{
		puts("\nEnter an integer");
		fgets(inputStr, LENGTH, stdin);
		if (inputStr[(strlen(inputStr) - 1)] == '\n') { // first check to see if there is a newline char \n at end of string
			inputStr[strlen(inputStr) - 1] = '\0'; // if there is a newline char, replace it with a null char \0
		}
		exploreValidateInt(inputStr);
	}

}



void printLimits()
{
	printf("The number of bits in a byte %d\n", CHAR_BIT);

	printf("The minimum value of SIGNED CHAR = %d\n", SCHAR_MIN);
	printf("The maximum value of SIGNED CHAR = %d\n", SCHAR_MAX);
	printf("The maximum value of UNSIGNED CHAR = %d\n", UCHAR_MAX);

	printf("The minimum value of SHORT INT = %d\n", SHRT_MIN);
	printf("The maximum value of SHORT INT = %d\n", SHRT_MAX);

	printf("The minimum value of INT = %d\n", INT_MIN);
	printf("The maximum value of INT = %d\n", INT_MAX);

	printf("The minimum value of CHAR = %d\n", CHAR_MIN);
	printf("The maximum value of CHAR = %d\n", CHAR_MAX);

	printf("The minimum value of LONG = %ld\n", LONG_MIN);
	printf("The maximum value of LONG = %ld\n", LONG_MAX);
}


void  exploreValidateInt(const char* buff)
{
	char* end = NULL;
	errno = 0;
	int validInt = 0;
	long intTest = strtol(buff, &end, 10); // stops when hits non-integer character
	if (end == buff) {
		fprintf(stderr, "%s: not a decimal number\n", buff);
	}
	else if ('\0' != *end) { // 
		fprintf(stderr, "%s: extra characters at end of input: %s\n", buff, end);
	}
	else if ((LONG_MIN == intTest || LONG_MAX == intTest) && ERANGE == errno) {
		fprintf(stderr, "%s out of range of type long\n", buff);
	}
	else if (intTest > INT_MAX) {
		fprintf(stderr, "%ld greater than INT_MAX\n", intTest);
	}
	else if (intTest < INT_MIN) {
		fprintf(stderr, "%ld less than INT_MIN\n", intTest);
	}
	else {
		validInt = (int)intTest;
		printf("%d is integer value ", validInt);
	}// needs to return integer value
}
