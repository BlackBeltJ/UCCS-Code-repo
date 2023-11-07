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
void insertPets(Pet* petPtr);
//void displayPets();
//void writePetsToFile();
//void removePet();
//void clearList();

int main() {
	Pet *petPtr = malloc(sizeof(Pet));
	char* string1 = { "String1" };
	char* string2 = { "striNg1" };
	int returnVal = strcmpCaseIgnore(string1, string2, strlen(string1));
	//printf("\n\nstrcmpCaseIgnore return value: %d\n\n", returnVal);

	insertPets(petPtr);
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
void insertPets(Pet* headPetPtr) {
	char userResponse[STR_LEN];

	puts("\nDo you want to add another pet? (y or n): ");
	fgets(userResponse, STR_LEN, stdin);

	while (strncmp(userResponse, "n", strlen(userResponse))) {
		char petName[STR_LEN];
		char petAge[STR_LEN];

		puts("Enter name of pet: ");
		fgets(petName, STR_LEN, stdin);
		puts("Enter age of pet: ");
		fgets(petAge, STR_LEN, stdin);
		
		if (headPetPtr->nextPtr == NULL) {
			strncpy(headPetPtr->name, petName, strlen(headPetPtr->name));
			headPetPtr->age = (int)(petAge);
			headPetPtr->nextPtr = NULL;
		}
		else {
			Pet* currentPtr = headPetPtr;

			while (currentPtr->name < currentPtr->nextPtr->name) {
				currentPtr->nextPtr = currentPtr->nextPtr->nextPtr;
			}
			//currentPtr->nextPtr = something lol;
		}
		
		

	}
}