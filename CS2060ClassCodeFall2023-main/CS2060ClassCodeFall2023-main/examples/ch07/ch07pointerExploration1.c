/*******************
 Understanding pointers

 Add comments to explain the code

 Joshua Edwards
 CS 2060 003
**************/

#include <stdio.h>


int main ()
{
	// Initalize houseNum
	int houseNum = 13;
	int calcHouseNum1 = 0;
	int calcHouseNum2 = 0;
	int *houseNumPtr = &houseNum; // this is a pointer to an integer which means houseNumPtr holds the address to houseNum
	
	printf("houseNum %d\n", houseNum); // prints value in houseNum (13)

	printf("&houseNum %p\n\n", &houseNum); // prints address of houseNum

	printf ("*houseNumPtr  %d\n", *houseNumPtr); // dereferences the pointer to print the value stored in houseNum

	printf ("houseNumPtr %p\n\n", houseNumPtr); // prints the value held in houseNumPtr which is the address of houseNum

	printf ("&houseNumPtr %p\n\n", &houseNumPtr); // prints the address of the pointer variable (not the address of the variable it points to)

	calcHouseNum1 =  *houseNumPtr + *houseNumPtr; // dereferences the pointer twice to add the values stored in houseNum (26)

	printf("*houseNumPtr + *houseNumPtr is %d\n\n", calcHouseNum1); // prints 26

	calcHouseNum2 = 2 * (*houseNumPtr); // dereferences the pointer again and multiplies the value in houseNum by 2 (26)

	printf("2 * (*houseNumPtr) is %d\n\n", calcHouseNum2); // prints 26

	printf("\n&*houseNumPtr = %p"
		"\n*&houseNumPtr = %p\n", &*houseNumPtr, *&houseNumPtr); // both these variables print the same thing, the address of houseNum
			
	return 0;
}
