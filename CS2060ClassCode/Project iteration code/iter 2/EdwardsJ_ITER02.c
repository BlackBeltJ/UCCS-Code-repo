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

	int numOfRenters;
	int totalNights;
	double totalCharges;

	int rentalSurvey[VACATION_RENTERS][RENTER_SURVEY_CATEGORIES];
	double categoryAverages[RENTER_SURVEY_CATEGORIES];

	char name[STRING_LENGTH];
	char location[STRING_LENGTH];
} Property;

//Prints the rental property information 
void displayRentalPropertyInfo(const Property* propStrucPtr, unsigned int minNights, unsigned int maxNights, int discountMult);
//Calculates the charge based on the number of nights rented
double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount);
//Prints the number of nights, and the charge  if there were any rentals
//Use for printing vacationer charge or for property owner summary
void printNightsCharges(const Property* propStrucPtr);

// login function
bool isLoggedIn(const char* correctID, const char* correctPassword, const unsigned int allowedAttempts, int STR_LEN);
// rental mode logic function
void rentalMode(Property* currentPropertyPtr, const int minRating, const int maxRating, size_t rows, size_t columns, const int discountMultiplier, const int sentinal, const char* correctID, const char* correctPassword, int allowedAttempts, size_t STR_LEN);

// functions for ratings
void printCategories(const char* categories[RENTER_SURVEY_CATEGORIES], size_t totalCategories);
void getRatings(Property* propStrucPtr, size_t renters_rows, size_t category_columns, int min_rating, int max_rating);
void printSurveyResults(const Property* propStrucPtr, size_t renters_rows, size_t category_columns, int min_rating, int max_rating);
void calculateCategoryAverages(Property* propStrucPtr, size_t renters_rows, size_t category_columns);
void displaySurveyAverages(const Property* propStrucPtr, size_t total_categories);
//void printCategoryData(const double categoryAverages[RENTER_SURVEY_CATEGORIES], size_t totalCategories);

// getting input functions
//int getValidIntSentinal(int min, int max, int sentinal);
int getValidInt(int MIN_RATING, int MAX_RATING);
void removeNewLine(char* stringPtr, int size);
bool scanInt(const char* const stringInput, int min, int max, int* const integerPtr);

// functions for property setup (structure)
void initializeDefaultPropertyVals(Property* prop, const int minNights, const int maxNights, const double minRate, const double maxRate);
void setUpProperty(Property* propertyPtr, int STR_SIZE, const int minNights, const int maxNights, const double minRate, const double maxRate);
void displayOrganization(const Property* propStrucPtr, const int minNights, const int maxNights, const int discountMult);

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

	// main main logic and program flow
	rentalMode(&property1, MINRATING, MAXRATING, VACATION_RENTERS, RENTER_SURVEY_CATEGORIES, DISCOUNT_MULTIPLIER, SENTINAL_NEG1, CORRECT_ID, CORRECT_PASSCODE, LOGIN_MAX_ATTEMPTS, STRING_LENGTH);
	
	// this is for when there are no rentals and the owner wants a summary
	if (property1.totalNights == 0 || property1.totalCharges == 0)
	{
		puts("\nThere were no rentals...Exiting program");
	}
	else
	{
		printNightsCharges(&property1);
	}
}


// mathy functons
// ================================================================================================

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

// this function reads through the 2D rating array and calculates the average rating for each category and writes it to the categoryAverages array
void calculateCategoryAverages(Property* propStrucPtr, size_t renters_rows, size_t category_columns) {
	// read integers from each row and calculate average
	// loop through 2D rentalSurvey array and get sum total of each category
	for (size_t category = 0; category < category_columns; category++)
	{
		int sum = 0;
		for (size_t renter = 0; renter < renters_rows; renter++)
		{
			sum += propStrucPtr->rentalSurvey[renter][category]; // add each rating to total sum
		}
		// divide sum by amount of renters to get average
		double average = ((double)sum / (double)renters_rows); // parse everything to double so there is no loss of data during the calculation
		// store average in categoryAverages array
		propStrucPtr->categoryAverages[category] = average;
	}
}

// ================================================================================================


// login function
// ================================================================================================

bool isLoggedIn(const char* correctID, const char* correctPassword, const unsigned int allowedAttempts, const int STR_LEN) {
	char id[] = { "Default ID"};
	char password[] = { "Default password" };
	puts("AirUCCS Rental Property Owner Login");
	bool isMatch = false;
	int attempts = 0;

	while ((isMatch != true) || (attempts <= allowedAttempts)) {
		puts("Enter your AirUCCS ID: ");
		fgets(id, STR_LEN, stdin);

		puts("Enter your AirUCCS password: ");
		fgets(password, STR_LEN, stdin);

		if (id != correctID) {
			puts("The ID is incorrect");
		}
		else if (password != CORRECT_ID) {
			puts("The password is incorrect");
		}
		else if ((id == correctID) && (password == correctPassword)) {
			puts("Logging in...");
			isMatch = true;
		}
		else {
			attempts++;
			printf("Try again. Tries remaining: %d", (allowedAttempts - attempts));
		}
	}
	return isMatch;
}

