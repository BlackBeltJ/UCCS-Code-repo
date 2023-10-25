/*
Joshua Edwards
CS 2060 003 AirUCCS Project Iteration 2
Made on Windows 10
This program creates a system for user to view information about rental properties and
then input the number of nights they want to rent the property for and receive an estimated
charge based on the number of nights and the discount rate. The owner of the property can
also input a special value to receive back a summary of the nights rented and the total
money made.

UPDATE THIS DESCRIPTION.
*/

#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

//Maximum length of a string
#define STRING_LENGTH 80
//Two dimensional array storage amounts for rows and columns of surve data
#define VACATION_RENTERS 5
#define RENTER_SURVEY_CATEGORIES 3
//Rental property rating ranges
#define MINRATING 1
#define MAXRATING 5
//Rental property login and sentinal values
#define CORRECT_ID "id1"
#define CORRECT_PASSCODE "ABCD"
#define LOGIN_MAX_ATTEMPTS 3
#define SENTINAL_NEG1 -1
//rental property constant ranges
#define MIN_RENTAL_NIGHTS 1
#define MAX_RENTAL_NIGHTS 14
#define MIN_RATE 1
#define MAX_RATE 1000
#define DISCOUNT_MULTIPLIER 2

// Defining property structure
// can be declared using the 'Property" tag
typedef struct property {
	int minimumNights;
	int maximumNights;
	int interval1Nights;
	int interval2Nights;
	double minimumRate;
	double maximumRate;
	double rate;
	double discount;

	char name[STRING_LENGTH];
	char location[STRING_LENGTH];
} Property;

//Prints the rental property information 
void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int
	interval1Nights, unsigned int interval2Nights, double rate, double discount);

//returns only valid input from the user based on the min and max values inclusively
int getValidIntSentinal(int min, int max, int sentinal);
// bool scanIntSentinal(const char* const stringInput, int min, int max, int* const integerPtr, int sentinal);

//Calculates the charge based on the number of nights rented
double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int
	interval2Nights, double rate, double discount);
//Prints the number of nights, and the charge  if there were any rentals
//Use for printing vacationer charge or for property owner summary
void printNightsCharges(unsigned int nights, double charges);


// functions for ratings
void printCategories(const char* categories[RENTER_SURVEY_CATEGORIES], size_t totalCategories);
void getRatings(int rentalSurvey[][RENTER_SURVEY_CATEGORIES], size_t renters_rows, size_t category_columns, int MIN_RATING, int MAX_RATING);

int getValidInt(int MIN_RATING, int MAX_RATING);
void removeNewLine(char* stringPtr, int size);
bool scanInt(const char* const stringInput, int min, int max, int* const integerPtr);

void printSurveyResults(const int rentalSurvey[][RENTER_SURVEY_CATEGORIES], size_t renters_rows, size_t category_columns, int MIN_RATING, int MAX_RATING);
void calculateCategoryAverages(int rentalSurvey[][RENTER_SURVEY_CATEGORIES], double categoryAverages[RENTER_SURVEY_CATEGORIES], size_t renters_rows, size_t ratings_columns);
void printCategoryData(const double categoryAverages[RENTER_SURVEY_CATEGORIES], size_t totalCategories);

// functions for property setup (structure)
void initializeDefaultPropertyVals(Property* prop, const int minNights, const int maxNights, const double minRate, const double maxRate);
void setUpProperty(Property* prop);
void displayOrganization(const Property prop);

