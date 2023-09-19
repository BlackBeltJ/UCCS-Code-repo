/*
Joshua Edwards
CS 2060 003 AirUCCS Project Iteration 1
This program creates a system for user to view information about rental properties and 
then input the number of nights they want to rent the property for and receive an estimated
charge based on the number of nights and the discount rate. The owner of the property can 
also input a special value to receive back a summary of the nights rented and the total 
money made. 
*/

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

	// put valid input and sentinal value logic in main
	int userNightInput = 0;
	int totalNights = 0;
	int totalCharges = 0;

	while (userNightInput != SENTINAL_NEG1) {
		printRentalPropertyInfo(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);
		userNightInput = getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, SENTINAL_NEG1);
		double rentalCharge = calculateCharges(userNightInput, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);
		totalCharges = totalCharges + rentalCharge;
		totalNights = totalNights + userNightInput;
	}
	if (totalNights == 0 || totalCharges == 0)
	{
		puts("No nights and charges accrewed.");
	}
	else
	{
		printNightsCharges(totalNights, totalCharges);
	}
}

//Prints the rental property information 
void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int
	interval1Nights, unsigned int interval2Nights, double rate, double discount) {
	printf("Rental property can be rented for %d to %d nights", minNights, maxNights);
	printf("%lf rate a night for the first %d nights", rate, interval1Nights);
	printf("%lf discount rate a night for nights %d to %d", discount, interval1Nights, interval2Nights);
	printf("%lf discount rate a night for each remaining night over %d", (rate * 2), interval2Nights);
}

//returns only valid input from the user based on the min and max values inclusively
int getValidInt(int min, int max, int sentinal) {
	int userNightInput = 0;
	int scanfReturnValue = 0;

	// algorithm to check valid input
	bool isValidInput = false;
	while ((getchar() != '\n')); // clears the input buffer
	while (isValidInput == false)
	{
		puts("Enter the number of nights you want to rent the property: ");
		scanfReturnValue = scanf("%d", &userNightInput);
		while ((getchar() != '\n')); // clear the input buffer again

		if (scanfReturnValue == 1)
		{
			// if scanf returns a 1, that means that data was successfully read (the user entered an integer)
			// check input against acceptable range
			if (userNightInput >= min && userNightInput <= max)
			{
				isValidInput = true;
			}
			else
			{
				printf("Error: Not within %d and %d. Please enter the value again.\n ", min, max);
				isValidInput = false;
			}
		}
		else
		{
			// prompt the user for an integer again if they did not enter one initially
			puts("Error: Not an integer number. Please enter the value again.\n");
			isValidInput = false;
		}
	}
	return userNightInput;
}

//Calculates the charge based on the number of nights rented
double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int
	interval2Nights, double rate, double discount) {
	double charge = 0;

	// create math logic
	// base rate
	if (nights < interval1Nights) {
		charge += (nights * rate);
	}
	// reduced rate
	if (nights > interval2Nights) {
		charge += ((interval2Nights - interval1Nights) * (rate - discount));
	}
	else (nights <= interval2Nights); 
		charge += ((nights - interval1Nights) * (rate * discount));
	// double reduced rate
	if (nights > interval2Nights) {
		charge += ((nights - interval2Nights) * (rate - 2 * discount));
	}
	// need to increment charge as it's calculated
	return charge;
}

//Prints the number of nights, and the charge  if there were any rentals
//Use for printing  vacationer charge or for property owner summary
void printNightsCharges(unsigned int nights, double charges) {
	puts("Rental Property Owner Total Summary");
	printf("\n\nNights\tCharge\n%d\t%lf.2", nights, charges);
}


