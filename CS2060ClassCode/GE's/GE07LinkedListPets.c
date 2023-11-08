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
void initPet(Pet* petPtr);
void displayPets(Pet** headPetPtr);

void removeNewLine(char* stringPtr, int size);
int getValidInt(const unsigned int min, const unsigned int max);
bool scanInt(const char* const stringInput, int* const integerPtr);
//void writePetsToFile();
//void removePet();
//void clearList();

int main() {
	Pet *petPtr = malloc(sizeof(Pet));
	initPet(petPtr);

	char* string1 = { "String1" };
	char* string2 = { "striNg1" };
	int returnVal = strcmpCaseIgnore(string1, string2, strlen(string1));
	//printf("\n\nstrcmpCaseIgnore return value: %d\n\n", returnVal);

	//insertPets(&petPtr, STR_LEN);

	Pet* pet1 = malloc(sizeof(Pet));
	if (pet1 != NULL) {
		strncpy(pet1->name, "name1", strlen(pet1->name));
		pet1->age = 5;
	}
	
	Pet* pet2 = malloc(sizeof(Pet));
	if (pet2 != NULL) {
		strncpy(pet2->name, "name2", strlen(pet2->name));
		pet2->age = 7;
	}

	//Pet* pet3 = malloc(sizeof(Pet));
	/*if (pet3 != NULL) {
		strncpy(pet3->name, "name3", strlen(pet3->name));
		pet3->age = 2;
	}*/

	displayPets(&petPtr);
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
	char userResponse[STR_LEN] = "n";
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

		puts("\nDo you want to add another pet? (y or n): ");
		fgets(userResponse, STR_LEN, stdin);
		removeNewLine(userResponse, strlen(userResponse));

	} while ((strncmp(userResponse, "n", strlen(userResponse))));
}

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
		while (currentPetPtr != NULL /* && lastPetPtr != NULL*/ && strcmpCaseIgnore(currentPetPtr->name, petName, max((int)(strlen(currentPetPtr->name)), (int)(strlen(petName)))) > 0) {
			//lastPetPtr = currentPetPtr;
			//currentPetPtr = currentPetPtr->nextPtr;
			lastPetPtr->nextPtr = newPetPtr;
			newPetPtr->nextPtr = currentPetPtr;
		}

		if (lastPetPtr == NULL) {
			*headPetPtr = newPetPtr;
			//lastPetPtr = newPetPtr;
			//currentPetPtr = newPetPtr;
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

void displayPets(Pet** headPetPtr) {
	Pet* currentPetPtr = *headPetPtr;

	do {
		printf("\nPet name: %s\tPet age: %d", currentPetPtr->name, currentPetPtr->age);
		currentPetPtr = currentPetPtr->nextPtr;
	} while (currentPetPtr->nextPtr != NULL);
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