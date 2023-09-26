/*
Joshua Edwards
GE04 Renter Survey code
This program allows users to leave reviews on AirUCCS properties and then will allow the
users to see past reviews and allow renters to see the average review score for each category.
*/

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define RENTERROWS 5
#define RENTERRATING 3
#define RENTER_SURVEY_CATEGORIES 3
#define MINRATING 1
#define MAXRATING 5

// insert function prototypes here
void printCategories(const char* categories[], size_t totalCategories);
void getRatings(int rentalSurvey[][RENTERRATING], size_t renters_rows, size_t ratings_columns, int MIN_RATING, int MAX_RATING);
int getValidInt(int MIN_RATING, int MAX_RATING);
void printSurveyResults(const int rentalSurvey[][RENTERRATING], int MIN_RATING, int MAX_RATING);
void calculateCetegoryAverages(int rentalSurvey[][RENTERRATING], int categoryAverages[RENTER_SURVEY_CATEGORIES], size_t renters_rows, size_t ratings_columns);
void printCategoryData(const int categoryAverages[RENTER_SURVEY_CATEGORIES], size_t totalCategories);

int main(void) {
	// declare and init variables and arrays
	int categoryAverages[RENTER_SURVEY_CATEGORIES];
	int rentalSurvey[RENTERROWS][RENTERRATING];
	const char* surveyCategories[RENTER_SURVEY_CATEGORIES] = { "Check-in Process", "Cleanliness", "Amenities" };

	// fill arrays with 0s
	for (size_t i = 0; i < RENTER_SURVEY_CATEGORIES; i++) {
		categoryAverages[i] = 0;
	}
	for (size_t row = 0; row < RENTERROWS; row++) {
		for (size_t column = 0; column < RENTERRATING; column++) {
			rentalSurvey[row][column] = 0;
		}
	}

	// printCategories(); add parameters
	// getRatings(); add parameters

} // end main

// insert function definitions here
void printCategories(const char* categories[], size_t totalCategories)
{
	//loop to display each category horizontally
	printf("%s", "Rating Categories:\t");
	for (size_t surveyCategory = 0; surveyCategory < totalCategories; ++surveyCategory)
	{
		printf("\t%zu.%s\t", surveyCategory + 1, categories[surveyCategory]);
	}
	puts(""); // start new line of output
}

void getRatings(int rentalSurvey[][RENTERRATING], size_t renters_rows, size_t ratings_colums, int MIN_RATING, int MAX_RATING) {
	// ask user for each rating	
	// verify valid data, use getValidInt()
	int rating = getValidInt(MIN_RATING, MAX_RATING);

	// write data to rentalSurvey[][] array

}

int getValidInt(int MIN_RATING, int MAX_RATING) {
	// algorithm to check valid input
	int input = 0;
	bool isValidInput = false;

	printf("Please enter an integer rating between %d and %d", MIN_RATING, MAX_RATING);
	int scanfReturnValue = scanf("%d", &input);
	while ((getchar() != '\n')); // clears the input buffer
	while (isValidInput == false)
	{
		if (scanfReturnValue == 1)
		{
			// if scanf returns a 1, that means that data was successfully read (the user entered an integer)
			// check range
			if ((input >= MIN_RATING) && (input <= MAX_RATING)) {
				isValidInput = true;
			}
			else {
				printf("Not between %d and %d, please try again: ", MIN_RATING, MAX_RATING);
				isValidInput = false;
				
				int scanfReturnValue = scanf("%d", &input); // prompt user again
				while ((getchar() != '\n')); // clears the input buffer
			}
		}
		else
		{
			// prompt the user for an integer again if they did not enter one initially
			puts("Not an integer, please try again: ");
			scanfReturnValue = scanf("%d", &input);
			while ((getchar() != '\n')); // clear the input buffer again
		}
	}
	return input; // function will always returen valid input
}

void printSurveyResults(const int rentalSurvey[][RENTERRATING], int MIN_RATING, int MAX_RATING) {
	// loop through array and display the each row and column
	for (size_t renter_row = 0; renter_row < RENTERROWS; renter_row++) {
		printf("Review %d: ", renter_row);
		for (size_t renter_rating = 0; renter_rating < RENTERRATING; renter_rating++) {
			printf("\t%d", renter_rating);
		}
	}
}

void calculateCetegoryAverages(int rentalSurvey[][RENTERRATING], int categoryAverages[RENTER_SURVEY_CATEGORIES], size_t renters_rows, size_t ratings_columns) {
	// read integers from each row and calculate average
	// store average in categoryAverages[]
}

void printCategoryData(const int categoryAverages[RENTER_SURVEY_CATEGORIES], size_t totalCategories) {
	// iterate through categoryAverages[] array and display results
	for (size_t categories = 0; categories < totalCategories; categories++) {
		printf("%d\t", categories);
	}
}