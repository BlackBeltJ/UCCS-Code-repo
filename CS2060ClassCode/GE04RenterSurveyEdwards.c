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
	// display character array for rating titles
	// ask user for each rating	
	// verify valid data, use getValidInt()
	// write data to rentalSurvey[][] array
}

int getValidInt(int MIN_RATING, int MAX_RATING) {
	// grab algorithm from documentation
	// check for range
}

void printSurveyResults(const int rentalSurvey[][RENTERRATING], int MIN_RATING, int MAX_RATING) {
	// loop through array and display the each row and column
}

void calculateCetegoryAverages(int rentalSurvey[][RENTERRATING], int categoryAverages[RENTER_SURVEY_CATEGORIES], size_t renters_rows, size_t ratings_columns) {
	// read integers from each row and calculate average
	// store average in categoryAverages[]
}

void printCategoryData(const int categoryAverages[RENTER_SURVEY_CATEGORIES], size_t totalCategories) {
	// iterate through categoryAverages[] array and display results
}