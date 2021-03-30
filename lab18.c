#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include <time.h>

#define MAXSTRING 84095 //Number of strings.

char dataArray[MAXSTRING][100]; //String is global so no overflow occurs.

int main() {

	FILE* fptr; // File pointer.
	int i = 0;
	int lower = 0; //For rand lower limit.
	int upper = 30393; //For rand upper limit.
	char line[100]; //Save each word from delim \n.
	int counter = 0; //To count the words within a limit.
	char* token; //Pointer used with strtok.
	srand(2000000 * time(NULL)); //Setting a high number so the randomness is much higher.

	fptr = fopen("C:\\Users\\User\\OneDrive\\college\\Data18.txt", "r"); // opens file in read mode.
	if (fptr == NULL) // if file is empty.
	{
		puts("Error Opening File \n Exiting ........");
		return;
	}


	while (!feof(fptr)) {// until the end of file.
		fgets(line, 100, fptr);
		token = strtok(line, "\n"); //Getting rid of \n.

		if (strlen(token) < 8 && strlen(token) > 3) { //Checking the length of the words.

			strcpy(dataArray[counter], token); //If within the limit save it into an array.
			counter++; //Number of words in new array.
		}
	}

	printf("Loaded %d number of words from the dictionary.\n", counter);
	printf("-----------------------------------------------\n");
	fclose(fptr);

	int randomIndex = rand() % upper + 1; //Random numbers in a limit for index.
	int numCorrect = 0; //To increment when input is in the word.
	int wordLength = strlen(dataArray[randomIndex]);//Used to print "-", and a check.
	int letterGuessed[8] = { 0,0,0,0,0,0,0,0 };//Array for input.
	int guessNumber = 0;
	char guess[16]; //Saves input.
	char letterEntered;

	while (numCorrect < wordLength) {//Runs while the word length hasnt been reached.
		guessNumber++;//How many guesses.
		printf("\nGuess %d\n", guessNumber);

		for (int i = 0; i < wordLength; i++) {//for the length of random word.

			if (letterGuessed[i] == 1) {//Prints the guessed letter in the place it belongs in the word.
				printf("%c", dataArray[randomIndex][i]);
			}
			else {
				printf("-");//Prints "-" until letter is guessed right.
			}
		}
		printf("\n");
		printf("Guess a letter > ");
		fgets(guess, 16, stdin);//Takes it into guess[].

		letterEntered = guess[0];

		for (int i = 0; i < wordLength; i++) {
			if (letterGuessed[i] == 1) {//For the same guessed right letter input.
				if (dataArray[randomIndex][i] == letterEntered) {
					break;
				}
				continue;
			}
			if (letterEntered == dataArray[randomIndex][i]) {
				letterGuessed[i] = 1;//For the first if to be fired.
				numCorrect++;
			}
		}
	}
	printf("\nWell done, that took you %d guesses to find %s!\n", guessNumber, dataArray[randomIndex]);
	return 0;
}