// main function
int main(void) {
	// constants
	unsigned int INTERVAL_1_NIGHTS = 0;
	unsigned int INTERVAL_2_NIGHTS = 0;
	double RENTAL_RATE = 0;
	double DISCOUNT = 0;

	unsigned int userNightInput = 0; // NOTE TO SELF: change this to unsigned throughout program
	unsigned int totalNights = 0; // NOTE TO SELF: change this to unsigned throughout program
	double totalCharges = 0;
	
	// rating survey initializations
	double categoryAverages[RENTER_SURVEY_CATEGORIES];
	int rentalSurvey[VACATION_RENTERS][RENTER_SURVEY_CATEGORIES];
	const char* surveyCategories[RENTER_SURVEY_CATEGORIES] = { "Check-in Process", "Cleanliness", "Amenities" };
	
	// initialize arrays with 0s
	// 1D array
	for (size_t i = 0; i < RENTER_SURVEY_CATEGORIES; i++) {
		categoryAverages[i] = 0;
	}
	// 2D array
	for (size_t row = 0; row < VACATION_RENTERS; row++) {
		for (size_t column = 0; column < RENTER_SURVEY_CATEGORIES; column++) {
			rentalSurvey[row][column] = 0;
		}
	}

	// add static counter to tell function what row to start writing data to (getRating function)

	Property property1;

	// TODO: need to re-work main logic and program flow
	while (userNightInput != SENTINAL_NEG1) {
		printRentalPropertyInfo(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);
		userNightInput = getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, SENTINAL_NEG1);
		if (userNightInput != SENTINAL_NEG1) // the purpose of this loop is to prevent the sentinal value from being written into the totalCharges and totalNights before the while loop comes back around and breaks
		{
			double rentalCharge = calculateCharges(userNightInput, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);
			totalCharges = totalCharges + rentalCharge;
			totalNights = totalNights + userNightInput;
		}
	} // this is for when there are no rentals and the owner wants a summary
	if (totalNights == 0 || totalCharges == 0)
	{
		puts("\nThere were no rentals...Exiting program");
	}
	else
	{
		printNightsCharges(totalNights, totalCharges);
	}
}

//Prints the rental property information 
void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int
	interval1Nights, unsigned int interval2Nights, double rate, double discount) {
	// %.2f is rounding to 2 decimal places
	printf("\n\nRental property can be rented for %d to %d nights", minNights, maxNights);
	printf("\n%.2f rate a night for the first %d nights", rate, interval1Nights);
	printf("\n%.2f discount rate a night for nights %d to %d", discount, (interval1Nights + 1), interval2Nights);
	printf("\n%.2f discount rate a night for each remaining night over %d.\n", (discount * 2), interval2Nights);
}

//returns only valid input from the user based on the min and max values inclusively
int getValidIntSentinal(int min, int max, int sentinal) {
	int integer = 0;

	bool isValidInput = scanInt(;
	// puts("\nEnter the number of nights you want to rent the property: ");
	
	
	return integer; // this function will always return a valid integer 
}

//Calculates the charge based on the number of nights rented
double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int
	interval2Nights, double rate, double discount) {
	double charge = 0;

	/* 
	This algorithm assume that the user is not getting any discount by calculating the charge using the base rent. Then the program will
	test the night input to see if the user is getting any discount. If the user does qualify for a discount, the program will SUBTRACT 
	the respective discount depending on how many nights the user entered. 
	*/

	// base case nights is less than interval 1
	charge = nights * rate; 
	// second case nights are between interval 1 and 2 (standard discount)
	if (nights > interval1Nights) { 
		if (nights > interval2Nights) 
		{
			// if nights is greater than interval 2, in other words if the user is maximizing their basic discount
			charge = charge - ((interval2Nights - interval1Nights) * discount);
		}
		else {
			// if the user is between interval 1 and interval 2
			charge = charge - ((nights - interval1Nights) * discount);
		}
	}
	// third case nights are over interval 2 (double discount)
	if (nights > interval2Nights) { 
		charge = charge - ((nights - interval2Nights) * (discount * 2));
	}
	printf("\nNights\t\tCharge\n%d\t\t$%.2f", nights, charge);
	return charge;
}

