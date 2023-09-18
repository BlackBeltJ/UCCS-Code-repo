#include <stdio.h>
#include <stdbool.h>
#include <math.h>

//Prints the rental property information 
void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int
	interval1Nights, unsigned int interval2Nights, double rate, double discount);

//returns only valid input from the user based on the min and max values inclusively
int getValidInt(int min, int max, int sentinal);

//Calculates the charge based on the number of nights rented
double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int
	interval2Nights, double rate, double discount);

//Prints the number of nights, and the charge  if there were any rentals
//Use for printing  vacationer charge or for property owner summary
void printNightsCharges(unsigned int nights, double charges);


int main(void) {
	int const SENTINAL_NEG1 = -1;
	int unsigned const MIN_RENTAL_NIGHTS = 1;
	unsigned int const MAX_RENTAL_NIGHTS = 14;
	unsigned int const INTERVAL_1_NIGHTS = 3;
	unsigned int const INTERVAL_2_NIGHTS = 6;
	double const RENTAL_RATE = 400;
	double const DISCOUNT = 50;

}

//Prints the rental property information 
void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int
	interval1Nights, unsigned int interval2Nights, double rate, double discount) {
	printf("Rental property can be rented for %d to %d nights", minNights, maxNights);
	printf("%d rate a night for the first %d nights", rate, interval1Nights);
	printf("%d discount rate a night for nights %d to %d", interval1Nights, interval2Nights);
	printf("%d discount rate a night for each remaining night over %d", (rate * 2), interval2Nights);
}

//returns only valid input from the user based on the min and max values inclusively
int getValidInt(int min, int max, int sentinal) {
	static int totalNights = 0;
	static double totalCharges = 0;
	int userNightInput = 0;

	puts("Enter the number of nights you want to rent the property: ");
	int scanfReturnValue = scanf("%d", &userNightInput);
	
	// algorithm to check valid input
	bool isValidInput = false;
	while ((getchar() != '\n')); // clears the input buffer
	while (isValidInput == false)
	{
		if (scanfReturnValue == 1)
		{
			// if scanf returns a 1, that means that data was successfully read (the user entered an integer)
					/* this is where I would check that the user entered in a valid value
					considering the range of acceptable values */
			while (isValidInput == false) 
				// NOTE TO SELF: need to flush out this control loop more
			{
				if (userNightInput < min || userNightInput > max) 
				{
					printf("Error: Not within %d and %d. Please enter the value again: ", min, max);
					scanfReturnValue = scanf("%d", &userNightInput);
					while ((getchar() != '\n')); // clear the input buffer again
				}
				else if (userNightInput == sentinal) 
				{
					if (totalNights == 0 || totalCharges == 0) 
					{
						puts("No nights / charges accrewed.");
					}
					printNightsCharges(totalNights, totalCharges);
					isValidInput = true;
				}
				else 
				{
					isValidInput = true;
				}
			}
		}
		else
		{
			// prompt the user for an integer again if they did not enter one initially
			puts("Error: Not an integer number. Please enter the value again.");
			scanfReturnValue = scanf("%d", &userNightInput);
			while ((getchar() != '\n')); // clear the input buffer again
		}
	}
	return userNightInput;
}

//Calculates the charge based on the number of nights rented
double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int
	interval2Nights, double rate, double discount) {

}

//Prints the number of nights, and the charge  if there were any rentals
//Use for printing  vacationer charge or for property owner summary
void printNightsCharges(unsigned int nights, double charges) {
	puts("Rental Property Owner Total Summary");
	printf("\n\nNights\tCharge\n%d\t%lf.2", nights, charges);
}