// ================================================================================================


// rental mode logic function
// ================================================================================================

void rentalMode(Property* currentPropertyPtr, const int minRating, const int maxRating, size_t rows, size_t columns, const int discountMultiplier, const int sentinal, const char* correctID, const char* correctPassword, int allowedAttempts, size_t STR_LEN) {
	bool sentinalEntered = false;
	
	do {
		displayRentalPropertyInfo(currentPropertyPtr, minRating, maxRating, discountMultiplier);
		printSurveyResults(currentPropertyPtr, rows, columns, minRating, maxRating);
		puts("Enter the number nights. ");
		int nightInput = getValidIntSentinal(currentPropertyPtr->minimumNights, currentPropertyPtr->maximumNights, sentinal);

		if (nightInput == sentinal) {
			if (isLoggedIn(correctID, correctPassword, allowedAttempts, STR_LEN)) { // add isLoggedIn parameters here...
				sentinalEntered = true;
			}
		}
		else {
			// incremement totalNights
			double charge = calculateCharges(nightInput, currentPropertyPtr->interval1Nights, currentPropertyPtr->interval2Nights,
				currentPropertyPtr->rate, currentPropertyPtr->discount);

			currentPropertyPtr->totalCharges += charge;
			currentPropertyPtr->totalNights += nightInput;
		}
	} while (!sentinalEntered);
}

// ================================================================================================


// rating functions
// ================================================================================================

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
void getRatings(Property* propStrucPtr, size_t renters_rows, size_t category_columns, int min_rating, int max_rating) {
	unsigned int nextIndexForRating = propStrucPtr->numOfRenters; 
	
	if (nextIndexForRating < renters_rows) {
		for (size_t category = 0; category < category_columns; category++)
		{
			// ask user for each rating	
			printf("\nEnter your rating for \nCategory %d: ", (int)(category + 1)); // category + 1 because the category index starts at 0 and I want renters to start at 1
			// verify valid integer
			int rating = getValidInt(min_rating, max_rating);
			// write data back to array
			propStrucPtr->rentalSurvey[nextIndexForRating][category] = rating;
		}
		(propStrucPtr->numOfRenters)++;
	}
	else {
		puts("Array full!");
	}
} // end of function

// this function displays the results of the rating data to the console (reads through 2D array)
void printSurveyResults(const Property* propStrucPtr, size_t renters_rows, size_t category_columns, int min_rating, int max_rating) {
	// loop through array and display the each row and column
	for (size_t renter = 0; renter < renters_rows; renter++) {
		printf("\nSurvey %d: ", (int)(renter + 1)); // row + 1 because index starts at 0 and we want to start at 1
		for (size_t category = 0; category < category_columns; category++) {
			printf("\t%d", propStrucPtr->rentalSurvey[renter][category]); // print each rating
		}
	}
}

//Prints the number of nights, and the charge  if there were any rentals
//Use for printing  vacationer charge or for property owner summary
void printNightsCharges(const Property* propStrucPtr) {
	puts("\nRental Property Owner Total Summary");
	printf("\nNights\tCharge\n%d\t$%.0f\n", propStrucPtr->totalNights, propStrucPtr->totalCharges);
}

void displaySurveyAverages(const Property* propStrucPtr, size_t total_categories) {
	// this function prints the average of each category
	// iterate through categoryAverages array and display results
	printf("%s", "\nRating averages:");
	for (size_t category = 0; category < total_categories; category++) {
		printf("\t\t%.2f", propStrucPtr->categoryAverages[category]);
	}
}

// ================================================================================================


// property functions
// ================================================================================================

void initializeDefaultPropertyVals(Property* prop, const int minNights, const int maxNights, const double minRate, const double maxRate) {
	prop->minimumNights = minNights;
	prop->maximumNights = maxNights;
	prop->minimumRate = minRate;
	prop->maximumRate = maxRate;
	prop->numOfRenters = 0;
}

void setUpProperty(Property* propertyPtr, int STR_SIZE, const int minNights, const int maxNights, const double minRate, const double maxRate) {
	// use fgets to read string info
	puts("Set up rental property information");

	puts("Enter the number of nights until first discount: ");
	propertyPtr->interval1Nights = getValidInt(minNights, maxNights); // use & because passing primative datatype
	//while ((getchar() != '\n'));
	puts("Enter the number of nights until second discount: ");
	propertyPtr->interval2Nights = getValidInt(propertyPtr->interval1Nights, maxNights);

	puts("Enter the nightly rental rate: ");
	propertyPtr->rate = getValidInt(minRate, maxRate);

	puts("Enter the discount: ");
	propertyPtr->rate = getValidInt(minRate, maxRate);

	puts("Enter the property name: ");
	fgets(propertyPtr->name, STR_SIZE, stdin); // dont need & because passing array which already holds address
	puts("Enter the property location: ");
	fgets(propertyPtr->location, STR_SIZE, stdin);
}

