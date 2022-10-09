#include <stdio.h>


int  main(int argc, char **argv)
{
  int i,j,sum ;

  for (i = 0 ; i < argc ; i++) {

    printf("argv[%d] is %s\n", i, argv[i]) ;

  }
  

  sum = 0 ;
  for (i = 0 ; i < argc ; i++) {

     j = 0 ;
     while (argv[i][j] != '\0') { 
       j++ ;
     }
     printf("the length of the word is %d\n",j) ;
     sum += j ;
  }

  printf("The total number of letters is %d\n",sum) ;

}



