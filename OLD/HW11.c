#include "FPToolkit.c"

int main() 
{
	int j, k; 
	double angle, x[2][100], y[2][100], n, i; //angle changes, x & y store n vertices, and i is i.
	char q;

	q='a';
	printf("q to quit. How many points?\n");
	scanf("%lf", &n);
  
	G_init_graphics(601, 601) ;
	i=0;
  
	while (q!='q'){
		G_rgb (0.1, 0.1, 0.1); // dark gray
		G_clear();
		j=0;
		while (j<n){
			G_rgb(0.0, 0.2, 0.6); // blue
			angle=(j/n +i/100)* 2*M_PI;
			x[1][j]=250*cos(angle) +300;
			y[1][j]=100*sin(angle) +150;
			G_fill_circle(x[1][j], y[1][j], 3);
			//printf("%lf %lf \n", x[j], y[j]);
			j++;
		}
		G_fill_polygon (x[1],y[1],n);
		
		j=0;
		while (j<n){
			G_rgb(0.0, 0.2, 0.6); // blue
			angle=(j/n)* 2*M_PI;
			x[0][j]=250*cos(angle) +300;
			y[0][j]=100*sin(angle) +450;
			G_fill_circle(x[0][j], y[0][j], 3);
			//printf("%lf %lf \n", x[j], y[j]);
			j++;
		}
		
		j=0;
		while (j<=n){ // Vertical Lines
			G_rgb (0.1, 0.1, 0.1); // dark gray
			G_line(x[0][j]+1,y[0][j],x[1][j]+1,y[1][j]);
			G_line(x[0][j]-1,y[0][j],x[1][j]-1,y[1][j]);
			G_rgb(0.95, 0.0, 0.65); // awesome pink
			G_line(x[0][j],y[0][j],x[1][j],y[1][j]);
			j++;
		}
		
		G_rgb(0.0, 0.2, 0.6); // blue
		G_fill_polygon (x[0],y[0],n);
		
		j=0;
		while (j<n){ // Deco Lines
			k=0;
			while(k<n){
				G_rgb(0.95, 0.0, 0.65); // awesome pink
				G_line(x[0][j],y[0][j],x[0][k],y[0][k]);
				G_line(x[1][j],y[1][j],x[1][k],y[1][k]);
				k++;
			}
			j++;
		}
		
		q=G_wait_key() ;
		i++;
	}
}