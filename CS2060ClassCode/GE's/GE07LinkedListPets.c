/*
Joshua Edwards
CS 2060 003
Deb Harding
GE07 code

This code implements linked lists, double pointers, and file operations to construct a program that
stores pets' names and ages in a linked list and allow the user to add and delete and then store 
to a file. 

NOTE: I am aware I was not required to validate user input, but I had the functions already created 
from my last project iteration and I felt like bringing them into this program because I will need 
to implement this into my project for next iteration and I will need to validate there. There was 
minimal extra work required on my part to implement validation into this GE07 program. 
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STR_LEN 80

typedef struct pet {
	char name[STR_LEN];
	int age;
	struct pet* nextPtr;
} Pet;

// function prototypes
int strcmpCaseIgnore(const char* string1, const char* string2, int string_length);
void insertPetLoop(Pet** headPetPtr, int str_len);
void insertPets(Pet** headPetPtr, char* petName, int petAge, int str_len);
char validateYesNo();
void initPet(Pet* petPtr);
void displayPets(Pet* headPetPtr);

void removeNewLine(char* stringPtr, int size);
int getValidInt(const unsigned int min, const unsigned int max);
bool scanInt(const char* const stringInput, int* const integerPtr);

void deletePetLoop(Pet** headPetPtr, int str_len);
void deletePet(Pet** headPtr, char* petName);
void freeRemainingPets(Pet** headPtr);
void writePetsToFile(FILE* filePtr, Pet** headPetPtr);

// main func
int main() {
	Pet* headPetPtr = NULL;
	FILE* filePtr = NULL;

	insertPetLoop(&headPetPtr, STR_LEN);
	displayPets(headPetPtr);

	writePetsToFile(filePtr, &headPetPtr);

	deletePetLoop(&headPetPtr, STR_LEN);
	displayPets(headPetPtr);
	freeRemainingPets(&headPetPtr);
	displayPets(headPetPtr);
}

/*
description: takes in two strings and a length and compares the all-lowercase values of the strings
parameters: two constant strings and an integer string length
return: integer corresponding to how the two lowercase strings compare to each other
	0 -> the strings are equal
	< 0 -> second string is greater than first
	> 0 -> first string is greather than second
*/
int strcmpCaseIgnore(const char* string1, const char* string2, int string_length) {
	char holder1[STR_LEN];
	char holder2[STR_LEN];

	// copies strings from string1 and string2 to holder1 and holder2 so I don't modify the original values
	strncpy(holder1, string1, sizeof(holder1));
	strncpy(holder2, string2, sizeof(holder2));

	// for each element in the holder strings, change to lowercase
	for (int element = 0; element < string_length; element++) {
		holder1[element] = tolower(string1[element]);
		holder2[element] = tolower(string2[element]);
	}
	// compare the values in the all-lowercase strings
	return strcmp(holder1, holder2);; // returns (-1, 0, 1 etc)
}

/*
description: this is the looping logic for adding pets to the list. prompts user for choice (y or n) and name and age of pet. calls insertPets() to 
	actually insert the pets into list
parameters: a double pointer that stores an address to a Pet struct which is the head pointer of a linked list, and an integer string length
return: nothing
*/
void insertPetLoop(Pet** headPetPtr, int str_len) {
	char userResponse[] = { " " };
	char noResponse[] = { "n" };

	do {
		char petName[STR_LEN];
		char userInput[STR_LEN];
		int petAge = 0;

		puts("Enter name of pet: ");
		fgets(petName, str_len, stdin);
		removeNewLine(petName, strlen(petName));

		puts("Enter age of pet: ");
		fgets(userInput, str_len, stdin);
		removeNewLine(userInput, strlen(userInput));

		scanInt(userInput, &petAge);

		//
		insertPets(headPetPtr, petName, petAge, str_len);
		//
		
		displayPets(*headPetPtr);

		puts("\nDo you want to add another pet?\n");
		char response = validateYesNo();

		strncpy(userResponse, &response, strlen(userResponse));
		removeNewLine(userResponse, strlen(userResponse));
	} while ((strcmp(userResponse, noResponse)) != 0);
}

/*
description: this function prompts the user for yes or no and returns the lowercase value of their input
parameters: none
return: a single character of the user's choice
*/
char validateYesNo() {
	char validYesNo;

	do {
		puts("Please enter (y)es or (n)o:");
		validYesNo = getchar();
		while (getchar() != '\n'); // makes sure the user entered a character and didn't just hit enter

		// convert char to lowercase
		validYesNo = tolower(validYesNo);

	} while (validYesNo != 'y' && validYesNo != 'n'); // loops until user enters y or n (Y or N allowed)

	return  validYesNo;
}

