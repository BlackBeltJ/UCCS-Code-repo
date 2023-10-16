// Passing Primitive Data Types and pointers
//Add comments to explain the code

#include <stdio.h>	
#include <stdlib.h>

#define RENTER_SURVEY_CATEGORIES 3

int cubePass1(int number);
int cubePass2(int * numberPtr); // this function takes a pointer to an int (takes an address to an int)
void cubePass2Updated(int* const numberPtr);
void displayCategories(const char* categories[RENTER_SURVEY_CATEGORIES], size_t totalCategories);

int main(void) {

	int numberMain = 5;
	int result = 0;

	const char* surveyCategories[RENTER_SURVEY_CATEGORIES] = { "Check-in Process", "Cleanliness", "Amenities" };
	
	printf ("In main before cubePass1  numberMain = %d\n", numberMain);
	printf("&numberMain = %p\n", &numberMain);
	result = cubePass1(numberMain);
	printf ("In main after cubePass1  numberMain = %d\n", numberMain);
	printf ("Result = %d\n", result);
	printf("\nIn main before cubePass2  numberMain = %d\n", numberMain);
	result = cubePass2(&numberMain);
	printf("\nIn main after cubePass2  numberMain = %d\n", numberMain);
	printf("result = %d\n", result);

	displayCategories(surveyCategories, RENTER_SURVEY_CATEGORIES);

} // main


int cubePass1 (int number) 
{
	int cube = 0;
	puts("\nIn cubePass1");
	printf("number = %d\n", number); // print value held in number
	printf("&number = %p\n", &number); // print address of number
	cube = number * number * number; // calculate cube of number
	printf("cube  = %d\n", cube);
	number = cube; // assign cube to variable passed to function (does not change value of number on main stack)
	printf("number = %d\n", number);
	return cube;
} 

int cubePass2 (int * numberPtr) 
{
	int cube = 0;
	puts ("\nIn cubePass2");
	printf("numberPtr = %p\n", numberPtr); // print value held in numberPtr (address of number variable)
	printf ("*numberPtr = %d\n", *numberPtr); // dereference pointer and print value in number 
	printf("&numberPtr = %p\n", &numberPtr); // print address of pointer (different than address of number variable)
	cube = (* numberPtr )* (* numberPtr )* (* numberPtr); // dereference pointer and cube value 
	*numberPtr = cube; // dereference and assign value of cube back to number variable in main stack
	printf ("*numberPtr = %d\n", *numberPtr);
	return cube;
} 

void cubePass2Updated(int* const numberPtr) {
	printf("   *numberPtr = %d\n", *numberPtr);
	printf("   numberPtr = %p\n", numberPtr);
	int cube = (*numberPtr) * (*numberPtr) * (*numberPtr);
	*numberPtr = cube;
	// numberPtr = &cube;
	printf("   *numberPtr = %d\n\n", *numberPtr);
}

void displayCategories(const char* categories[RENTER_SURVEY_CATEGORIES], size_t totalCategories) {
	//loop to display each category horizontally
	printf("%s", "\n\nRating Categories:\t");
	for (size_t surveyCategory = 0; surveyCategory < totalCategories; ++surveyCategory)
	{
		printf("\t%zu.%s\t", surveyCategory + 1, categories[surveyCategory]); // %zu is to print size_t datatypes
	}
	puts(""); // start new line of output
}

