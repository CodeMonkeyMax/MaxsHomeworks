#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
//Homework lab 8: given n people, what is the probability that at least 2 people have birthday on the same day
int roll(int n);
int main(){
	double o, n, rn;
	int i;
	printf("For how many people would you like to test The \"Max's Bulletproof Birthday Algorithm?\"\n");
	scanf("%lf", &n); // n = number of people
	printf("How many times would you like the test run?\n");
	scanf("%lf", &rn); // rn = number of times to run test
	o=0;
	i=0;
	while(i<rn){
		if(roll(n) == 1){
			o++;
		}
		i++;
	}
	printf("%lf successes, \n", o);
	o=(100*o)/rn;
	printf("%lf %%.\n", o);
}

int roll(int n){
	double r, day[366]={0};
	int i, ro, o;
	i=0;
	o=0;
	while(i<n){
		r = drand48();
  	r = floor(365*r);
		ro = r;
		day[ro]++;
		//printf("Debug: day %d ++. \nIndex: %d\n\n", o, i);
		i++;
	}
	i=1;
	while(i<=365){
		if(day[i]>=2){
			//printf("2 or more Birthdays Occurred on day %d!\n", i);
			o=1;
		} else {
			//printf("No coincidence on day %d.\n", i);
		}
		i++;
	}
	return o;
}