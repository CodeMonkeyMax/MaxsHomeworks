#include "FPToolkit.c"

int main() 
{
	int j, h; 
	double angle, x[100], y[100], n, i, ellipseHeight, ellipseWidth;
	char q;
	q='a';
	printf("q to quit. How many points?\n");
	scanf("%lf", &n);
	if(n>100) n=100;
	G_init_graphics(601, 601) ;
	i=0;
	
	ellipseHeight = 150;
	ellipseWidth = 250;
	
	while (q!='q'){
		G_rgb (0.1, 0.1, 0.1); // dark gray
		G_clear ();
		G_rgb(0.0, 0.2, 0.6); // dark blue
		//G_circle(300,300,250);
		j=0;
		G_rgb(0.95, 0.0, 0.65); // awesome pink
		
		while (j<n){
			angle=(j/n +i/100)* 2*M_PI;
			x[j]=ellipseWidth*cos(angle) +300;
			y[j]=ellipseHeight*sin(angle) +300;
			G_fill_circle(x[j], y[j], 3);
			//printf("%lf %lf \n", x[j], y[j]);
			j++;
		}
		
		G_rgb(0.0, 0.2, 0.6); // dark blue
		G_fill_polygon (x,y,n);
		
		/*
		j=0;
		G_rgb (0.1, 0.1, 0.1); // dark gray
		while(j<n){ // Draw lines
			h=0;
			while(h<n){
				G_line(x[j]+1.5,y[j]+1.5,x[h]+1.5,y[h]+1.5);
				h++;
			}
			j++;
	 	}
	 	*/
	 	
		j=0;
		G_rgb(0.95, 0.0, 0.65); // awesome pink
		while(j<n){ // Draw lines
			h=0;
			while(h<n){
				G_line(x[j],y[j],x[h],y[h]);
				h++;
			}
			j++;
	 	}
	 	
	 	/*
	 	j=0;
		G_rgb (0.1, 0.1, 0.1); // dark gray
		while(j<n){ // Draw lines
			h=0;
			while(h<n){
				G_line(x[j]-1.5,y[j]-1.5,x[h]-1.5,y[h]-1.5);
				h++;
			}
			j++;
	 	}
	 	*/
		
		q=G_wait_key() ;
		i++;
	}
}