//Prints the number of nights, and the charge  if there were any rentals
//Use for printing  vacationer charge or for property owner summary
void printNightsCharges(unsigned int nights, double charges) {
	puts("\nRental Property Owner Total Summary");
	printf("\nNights\tCharge\n%d\t$%.0f\n", nights, charges);
}



// rating functions
// insert function definitions here
void printCategories(const char* categories[RENTER_SURVEY_CATEGORIES], size_t totalCategories)
{
	//loop to display each category horizontally
	printf("%s", "\n\nRating Categories:\t");
	for (size_t surveyCategory = 0; surveyCategory < totalCategories; ++surveyCategory)
	{
		printf("\t%zu.%s\t", surveyCategory + 1, categories[surveyCategory]);
	}
	puts(""); // start new line of output
}

// this function will get ratings from the renters and fill the 2D array with those ratings
void getRatings(int rentalSurvey[][RENTER_SURVEY_CATEGORIES], size_t renters_rows, size_t category_columns, int min_rating, int max_rating) {
	static int nextIndexForRating = 0; // static counter to tell function what row to start writing data to in array from function call to function call

	//printf("\n\tRenter %d:", nextIndexForRating); // use static variable so we know exactly where to jump back into the array to write the next ratings
	
	if (nextIndexForRating < renters_rows) {
		for (size_t category = 0; category < category_columns; category++)
		{
			// ask user for each rating	
			printf("\nEnter your rating for \nCategory %d: ", (int)(category + 1)); // category + 1 because the category index starts at 0 and I want renters to start at 1
			// verify valid integer
			int rating = getValidInt(min_rating, max_rating);
			// write data back to array
			rentalSurvey[nextIndexForRating][category] = rating;
		}
		nextIndexForRating++;
	}
	else {
		puts("Array full!");
	}
	
} // end of function

// this function will always return a valid rating 
int getValidInt(int MIN_RATING, int MAX_RATING) {
	int input = 0;
	bool isValidInput = false;

	// algorithm to check valid input
	int scanfReturnValue = scanf("%d", &input); // read input to "input" variable (& is address operator (pass by reference))
	while ((getchar() != '\n')); // clears the input buffer
	while (isValidInput == false)
	{
		if (scanfReturnValue == 1)
		{
			// if scanf returns a 1, that means that data was successfully read (the user entered an integer)
			// check range
			if ((input >= MIN_RATING) && (input <= MAX_RATING)) {
				isValidInput = true; // if the user entered an integer within the valid range
			}
			else // the user entered an integer but not in valid range
			{
				printf("Not between %d and %d, please try again: ", MIN_RATING, MAX_RATING);
				isValidInput = false;

				scanfReturnValue = scanf("%d", &input); // prompt user again
				// read input to "input" variable (& is address operator (pass by reference))
				while ((getchar() != '\n')); // clears the input buffer
			}
		}
		else // user did not enter an integer
		{
			puts("Not an integer, please try again: "); // prompt the user again
			scanfReturnValue = scanf("%d", &input); // read input to "input" variable (& is address operator (pass by reference))
			while ((getchar() != '\n')); // clear the input buffer again
		}
	}
	return input; // function will always returen valid input
}

// this function displays the results of the rating data to the console (reads through 2D array)
void printSurveyResults(const int rentalSurvey[][RENTER_SURVEY_CATEGORIES], size_t renters_rows, size_t category_columns, int min_rating, int max_rating) {
	// loop through array and display the each row and column
	for (size_t renter = 0; renter < renters_rows; renter++) {
		printf("\nSurvey %d: ", (int)(renter + 1)); // row + 1 because index starts at 0 and we want to start at 1
		for (size_t category = 0; category < category_columns; category++) {
			printf("\t%d", rentalSurvey[renter][category]); // print each rating
		}
	}
}

