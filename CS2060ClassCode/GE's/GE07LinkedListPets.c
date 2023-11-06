/*

Joshua Edwards

*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define STR_LEN 80

typedef struct pet {
	char* name[STR_LEN];
	int age;
	struct pet* nextPtr;
} Pet;

// function prototypes
int strcmpCaseIgnore(const char* string1, const char* string2, int string_length);
//void insertPets();
//void displayPets();
//void writePetsToFile();
//void removePet();
//void clearList();

int main() {
	//Pet *petPtr = malloc(sizeof(Pet));
	char* string1 = { "String1" };
	char* string2 = { "striNg1" };
	strcmpCaseIgnore(string1, string2, sizeof(string1));
}

int strcmpCaseIgnore(const char* string1, const char* string2, int string_length) {
	char* holder1[STR_LEN];
	char* holder2[STR_LEN];

	strcpy(holder1, string1);
	strcpy(holder2, string2);

	for (int element = 0; element < string_length; element++) {
		*holder1[element] = tolower(string1[element]);
		*holder2[element] = tolower(string2[element]);
	}


	return strcmp(*holder1, *holder2);; // (-1, 0, 1 etc)
}