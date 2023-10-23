/* 
Joshua Edwards
Oct 21, 2023
CS 2060 003 
Deb Harding

GE06 code
This program gets values from the user to set up property info and validate user input with fgets. 
*/

#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 80

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

	char name[SIZE];
	char location[SIZE];
} Property;

void initializeDefaultPropertyVals(Property *prop, const int minNights, const int maxNights, const double minRate, const double maxRate);
void setUpProperty(Property* prop);
void displayOrganization(const Property prop);
bool getValidInt(const char* const stringInput, int min, int max, int* const integerPtr);
// use later -> int getValidInt(int min, int max);
// use later -> double getValidDub(double min, double max);
 
int main(void)
{
	int minNights = 1;
	int maxNights = 14;
	double minRate = 1;
	double maxRate = 1000;

	Property property1;
	// initialize default property values
	// initializeDefaultPropertyVals(&property1, minNights, maxNights, minRate, maxRate);

	// pass by reference to set up property data
	// setUpProperty(&property1);

	// display property data
	// displayOrganization(property1);

	char inputStr[SIZE];
	int integer = 0;

	puts("\nEnter an integer: ");
	fgets(inputStr, SIZE, stdin);
	if (inputStr[(strlen(inputStr) - 1)] == '\n') { // first check to see if there is a newline char \n at end of string
		inputStr[strlen(inputStr) - 1] = '\0'; // if there is a newline char, replace it with a null char \0
	}
	bool validReturnVal = getValidInt(inputStr, maxNights, minNights, &integer);
	printf("Value in integer: %d", integer);
}

void initializeDefaultPropertyVals(Property* prop, const int minNights, const int maxNights, const double minRate, const double maxRate) {
	prop->minimumNights = minNights;
	prop->maximumNights = maxNights;
	prop->minimumRate= minRate;
	prop->maximumRate= maxRate;
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
	fgets(propertyPtr->name, SIZE, stdin); // dont need & because passing array which already holds address
	puts("Enter the property location: ");
	fgets(propertyPtr->location, SIZE, stdin);
}

void displayOrganization(const Property prop) {
	printf("\nName: %s", prop.name);
	printf("Location: %s", prop.location);
	printf("Rental Property can be rented for %d to %d nights.", prop.interval1Nights, prop.interval2Nights);
	printf("\n%.2f rate a night for the first %d nights", prop.rate, prop.interval1Nights);
	printf("\n%.2f discount rate a night for nights %d to %d", prop.discount, prop.interval1Nights, prop.interval2Nights);
	printf("\n%.2f discount rate a night for each remaining night over %d.", (prop.discount * 2), prop.interval2Nights);
}

// function returns true if valid integer (stringInput) was read to variable (var that integerPtr points to) and false otherwise
bool getValidInt(const char* const stringInput, int max, int min, int* const integerPtr) {
	
	char* end = NULL;
	errno = 0;
	long intTest = strtol(stringInput, &end, 10); // stops when hits non-integer character
	// if any of the following conditions return true (if any of the checks do not pass), then the if statement will pass over and continu to the else. 
	// the only way to enter the if statement and return true is if every single one of the conditions are met
	if (!(end == stringInput) && !('\0' != *end) && !((LONG_MIN == intTest || LONG_MAX == intTest) && ERANGE == errno) && !(intTest > max) && !(intTest < min)) {
		*integerPtr = (int)intTest;
		puts("getValidInt return val: true");
		return true;
	}
	else {
		// default return value is false. Will only return true if non of the if or else if statements were initiated 
		puts("getValidInt return val: false");
		return false;
	}
}