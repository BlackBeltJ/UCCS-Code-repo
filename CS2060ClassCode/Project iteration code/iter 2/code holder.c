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