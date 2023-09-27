/*
Joshua Edwards
GE04 Renter Survey code
This program allows users to leave reviews on AirUCCS properties and then will allow the
users to see past reviews and allow renters to see the average review score for each category.
*/

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

// constants
#define RENTERS_ROWS 5
#define RENTER_SURVEY_CATEGORIES 3
#define MINRATING 1
#define MAXRATING 5

// insert function prototypes here
void printCategories(const char* categories[RENTER_SURVEY_CATEGORIES], size_t totalCategories);
void getRatings(int rentalSurvey[][RENTER_SURVEY_CATEGORIES], size_t renters_rows, size_t category_columns, int MIN_RATING, int MAX_RATING);
int getValidInt(int MIN_RATING, int MAX_RATING);
void printSurveyResults(const int rentalSurvey[][RENTER_SURVEY_CATEGORIES], size_t renters_rows, size_t category_columns, int MIN_RATING, int MAX_RATING);
void calculateCategoryAverages(int rentalSurvey[][RENTER_SURVEY_CATEGORIES], double categoryAverages[RENTER_SURVEY_CATEGORIES], size_t renters_rows, size_t ratings_columns);
void printCategoryData(const double categoryAverages[RENTER_SURVEY_CATEGORIES], size_t totalCategories);

int main(void) {
	// declare and init variables and arrays
	double categoryAverages[RENTER_SURVEY_CATEGORIES];
	int rentalSurvey[RENTERS_ROWS][RENTER_SURVEY_CATEGORIES];
	const char* surveyCategories[RENTER_SURVEY_CATEGORIES] = { "Check-in Process", "Cleanliness", "Amenities" };

	// initialize arrays with 0s
	// 1D array
	for (size_t i = 0; i < RENTER_SURVEY_CATEGORIES; i++) {
		categoryAverages[i] = 0;
	}
	// 2D array
	for (size_t row = 0; row < RENTERS_ROWS; row++) {
		for (size_t column = 0; column < RENTER_SURVEY_CATEGORIES; column++) {
			rentalSurvey[row][column] = 0;
		}
	}
	
	// function calls
	printCategories(surveyCategories, RENTER_SURVEY_CATEGORIES);
	getRatings(rentalSurvey, RENTERS_ROWS, RENTER_SURVEY_CATEGORIES, MINRATING, MAXRATING);
	puts("\nSurvey results");
	printCategories(surveyCategories, RENTER_SURVEY_CATEGORIES);
	printSurveyResults(rentalSurvey, RENTERS_ROWS, RENTER_SURVEY_CATEGORIES, MINRATING, MAXRATING);
	calculateCategoryAverages(rentalSurvey, categoryAverages, RENTERS_ROWS, RENTER_SURVEY_CATEGORIES);
	printCategories(surveyCategories, RENTER_SURVEY_CATEGORIES);
	printCategoryData(categoryAverages, RENTER_SURVEY_CATEGORIES);

} // end main

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
	// loop through entire 2D array
	for (size_t renters = 0; renters < renters_rows; renters++)
	{
		printf("\n\tRenter %d:", (int)(renters + 1)); // use the row value + 1 (because index starts at 0) to display the renter number
		for (size_t category = 0; category < category_columns; category++)
		{
			// ask user for each rating	
			printf("\nEnter your rating for \nCategory %d: ", (int)(category + 1)); // category + 1 because the category index starts at 0 and I want renters to start at 1
			// verify valid data, use getValidInt()
			int rating = getValidInt(min_rating, max_rating);
			// write data to 2D rentalSurvey element
			rentalSurvey[renters][category] = rating;
		}
	}
} // by the end of this function, the 2D array passed will be full of valid ratings from each renter 

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

// this function prints the average of each category
void printCategoryData(const double categoryAverages[RENTER_SURVEY_CATEGORIES], size_t totalCategories) {
	// iterate through categoryAverages array and display results
	printf("%s", "\nRating averages:");
	for (size_t category = 0; category < totalCategories; category++) {
		printf("\t\t%.2f", categoryAverages[category]);
	}
}