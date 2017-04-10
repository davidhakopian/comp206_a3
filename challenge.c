int challenge(char *userInput) {
	
	char input[6] = userInput;
	char correctAnswer[6];
	char *heads = "heads";
	char *tails = "tails";

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
