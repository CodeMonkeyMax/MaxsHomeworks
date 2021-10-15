#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
int CharCounter();
int main(){
	char a[1000];
	char b[1000];
	char x[1000];
	int i, sa, sb, sx;
	printf("ENTER A WORD: ");
	scanf("%s", a);
	sa = CharCounter(a);
	//printf("\nDEBUG: WORD A IS %i CHARACTERS", sa);
	printf("ENTER YET ANOTHER WORD: ");
	scanf("%s", b);
	sb = CharCounter(b);
	//printf("\nDEBUG: WORD B IS %i CHARACTERS\n", sb);
	sx = sa+sb;
	while(i<sx){
		if(i<sa){
			//printf("\nDEBUG: i<sa.");
			x[i] = a[i];
			//printf("%c ",x[i]);
		} else if(i<sx) {
			//printf("\nDEBUG: i<sb.");
			x[i] = b[i-sa];
			//printf("%c ",x[i]);
		}
		i++;
	}
	i=0;
	printf("\n");
	while(i<sx){
		printf("%c",x[i]);
		i++;
	}
	printf("\n");
}

int CharCounter(char workingWord[]){
	int i=0;
	int charCount = 0;
	while (workingWord[i] != '\0'){
		charCount++;
		i++;
	}
	return charCount;
}