/*
description: this function takes in the head pointer to linked list and determines where to add the pet based on the name and age provided
parameters: a double pointer that stores an address to a Pet struct which is the head pointer of a linked list, string pet name, integer pet age and integer string length
return: nothing, updates values in linked list via pointers on calling stack
*/
void insertPets(Pet **headPetPtr, char* petName, int petAge, int str_len) {
	// initialize and declare memory for new pet "node"
	Pet* newPetPtr = malloc(sizeof(struct pet));
	initPet(newPetPtr);

	if (newPetPtr != NULL) {
			
		// initialize data for new pet 
		strncpy(newPetPtr->name, petName, strlen(newPetPtr->name));
		newPetPtr->age = petAge;
		newPetPtr->nextPtr = NULL;

		// initialize trailing pet pointer and current pet pointer
		Pet* lastPetPtr = NULL;
		Pet* currentPetPtr = *headPetPtr;

		// check that new name is less than current pet pointer name
		while (currentPetPtr != NULL && strcmpCaseIgnore(currentPetPtr->name, petName, strlen(currentPetPtr->name)) < 0) {
			lastPetPtr = currentPetPtr;
			currentPetPtr = currentPetPtr->nextPtr;
		}
		if (lastPetPtr == NULL) {
			*headPetPtr = newPetPtr;
		}
		else {
			lastPetPtr->nextPtr = newPetPtr;
		}
		newPetPtr->nextPtr = currentPetPtr;
	}
	else {
		printf("No memory to create node for name \"%s\" and age \"%d\"", petName, petAge);
	}
}

/*
description:
parameters:
return:
*/
void displayPets(Pet* headPetPtr) {
	// 
	if (headPetPtr != NULL)
	{
		printf("%s", "\n\nThe list is: ");
		//
		Pet* currentPetPtr = headPetPtr;

		//
		while (currentPetPtr != NULL)
		{
			// display and go to next node
			printf("\nname: %s\tage: %d", currentPetPtr->name, currentPetPtr->age);
			currentPetPtr = currentPetPtr->nextPtr;
		}
	}
	// 
	else
	{
		puts("List is empty");
	}
}

/*
description:
parameters:
return:
*/
void initPet(Pet* petPtr) {
	char defaultName[STR_LEN] = {"Default name"};
	
	petPtr->age = 0;
	strncpy(petPtr->name, defaultName, strlen(petPtr->name));
	petPtr->nextPtr = NULL;
}

/*
description:
parameters:
return:
*/
void removeNewLine(char* stringPtr, int size) {
	if (stringPtr[(size - 1)] == '\n') { // first check to see if there is a newline char \n at end of string
		stringPtr[size - 1] = '\0'; // if there is a newline char, replace it with a null char \0
	}
}

/*
description:
parameters:
return:
*/
int getValidInt(const unsigned int min, const unsigned int max) {
	char inputStr[STR_LEN];
	int integer = 0;
	bool result = false;

	do {
		fgets(inputStr, STR_LEN, stdin);
		removeNewLine(inputStr, strlen(inputStr));
		result = scanInt(inputStr, &integer); // check if input is integer 

		// range check integer
		if (result) {
			if ((integer < min) || (integer > max)) {
				printf("Not between %d and %d. Try again: ", min, max);
				result = false;
			}
			else {
				result = true;
			}
		}
		else {
			printf("Not valid input. Please enter an integer between %d and %d: ", min, max);
		}
	} while (!result);
	return integer;
}

/*
description:
parameters:
return:
*/
bool scanInt(const char* const stringInput, int* const integerPtr) {

	char* end = NULL;
	errno = 0;
	long intTest = strtol(stringInput, &end, 10); // stops when hits non-integer character
	// if any of the following conditions return true (if any of the checks do not pass), then the if statement will pass over and continu to the else. 
	// the only way to enter the if statement and return true is if every single one of the conditions are met
	if (!(end == stringInput) && !('\0' != *end) && !((LONG_MIN == intTest || LONG_MAX == intTest) && ERANGE == errno)) {
		*integerPtr = (int)intTest;
		return true;
	}
	else {
		// default return value is false. Will only return true if non of the "if" conditions were returned  
		return false;
	}
}

