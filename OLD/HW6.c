#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
//Homework lab 6: enter a word, is it a palindrome, yes or no
// # # E.g. racecar, tacocat, kayak, mom # # # # # # # # # #
int CharCounter(char workingWord[]);
int main() {
	char word[1000];
	int i, s;
	printf("ENTER A PALINDROME: ");
	scanf("%s", word);
	s = CharCounter(word);
	printf("That word is %i characters long. Is it a PALINDROME? Time will tell.", s);
	i=0;
	while(i<s){
		word[i]=toupper(word[i]);
		word[s-i-1]=toupper(word[s-i-1]);
		//printf("\n%c == %c?", word[i], word[s-i-1]);
		if(word[i]==word[s-i-1]){
			//printf(" That seems palindrome-y...");
		} else {
			printf("\n%c == %c?", word[i], word[s-i-1]);
			printf("\nHA! FAKE PALINDROME! LIAR!\n");
			break;
		}
		if (i==s-1){
			printf("\nThat word would appear to be a palindrome.\n");
		}
		i++;
	}
}

int CharCounter(char workingWord[]){
	int i=0;
	int charCount;
	while (workingWord[i] != '\0'){
		charCount++;
		i++;
	}
	charCount -= 1; //don't wanna count the \0, oh well.
	return charCount;
}