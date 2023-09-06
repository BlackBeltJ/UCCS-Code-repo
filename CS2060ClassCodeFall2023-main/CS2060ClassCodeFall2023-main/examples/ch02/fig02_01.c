// fig02_01.c
// A first program in C.
#include <stdio.h>
#include <stdbool.h>

// function declarations
double calculateArea(double length, double width);

// function main begins program execution 
int main(void) {
	int length = 0;
	int width = 0;
	int area = 0;
	int scanfReturn = 0;
	int scanfReturn2 = 0;

	puts("Enter the length: ");
	// printf("%s", "Enter the length");
	scanfReturn = scanf("%d", &length);

	// algorithm to check valid input
	bool isValidInput = false;
	while ((getchar() != '\n')); // clears the input buffer
	while (isValidInput == false)
	{
		if (scanfReturn == 1)
		{
			// if scanf returns a 1, that means that data was successfully read (the user entered an integer)
			/* this is where I would check that the user entered in a valid value
			considering the range of acceptable values,	but for the purposes of
			this GE, I am only concerned with checking if the user entered in the
			correct data type */
			isValidInput = true;
		}
		else
		{
			// prompt the user for an integer again if they did not enter one initially
			puts("Please enter an integer, try again.");
			scanfReturn = scanf("%d", &length);
			while ((getchar() != '\n')); // clear the input buffer again
		}
	}

	puts("Enter the width: ");
	scanfReturn2 = scanf("%d", &width);

	// algorithm to check valid input
	isValidInput = false;
	while ((getchar() != '\n')); // clears the input buffer
	while (isValidInput == false)
	{
		if (scanfReturn2 == 1)
		{
			// if scanf returns a 1, that means that data was successfully read (the user entered an integer)
			/* this is where I would check that the user entered in a valid value
			considering the range of acceptable values,	but for the purposes of
			this GE, I am only concerned with checking if the user entered in the
			correct data type */
			isValidInput = true;
		}
		else
		{
			// prompt the user for an integer again if they did not enter one initially
			puts("Please enter an integer, try again.");
			scanfReturn2 = scanf("%d", &width);
			while ((getchar() != '\n')); // clear the input buffer again
		}
	}

	// calculate area and display values
	area = width * length;
	printf("Length: %d, Width: %d, and the area is: %d", length, width, area);

	// calculate average as double
	double averageResult = (double) (length + width) / 2;
	printf("\nAverage of length and width: %.1f", averageResult);

	// call function to calculate DOUBLE area
	area = calculateArea(length, width);
	printf("\nArea from main: %d\n\n", area);

	return 0;
    // printf("Welcome to C!\n");
} // end function main 

// function calculateArea takes length and width and returns the double area
double calculateArea(double length, double width) 
{
	double area = (double) (length * width);
	// the "%lf" format specifier tells the function to format to a double
	printf("\n\nArea from function: %lf", area); 
	return area;
}// end of calculateArea function

/**************************************************************************
 * (C) Copyright 1992-2021 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
