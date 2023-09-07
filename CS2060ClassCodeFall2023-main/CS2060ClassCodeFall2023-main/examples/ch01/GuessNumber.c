// Randomly generate numbers between a min and max for user to guess.


// these statements "import" libraries into the program to allow certain methods and functions to be used that are not in the standard library
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// sets "constants" and sets the values equal to placeholders called MIN and MAX
#define MIN 1
#define MAX 1000

// defines a two functions that the program will use. The first function takes no arguments, the second takes the user's guess and the number answer
void guessGame(void); 
bool isCorrect(int guess, int answer); 

int main(void) {
    // generate a random value to set as the random seed. Uses time from a certain event to get a new random number every time the program is run
   srand(time(0)); 

   // calls the guessGame function and passes program execution to the function 
   guessGame();
} // end main


// instantiates the guessGame function
void guessGame(void) {
    
    // sets variable values pre-excecution 
   int response = 0;
   int guess = 0;

   // starts a do-while loop. The "do" portion will always run, the "while" portion will stop when the condition is met
   do {

      // defines the variable "answer" and assigns it to a random value within the parameters
      int answer = MIN + rand() % MAX;

      puts("Hello Josh");

      // prints this message to the console using the MIN and MAX variables in the message
      printf("I have a number between %d and %d.\n", MIN, MAX);

      // prints this message to the console with a line break "\n"
      puts("Can you guess my number?\n" 
           "Please type your first guess.");

      // This line uses a format specifier "%s" to print a string "?" to the console
      printf("%s", "? ");
      

      // receives an input, specifically an integer specified by the "%d" specifier, from the user and stores that in the variable "guess"
      scanf("%d", &guess);

      // this will loop until the user picks the correct answer and will continue asking the user for a guess
      while (!isCorrect(guess, answer)) {
         scanf("%d", &guess);
      }


      puts("\nExcellent! You guessed the number!\n"
         "Would you like to play again?");
      printf("%s", "Please type (1=yes, 2=no)? ");
      scanf("%d", &response);
      puts("");

   } while (response == 1);
} // end function guessGame

// instantiates the isCorrect function that takes two parameters, the user's guess and the answer
bool isCorrect(int guess, int answer) {

    // sets the default value of the trigger "correct" to false
    bool correct = false;

   // checks if the user has guessed the answer and if they have, set the trigger "correct" to true
   if (guess == answer) {
      correct = true;
   }

   // this will help the user guess the number by giving them hints based on their guess
   if (guess < answer) {
      printf( "%s", "Too low. Try again.\n? " );
   }
   else {
      printf( "%s", "Too high. Try again.\n? " );
   }

   return correct;
} // end function isCorrect



/**************************************************************************
 * (C) Copyright 1992-2012 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/
