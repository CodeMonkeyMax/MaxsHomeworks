#include "FPToolkit.c"
int main()
{
	float swidth, sheight, i;
	double lowleftx, lowlefty, width, height;
	double x[10], y[10], numxy;
	double a[20], b[20], numab;

	swidth = 600 ;  sheight = 600 ; // 600x600 is about the largest Repl supports
	G_init_graphics (swidth,sheight) ;  // interactive graphics
   
	// clear the screen in a given color
	G_rgb (0.1, 0.1, 0.1) ; // dark gray
	G_clear () ;

	/*
	// draw a point
	G_rgb (1.0, 0.0, 0.0) ; // red
	G_point (200, 580) ; // hard to see
  
  
	// draw a line
	G_rgb (0.0, 1.0, 0.0) ; // green
	G_line (0,0, swidth-1, sheight-1) ;
	*/
  
  
	//Let's Make Graph Paper DONE
	/*
	G_rgb (1.0, 0.2, 0.2) ; // darker red
	i=0;
	while(i<swidth){
  	G_line (i,0, i, sheight-1);
  	i+=8;
	}
	*/
	
	/*
	i=0;
	while(i<sheight){
  	G_line (0,i, swidth, i);
  	i+=8;
	}
  
	// Let's make diaggies
	G_rgb (1.0, 0, 0.6) ; //
	i=0;
	while(i<sheight){
  	G_line (0,sheight-i, i, 0);
  	i+=12;
  	//G_wait_key() ;
	}
	G_rgb (0.0, 0.1, 0.8) ; //
	i=0;
	while(i<sheight){
  	G_line (0,sheight-i, i, 0);
  	i+=24;
	}
	*/
	
	// CIRCLES
	int key, f;
	f=0;
	float colors[2][2][2];
	//colors[0][0][0] = 0.95, 0, 0.65;
	//colors[1][1][1] = 0.0, 0.2, 0.6;
	float j;
	while(f<20){
		i=swidth/2-20;
		j=1;
		while(i>0){
			key=G_wait_key();
			G_rgb (0.95, 0, 0.65);
			G_fill_circle(swidth/2,sheight/2,j*i);
			G_rgb (0.1, 0.1, 0.1) ;
			G_circle(swidth/2,sheight/2,j*i);
			j+=0.05;
			
			key=G_wait_key();
			G_rgb (0.0, 0.2, 0.6);
			G_fill_circle(swidth/2,sheight/2,(i-10)*j);
			G_rgb (0.1, 0.1, 0.1) ;
			G_circle(swidth/2,sheight/2,(i-10)*j);
			i-=20;
			j+=0.05;
		}
		i=swidth/2-20;
		j=1;
		while(i>0){
			key=G_wait_key();
			G_rgb (0.0, 0.2, 0.6);
			G_fill_circle(swidth/2,sheight/2,j*i);
			G_rgb (0.1, 0.1, 0.1) ;
			G_circle(swidth/2,sheight/2,j*i);
			j+=0.05;
			
			key=G_wait_key();
			G_rgb (0.95, 0, 0.65);
			G_fill_circle(swidth/2,sheight/2,(i-10)*j);
			G_rgb (0.1, 0.1, 0.1) ;
			G_circle(swidth/2,sheight/2,(i-10)*j);
			i-=20;
			j+=0.05;
		}
		f++;
	}
	

	/*
	// aligned rectangles
	G_rgb (0.0, 0.0, 1.0) ; // blue
	lowleftx = 200 ; lowlefty = 50 ; width = 10 ; height = 30 ;
	G_rectangle (lowleftx, lowlefty, width, height) ;
	lowleftx = 250 ; 
	G_fill_rectangle (lowleftx, lowlefty, width, height) ;
   
	// triangles
	G_rgb (1.0, 1.0, 0.0) ; // yellow
	G_triangle (10, 300,  40,300,  60,250) ;
	G_fill_triangle (10,100,  40,100,  60,150) ;
   
	// circles   
	G_rgb (1.0, 0.5, 0.0) ; // orange
	G_circle (100, 300, 75) ;
	G_fill_circle (370, 200, 50) ;
   
	// polygons
	G_rgb (0.0, 0.0, 0.0) ; // black
	x[0] = 100 ;   y[0] = 100 ;
	x[1] = 100 ;   y[1] = 300 ;
	x[2] = 300 ;   y[2] = 300 ;
	x[3] = 300 ;   y[3] = 100 ;
	x[4] = 200 ;   y[4] = 175 ;
	numxy = 5 ;
	G_polygon (x,y,numxy) ;

	G_rgb (0.4, 0.2, 0.1) ; // brown
	a[0] = 300 ;   b[0] = 400 ;
	a[1] = 350 ;   b[1] = 450 ;
	a[2] = 275 ;   b[2] = 500 ;
	a[3] = 125 ;   b[3] = 400 ;
	numab = 4 ;
	G_fill_polygon (a,b,numab) ;
	*/
	//===============================================
   
	double p[2], q[2] ;

	G_rgb(1,0,0) ;
	
	key = G_wait_key(); // pause so user can see results

	G_save_to_bmp_file("demo.bmp") ;
}
