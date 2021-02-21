#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "associative_array.h"
#include "vector.h"

int charUsed(char guess, char* usedChars);

int main(int argc, char* argv[])
{
  VECTOR vectors[30];
  MY_STRING strCheck = my_string_init_default();
  FILE* fp; int i, solved = 0, playAgain = 1;

  fp = fopen("dictionary.txt", "r");
  if (fp == NULL)
    {
      printf("error: file not found\n");
      return 1;
    }

  printf("loading...\n");
  for (i = 0; i < 30; i++)
    vectors[i] = vector_init_default();

  while (my_string_extraction(strCheck, fp) != FAILURE)
  {
    if (my_string_get_size(strCheck) < 30)
    {
      int j = my_string_get_size(strCheck);
      MY_STRING temp = NULL;
      my_string_assignment(&temp, strCheck);
      vector_push_back(vectors[j], temp);
    }
  }

  fclose(fp);
	
  while (playAgain)
  {
    VECTOR wordBank = NULL;
    ASSOCIATIVE_ARRAY testAA; 
    char usedChars[26] = { '\0' }; int usedCharCounter = 0, wordSize = 0, numGuesses = 0;

    char guessChar; int seeWords;
    printf("Please enter a word size: ");
    do {
      char h;
      scanf("%d", &wordSize);
      for (h = getchar(); h != '\n' && h != '\0'; h = getchar()); //clear buffer
      if (wordSize > 29 || wordSize < 2 || wordSize == 23 || wordSize == 25 || wordSize == 26 || wordSize == 27)
        printf("Invalid word size. Try again: ");
      } while (wordSize > 29 || wordSize < 2 || wordSize == 23 || wordSize == 25 || wordSize == 26 || wordSize == 27);
		
      testAA = assoc_init_default(wordSize);

      printf("Please enter number of guesses: ");
      do {
	char h;
	scanf("%d", &numGuesses);
	for (h = getchar(); h != '\n' && h != '\0'; h = getchar()); //clear buffer

	if (numGuesses <= 0)
	  printf("Number of guesses must be greater than zero. Try again: ");
      } while (numGuesses <= 0);

      printf("Do you want to see the word bank? (Y/N) ");
      do {
	char h;
	guessChar = getchar();
	if (guessChar != '\n')
	  for (h = getchar(); h != '\n' && h != '\0'; h = getchar()); //clear buffer

	if (guessChar == 'Y' || guessChar == 'y')
	  seeWords = 1;
	else if (guessChar == 'N' || guessChar == 'n')
	  seeWords = 0;
	else
	  printf("Invalid input. Try again: ");
      } while (guessChar != 'Y' && guessChar != 'y' && guessChar != 'N' && guessChar != 'n');

      wordBank = vector_init_default();

      for (i = 0; i < vector_get_size(vectors[wordSize]); i++)
      {
        MY_STRING tempStr = my_string_init_c_string(my_string_c_str(*vector_at(vectors[wordSize], i)));
        vector_push_back(wordBank, tempStr);
      }

		

      if (seeWords)
	for (i = 0; i < vector_get_size(wordBank); i++)
	  printf("%s\n", my_string_c_str(*vector_at(wordBank, i)));
		
      printf("%s\n", my_string_c_str(getCurrentKey(testAA)));

      while (numGuesses > 0 && !solved)
	{
	  char h; int changed;
	  solved = 1;
	  printf("Guesses remaining: %d\nPlease guess a character: ", numGuesses);
	  guessChar = getchar();
			
	  if (guessChar != '\n')
	    h = getchar();
	  else
	    h = guessChar;

	  if (guessChar > 96)
              guessChar -= 32;
	  
	  while (!((guessChar >= 65 && guessChar <= 90) || (guessChar >= 97 && guessChar <= 122)) || h != '\n' || guessChar == '\n' || charUsed(guessChar, usedChars))  //check guess
	  {
	    if (h != '\n')                            //clear buffer
	      for (h = getchar(); h != '\n' && h != '\0'; h = getchar());
	    printf("Invalid input. Please try again: ");
	    guessChar = getchar();
	    if (guessChar != '\n')
              h = getchar();
	    if (guessChar > 96)
            guessChar -= 32;
          }

        if (usedCharCounter < 26)
	  usedChars[usedCharCounter] = guessChar;
	usedCharCounter++;

        for (i = 0; i < vector_get_size(wordBank); i++)
          addWord(testAA, *vector_at(wordBank, i), guessChar);

	//vector_destroy(&wordBank);
        wordBank = key_update(testAA, &changed, &wordBank);

	if (seeWords) //print remaining word bank
          for (i = 0; i < vector_get_size(wordBank); i++)
	    printf("%s\n", my_string_c_str(*vector_at(wordBank, i)));

        printf("%s, %d\n", my_string_c_str(getCurrentKey(testAA)), vector_get_size(wordBank));

        printf("Characters used/tried: ");
        for (i = 0; usedChars[i] != '\0' && i < 26; i++)
          printf("%c", usedChars[i]);
        printf("\n");

        for (i = 0; i < wordSize && solved; i++) //check if solved
          if (*my_string_at(getCurrentKey(testAA), i) == '-')
            solved = 0;

	if (!changed)
          numGuesses--;
      }

      if (solved)
	printf("Congratulations! You won!\n");
      else
      {
        my_string_insertion(vector_rString(wordBank), stdout);
        printf("\nSorry, you lost.\n");
      }

      vector_destroy(&wordBank);
      solved = 0;
      
      printf("Play again? Y/N");

      do {
	char h;
	guessChar = getchar();
	for (h = getchar(); h != '\n' && h != '\0'; h = getchar()); //clear buffer

	if (guessChar == 'Y' || guessChar == 'y')
	  playAgain = 1;
	else if (guessChar == 'N' || guessChar == 'n')
	  playAgain = 0;
	else
	  printf("Invalid input. Try again: ");
      } while (guessChar != 'Y' && guessChar != 'y' && guessChar != 'N' && guessChar != 'n');

      assoc_destroy(&testAA);
    }

  for (i = 0; i < 30; i++)
    vector_destroy(&vectors[i]);
	
  my_string_destroy((Item*)&strCheck);

  return 0;
}

int charUsed(char guess, char* usedChars)
{
  int g;
  for (g = 0; g < 26; g++)
    {
      //printf("%c, %c\n", guess, usedChars[g]);
    if (guess == usedChars[g])
      return 1;
    }
  return 0;
}