void displayOrganization(const Property* propStrucPtr, const int minNights, const int maxNights, const int discountMult){
	printf("\nName: %s", propStrucPtr->name);
	printf("Location: %s", propStrucPtr->location);
	printf("Rental Property can be rented for %d to %d nights.", minNights, maxNights);
	printf("\n%.2f rate a night for the first %d nights", propStrucPtr->rate, propStrucPtr->interval1Nights);
	printf("\n%.2f discount rate a night for nights %d to %d", propStrucPtr->discount, propStrucPtr->interval1Nights, propStrucPtr->interval2Nights);
	printf("\n%.2f discount rate a night for each remaining night over %d.", (propStrucPtr->discount * discountMult), propStrucPtr->interval2Nights);
}

//Prints the rental property information 
void displayRentalPropertyInfo(const Property* propStrucPtr, unsigned int minNights, unsigned int maxNights, int discountMult) {
	// %.2f is rounding to 2 decimal places
	printf("\nName: %s", propStrucPtr->name);
	printf("Location: %s", propStrucPtr->location);
	printf("Rental Property can be rented for %d to %d nights.", minNights, maxNights);
	printf("\n%.2f rate a night for the first %d nights", propStrucPtr->rate, propStrucPtr->interval1Nights);
	printf("\n%.2f discount rate a night for nights %d to %d", propStrucPtr->discount, propStrucPtr->interval1Nights, propStrucPtr->interval2Nights);
	printf("\n%.2f discount rate a night for each remaining night over %d.", (propStrucPtr->discount * discountMult), propStrucPtr->interval2Nights);
}

// ================================================================================================


// input validation functions
// ================================================================================================

// getInt starts the process of getting a valid integer, calls getValidIntNEW during function excecution
int getValidInt(int min, int max) {
	char inputStr[STRING_LENGTH];
	int integer = 0;

	do {
		puts("\nEnter an integer: ");
		fgets(inputStr, STRING_LENGTH, stdin);
		removeNewLine(inputStr, strlen(inputStr));
		bool result = scanInt(inputStr, min, max, &integer);

		if (result) {
			if ((integer < min) || (integer > max)) {
				printf("Not between %d and %d. Try again. ", min, max);
				result = false;
			}
			else {
				result = true;
			}
		}
		else {
			printf("Not valid input. Please enter an integer between %d and %d", min, max);
		}
	} while (!(scanInt(inputStr, min, max, &integer)));
	return integer;
}

// getInt starts the process of getting a valid integer, calls getValidIntNEW during function excecution
int getValidIntSentinal(int min, int max, int sentinal) {
	char inputStr[STRING_LENGTH];
	int integer = 0;

	do {
		puts("\nEnter an integer: ");
		fgets(inputStr, STRING_LENGTH, stdin);
		removeNewLine(inputStr, strlen(inputStr));
		bool result = scanInt(inputStr, min, max, &integer);

		if (result) {
			if (((integer < min) || (integer > max)) && (integer != sentinal)) {
				printf("Not between %d and %d. Try again. ", min, max);
				result = false;
			}
			else {
				result = true;
			}
		}
		else {
			printf("Not valid input. Please enter an integer between %d and %d", min, max);
		}
	} while (!(scanInt(inputStr, min, max, &integer)));
	return integer;
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
	// if any of the following conditions return true (if any of the checks do not pass), then the if statement will pass over and continu to the else. 
	// the only way to enter the if statement and return true is if every single one of the conditions are met
	if (!(end == stringInput) && !('\0' != *end) && !((LONG_MIN == intTest || LONG_MAX == intTest) && ERANGE == errno) && !(intTest > max) && !(intTest < min)) {
		*integerPtr = (int)intTest;
		return true;
	}
	else {
		// default return value is false. Will only return true if non of the if or else if statements were initiated 
		return false;
	}

	//if (end == stringInput) { // checks to see if the pointer end was moved from it's original position (if it found a leading decimal)
	//	fprintf(stderr, "%s: not a decimal number\n", stringInput);
	//}
	//else if ('\0' != *end) { // checks to see if the pointer end is pointing to a null character which would mean strtol read through the whole string and ended without finding a non-decimal character
	//	fprintf(stderr, "%s: extra characters at end of input: %s\n", stringInput, end);
	//}
	//else if ((LONG_MIN == intTest || LONG_MAX == intTest) && ERANGE == errno) {	// checks to see if the value entered was too large or too small for the long type, and checks for errno value to see if user entered max or min value exactly
	//	printf("ERANGE: %d", ERANGE);
	//	printf("errno: %d", errno);
	//	printf(stderr, "%s out of range of type long\n", stringInput);
	//}
	//else if (intTest > INT_MAX) { // checks to see if value entered is too large for the int datatype
	//	fprintf(stderr, "%ld greater than INT_MAX\n", intTest);
	//}
	//else if (intTest < INT_MIN) { // checks to see if value entered is too small for the int datatype
	//	fprintf(stderr, "%ld less than INT_MIN\n", intTest);
	//}
	//else { // if all the tests were passed, this means the value entered is a valid integer
	//	*integerPtr = (int)intTest;
	//	return true;
	//	// printf("%d is integer value ", *integerPtr);
	//}
	//return false;
}

// ================================================================================================
