/*

Joshua Edwards

*/

#include <stdio.h>
#include <stdbool.h>

#define STR_LEN 80

typedef struct pet {
	char* name[STR_LEN];
	int age;
} Pet;

// function prototypes
bool strcmpCaseIgnor(char* string1, char* string2);
void insertPets();
void displayPets();
void writePetsToFile();
void removePet();
void clearList();

int main() {

}