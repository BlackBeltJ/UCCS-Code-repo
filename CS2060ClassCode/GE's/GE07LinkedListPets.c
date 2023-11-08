/*

Joshua Edwards

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
//void freeRemainingPets(Pet** headPtr);
void writePetsToFile(Pet* headPetPtr, char* fileName);

int main() {
	Pet* headPetPtr = NULL;


	insertPetLoop(&headPetPtr, STR_LEN);
	displayPets(headPetPtr);
	//writePetsToFile()
	deletePetLoop(&headPetPtr, STR_LEN);
	displayPets(headPetPtr);
}

/*
*/
int strcmpCaseIgnore(const char* string1, const char* string2, int string_length) {
	char holder1[STR_LEN];
	char holder2[STR_LEN];

	strncpy(holder1, string1, sizeof(holder1));
	strncpy(holder2, string2, sizeof(holder2));

	for (int element = 0; element < string_length; element++) {
		holder1[element] = tolower(string1[element]);
		holder2[element] = tolower(string2[element]);
	}
	//printf("lowercase strings: \"%s\" and \"%s\"", holder1, holder2);
	return strcmp(holder1, holder2);; // (-1, 0, 1 etc)
}

/*
*/
void insertPetLoop(Pet** headPetPtr, int str_len) {
	char userResponse[] = { " " };
	char noResponse[] = { "n" };
	removeNewLine(&noResponse, strlen(&noResponse));

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

		strncpy(&userResponse, &response, strlen(&userResponse));
		removeNewLine(&userResponse, strlen(&userResponse));

		//printf("string1: %s\tstring2: %s", &userResponse, &noResponse);
		//printf("\nstrcmp: %d", strcmp(&userResponse, &noResponse));

	} while ((strcmp(&userResponse, &noResponse)) != 0);
}

char validateYesNo() {
	char validYesNo;

	do {
		puts("Please enter (y)es or (n)o:");
		validYesNo = getchar();
		while (getchar() != '\n');

		validYesNo = tolower(validYesNo);

	} while (validYesNo != 'y' && validYesNo != 'n');

	return  validYesNo;
} //End validateYesNo

/*

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

void initPet(Pet* petPtr) {
	char defaultName[STR_LEN] = {"Default name"};
	
	petPtr->age = 0;
	strncpy(petPtr->name, defaultName, strlen(petPtr->name));
	petPtr->nextPtr = NULL;
}

void removeNewLine(char* stringPtr, int size) {
	if (stringPtr[(size - 1)] == '\n') { // first check to see if there is a newline char \n at end of string
		stringPtr[size - 1] = '\0'; // if there is a newline char, replace it with a null char \0
	}
}

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
*/
void deletePetLoop(Pet** headPetPtr, int str_len) {
	char userResponse[] = { " " };
	char noResponse[] = { "n" };
	removeNewLine(&noResponse, strlen(&noResponse));

	do {
		char petName[STR_LEN];
		char userInput[STR_LEN];

		puts("\nEnter name of pet to delete: ");
		fgets(petName, str_len, stdin);
		removeNewLine(petName, strlen(petName));

		//
		deletePet(headPetPtr, petName);
		//

		displayPets(*headPetPtr);

		puts("\nDo you want to delete another pet?\n");
		char response = validateYesNo();

		strncpy(&userResponse, &response, strlen(&userResponse));
		removeNewLine(&userResponse, strlen(&userResponse));
	} while (headPetPtr != NULL && (strcmp(&userResponse, &noResponse)) != 0);
}
/*
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
*/
void writePetsToFile(Pet* headPetPtr, char* fileName) {
	
	while (headPetPtr != NULL) {
		// add code to iterate through linked list and write each pet name to file
	}
}