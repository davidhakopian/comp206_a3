#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
	
	char input[6];
	char correctAnswer[6];
	char *heads = "heads";
	char *tails = "tails";
	
	printf("Welcome to Ferenginar, space explorer! Enter heads or tails on that bit of gold-pressed latinum (i.e. let's flip a coin) and see if the Rules of Acquisition are in your favour!\n");
	scanf("%s", input);

	int randomNumber = rand() % 1;
  /*
	printf("%d\n", randomNumber);
	printf("Reminder for myself while editing: 1 is heads, 0 is tails\n");*/

	if (randomNumber == 1) {
		strcpy(correctAnswer, heads);
	}
	else {
		strcpy(correctAnswer, tails);
	}

	if (strcmp(correctAnswer, input) == 0) {
		printf("%s is correct! You win!\n", input);
		return 1;
	}
	else {
		printf("%s is incorrect. You lose.\n", input);
		return 0;
	}



}
