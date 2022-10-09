#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int fac (int n)
{
	int i, r;
	r = 1;
	for (i=1 ; i <= n ; i++){
		r = r * i ;
	}
	return r ;
}

int main(){
	int numFriends, numInvites, numChoices ;
	
	printf("how many friends do you have?") ;
	scanf("%d", &numFriends) ;
	printf("\nhow many invitations to your party?") ;
	scanf("%d", &numInvites) ;
	numChoices = fac(numFriends)/(fac(numInvites) * fac(numFriends-numInvites)) ;
	printf("%d choices \n", numChoices) ;
}