// this function reads through the 2D rating array and calculates the average rating for each category and writes it to the categoryAverages array
void calculateCategoryAverages(int rentalSurvey[][RENTER_SURVEY_CATEGORIES], double categoryAverages[RENTER_SURVEY_CATEGORIES], size_t renters_rows, size_t category_columns) {
	// read integers from each row and calculate average
	// loop through 2D rentalSurvey array and get sum total of each category
	for (size_t category = 0; category < category_columns; category++)
	{
		int sum = 0;
		for (size_t renter = 0; renter < renters_rows; renter++)
		{
			sum += rentalSurvey[renter][category]; // add each rating to total sum
		}
		// divide sum by amount of renters to get average
		double average = ((double)sum / (double)renters_rows); // parse everything to double so there is no loss of data during the calculation
		// store average in categoryAverages array
		categoryAverages[category] = average;
	}
}



// setup property functions
void initializeDefaultPropertyVals(Property* prop, const int minNights, const int maxNights, const double minRate, const double maxRate) {
	prop->minimumNights = minNights;
	prop->maximumNights = maxNights;
	prop->minimumRate = minRate;
	prop->maximumRate = maxRate;
}

void setUpProperty(Property* propertyPtr) {
	// read numeric values using scanf
	// use fgets to read string info
	puts("Set up rental property information");

	puts("Enter the number of nights until first discount: ");
	scanf("%d", &propertyPtr->interval1Nights); // use & because passing primative datatype
	while ((getchar() != '\n'));
	puts("Enter the number of nights until second discount: ");
	scanf("%d", &propertyPtr->interval2Nights);
	while ((getchar() != '\n'));
	puts("Enter the nightly rental rate: ");
	scanf("%lf", &propertyPtr->rate);
	while ((getchar() != '\n'));
	puts("Enter the discount: ");
	scanf("%lf", &propertyPtr->discount);
	while ((getchar() != '\n'));

	puts("Enter the property name: ");
	fgets(propertyPtr->name, STRING_LENGTH, stdin); // dont need & because passing array which already holds address
	puts("Enter the property location: ");
	fgets(propertyPtr->location, STRING_LENGTH, stdin);
}

void displayOrganization(const Property prop) {
	printf("\nName: %s", prop.name);
	printf("Location: %s", prop.location);
	printf("Rental Property can be rented for %d to %d nights.", prop.interval1Nights, prop.interval2Nights);
	printf("\n%.2f rate a night for the first %d nights", prop.rate, prop.interval1Nights);
	printf("\n%.2f discount rate a night for nights %d to %d", prop.discount, prop.interval1Nights, prop.interval2Nights);
	printf("\n%.2f discount rate a night for each remaining night over %d.", (prop.discount * 2), prop.interval2Nights);
}

// getInt starts the process of getting a valid integer, calls getValidIntNEW during function excecution
int getInt(int min, int max) {
	char inputStr[STRING_LENGTH];
	int integer = 0;
	bool isValidInt = false;

	puts("\nEnter an integer: ");
	fgets(inputStr, STRING_LENGTH, stdin);
	removeNewLine(inputStr, strlen(inputStr));
	//if (inputStr[(strlen(inputStr) - 1)] == '\n') { // first check to see if there is a newline char \n at end of string
	//	inputStr[strlen(inputStr) - 1] = '\0'; // if there is a newline char, replace it with a null char \0
	//}
	// bool validReturnVal = scanInt(inputStr, MAX_RENTAL_NIGHTS, MIN_RENTAL_NIGHTS, &integer);
	while (!isValidInt) {
		if (!(scanInt(inputStr, max, min, &integer))) {
			puts("Invalid input, try again: ");
			fgets(inputStr, STRING_LENGTH, stdin);
			removeNewLine(inputStr, strlen(inputStr));
		}
		else {
			if ((integer < min) || (integer > max)) {
				printf("Value in integer: %d", integer);
				return integer;
			}
			else {
				printf("Not between %d and %d. Try again. ", min, max);
			}
		}
	}
}