/*
description:
parameters:
return:
*/
void deletePetLoop(Pet** headPetPtr, int str_len) {
	char userResponse[] = { " " };
	char noResponse[] = { "n" };
	removeNewLine(noResponse, strlen(noResponse));

	do {
		char petName[STR_LEN];
		//char userInput[STR_LEN];

		puts("\nEnter name of pet to delete: ");
		fgets(petName, str_len, stdin);
		removeNewLine(petName, strlen(petName));

		//
		deletePet(headPetPtr, petName);
		//

		if (*headPetPtr != NULL) {
			displayPets(*headPetPtr);
			puts("\nDo you want to delete another pet?\n");
			char response = validateYesNo();
			
			// removed & from userResponse's, could break things
			strncpy(userResponse, &response, strlen(userResponse));
			removeNewLine(userResponse, strlen(userResponse));
		}
	} while (*headPetPtr != NULL && (strcmp(userResponse, noResponse)) != 0);
}

/*
description:
parameters:
return:
*/
void deletePet(Pet** headPetPtr, char* petName) {
	// initialize trailing pet pointer and current pet pointer
	Pet* lastPetPtr = NULL;
	Pet* currentPetPtr = *headPetPtr;
	
	if (*headPetPtr != NULL)
	{
		// if the first pet has the name to delete
		if (strcmpCaseIgnore((*headPetPtr)->name, petName, strlen((*headPetPtr)->name)) == 0)
		{
			*headPetPtr = (*headPetPtr)->nextPtr;
			// deallocate mem
			free(currentPetPtr);
			currentPetPtr = NULL;
		}
		else // if the first pet does not have the name to delete
		{
			while (currentPetPtr != NULL && strcmpCaseIgnore(currentPetPtr->name, petName, strlen(currentPetPtr->name)) != 0)
			{
				// advance the pointers to next pet
				lastPetPtr = currentPetPtr;
				currentPetPtr = currentPetPtr->nextPtr;
			}
			if (currentPetPtr != NULL)
			{
				lastPetPtr->nextPtr = currentPetPtr->nextPtr;
				// deallocate mem
				free(currentPetPtr);
				currentPetPtr = NULL;
			}
			// if the name was not found in linked list
			else
			{
				puts("Pet to delete not found!");
			}
		}
	}
	else // the list is empty
	{
		puts("There aren't any pets in the list!");
	}
}

/*
function description: this function takes in a head pointer and iterates through the linked list deleting and deallocating 
memory as it goes to completely wipe the list
parameters: a double pointer that stores an address to a Pet struct which is the head pointer of a linked list
return: nothing
*/
void freeRemainingPets(Pet** headPetPtr) {
	// declare iterator pointers
	Pet* currentPetPtr = *headPetPtr;
	Pet* nextPetPtr = NULL;

	// will loop until currentPetPtr is NULL (reaches end of list)
	while (currentPetPtr != NULL)
	{
		// set the next pointer to the value stored in the current pet's nextPtr variable (move iteration along to next pet)
		nextPetPtr = currentPetPtr->nextPtr;
		// deallocate memory for current pet
		free(currentPetPtr);
		// bring current pet pointer back to speed by setting it equal to next pointer which is now pointing to the next pet in list
		currentPetPtr = nextPetPtr;
	}
	// set the address stored in the head pointer to NULL (delete any remaining links to list)
	*headPetPtr = NULL;
	puts("\n==============================\nAll pets have been deleted.\n==============================\n");
}

/*
description:
parameters:
return:
*/
void writePetsToFile(FILE* filePtr, Pet** headPetPtr) {
	FILE* writePtr = NULL;
	
	// C:/Users/black/Desktop/UCCS-Code-repo/CS2060ClassCode/GE's/ <-- file path to program
	if ((writePtr = fopen("C:/Users/black/Desktop/UCCS-Code-repo/CS2060ClassCode/GE's/pets.txt", "w")) == NULL) {
		puts("File could not be opened");
	}
	else {
		fprintf(writePtr, "Format: (pet name) (pet age)");
		bool stop = false;

		while (!feof(writePtr) && !stop) {
			
			if (*headPetPtr != NULL)
			{
				// initialize current pet pointer
				Pet* currentPetPtr = *headPetPtr;

				while (currentPetPtr != NULL)
				{
					fprintf(writePtr, "\n%-6s\t%-26d", (currentPetPtr)->name, (currentPetPtr)->age);
					// advance the pointer to next pet
					currentPetPtr = currentPetPtr->nextPtr;
				}
				stop = true;
			}
		}
		fclose(writePtr);
	}
}