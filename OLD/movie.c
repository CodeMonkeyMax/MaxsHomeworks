#include "FPToolkit.c"
int main()
{
	double swidth, sheight, i, n, r;
	int j,h,k;
	double lowleftx, lowlefty, width, height;
	double x[100], y[100], numxy;
	double a, b, numab;

	printf("Enter number of points: ");
	scanf("%lf", &n);
	
	swidth = 600 ;  sheight = 600 ; // 600x600 is about the largest Repl supports
	G_init_graphics (swidth,sheight) ;  // interactive graphics

	// clear the screen in a given color
	

	int key, f;
	f=0;
	i=0;
	//double colors[2][3];
	
	//colors[0][0] = 0.95;
	//colors[0][1] = 0;
	//colors[0][2] = 0.65;
	
	//colors[1][n] = 0.0, 0.2, 0.6;
	r = swidth*4/10;
	k=0;
	key = G_wait_key(); // pause so user can see results
	
	while(key!='q'){ // BIG loop. re-does everything
		G_rgb (0.1, 0.1, 0.1); // dark gray
		G_clear ();
		G_rgb(0.0, 0.2, 0.6);
		G_circle(swidth/2, sheight/2, r);
	
		G_rgb(0.95, 0.0, 0.65);
		i=0;
		while(i<n){ // This guy places AND ASSIGNS points
			j=i;
			a=2*M_PI*(i/n+k/360);
			x[j]=cos(a)*r+swidth/2;
			y[j]=sin(a)*r+sheight/2;
			G_fill_circle (x[j], y[j], 3);
			i++;
		}
		
		G_rgb(0.0, 0.2, 0.6);
		G_fill_polygon (x, y, n); // Place polygon
		
		G_rgb(0.95, 0.0, 0.65);
		j=0;
		
		while(j<n){ // Draw lines
			h=0;
			while(h<n){
				G_line(x[j],y[j],x[h],y[h]);
				h++;
			}
			j++;
	 	}
	 	key = G_wait_key();
	 	k++;
	}
	
	double p[2], q[2] ;

	G_rgb(1,0,0) ;
	
	

	G_save_to_bmp_file("demo.bmp") ;
}
