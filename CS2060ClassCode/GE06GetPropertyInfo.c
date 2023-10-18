/* Joshua Edwards
CS 2060 003 
Deb Harding
GE06 code
Add description here...
*/

#include <stdio.h>
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
	initializeDefaultPropertyVals(&property1, minNights, maxNights, minRate, maxRate);

	// pass by reference to set up property data
	setUpProperty(&property1);

	// display property data
	displayOrganization(property1);
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
	printf("\nLocation: %s", prop.location);
	printf("\nRental Property can be rented for %d to %d nights.", prop.interval1Nights, prop.interval2Nights);
	printf("\n%.2f rate a night for the first %d nights", prop.rate, prop.interval1Nights);
	printf("\n%.2f discount rate a night for nights %d to %d", prop.discount, prop.interval1Nights, prop.interval2Nights);
	printf("\n%.2f discount rate a night for each remaining night over %d.", (prop.discount * 2), prop.interval2Nights);
}