// getInt starts the process of getting a valid integer, calls getValidIntNEW during function excecution
int getIntSentinal(int min, int max, int sentinal) {
	char inputStr[STRING_LENGTH];
	int integer = 0;
	bool isValidInt = false; 

	puts("\nEnter an integer: ");
	fgets(inputStr, STRING_LENGTH, stdin);
	removeNewLine(inputStr, strlen(inputStr));
	//if (inputStr[(strlen(inputStr) - 1)] == '\n') { // first check to see if there is a newline char \n at end of string
	//	inputStr[strlen(inputStr) - 1] = '\0'; // if there is a newline char, replace it with a null char \0
	//}

	// bool validReturnVal = scanInt(inputStr, MAX_RENTAL_NIGHTS, MIN_RENTAL_NIGHTS, &integer);
	while (!isValidInt) {
		if (!(scanInt(inputStr, max, min, &integer))) {
			puts("Invalid input, try again: ");
			fgets(inputStr, STRING_LENGTH, stdin);
			removeNewLine(inputStr, strlen(inputStr));
		}
		else {
			if ((integer == sentinal) || ((integer < min) || (integer > max))) {
				printf("Value in integer: %d", integer);
				return integer;
			}
			else {
				printf("Not between %d and %d. Try again. ", min, max);
			}
		}
	}
}

// function takes in a character array (string) and removes the newline character from the end of if it exists
void removeNewLine(char* stringPtr, int size) {
	if (stringPtr[(size - 1)] == '\n') { // first check to see if there is a newline char \n at end of string
		stringPtr[size - 1] = '\0'; // if there is a newline char, replace it with a null char \0
	}
}

// function returns true if valid integer (stringInput) was read to variable (var that integerPtr points to) and false otherwise
bool scanInt(const char* const stringInput, int max, int min, int* const integerPtr) {

	char* end = NULL;
	errno = 0;
	long intTest = strtol(stringInput, &end, 10); // stops when hits non-integer character
	//// if any of the following conditions return true (if any of the checks do not pass), then the if statement will pass over and continu to the else. 
	//// the only way to enter the if statement and return true is if every single one of the conditions are met
	//if (!(end == stringInput) && !('\0' != *end) && !((LONG_MIN == intTest || LONG_MAX == intTest) && ERANGE == errno) && !(intTest > max) && !(intTest < min)) {
	//	*integerPtr = (int)intTest;
	//	// puts("getValidInt return val: true");
	//	return true;
	//}
	//else {
	//	// default return value is false. Will only return true if non of the if or else if statements were initiated 
	//	// puts("getValidInt return val: false");
	//	return false;
	//}

	if (end == stringInput) { // checks to see if the pointer end was moved from it's original position (if it found a leading decimal)
		fprintf(stderr, "%s: not a decimal number\n", stringInput);
	}
	else if ('\0' != *end) { // checks to see if the pointer end is pointing to a null character which would mean strtol read through the whole string and ended without finding a non-decimal character
		fprintf(stderr, "%s: extra characters at end of input: %s\n", stringInput, end);
	}
	else if ((LONG_MIN == intTest || LONG_MAX == intTest) && ERANGE == errno) {	// checks to see if the value entered was too large or too small for the long type, and checks for errno value to see if user entered max or min value exactly
		printf("ERANGE: %d", ERANGE);
		printf("errno: %d", errno);
		printf(stderr, "%s out of range of type long\n", stringInput);
	}
	else if (intTest > INT_MAX) { // checks to see if value entered is too large for the int datatype
		fprintf(stderr, "%ld greater than INT_MAX\n", intTest);
	}
	else if (intTest < INT_MIN) { // checks to see if value entered is too small for the int datatype
		fprintf(stderr, "%ld less than INT_MIN\n", intTest);
	}
	else { // if all the tests were passed, this means the value entered is a valid integer
		*integerPtr = (int)intTest;
		return true;
		// printf("%d is integer value ", *integerPtr);
	}
	return false;
}