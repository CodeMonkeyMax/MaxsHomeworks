#include "FPToolkit.c"

int main() 
{
  int j; 
  double angle, x[100], y[100], n, i ;
  char q;
  q='a';
  printf("q to quit. How many points?\n");
  scanf("%lf", &n);
  G_init_graphics(400, 400) ;
  i=0;
  while (q!='q'){
    G_rgb(0.8,0.8,0.8) ;
    G_clear();
    G_rgb(1,.5,0) ;
    G_circle(300,300,250);
    j=0;
    while (j<n){
      angle=(j/n +i/100)* 2*M_PI;
      x[j]=250*cos(angle) +300;
      y[j]=250*sin(angle) +300;
      G_fill_circle(x[j], y[j], 3);
      //printf("%lf %lf \n", x[j], y[j]);
      j++;
    }
    G_fill_polygon (x,y,n) ;
    q=G_wait_key() ;
    i++;
  }
}
