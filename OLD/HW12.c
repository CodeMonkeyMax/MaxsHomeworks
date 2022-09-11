#include "FPToolkit.c"
int main(){
	double click[2][2],n,d,sl,dx,dy,square[2][4]; // 2 click vertices, n, total distance, segment length
	int i, up;
	
	printf("Enter Number of Squares: ");
	scanf("%lf",&n);
	
	G_init_graphics(600, 600);
	G_rgb(0,0,0);
	G_clear();
	G_rgb(1,0,0);
	G_wait_click(click[0]);
	G_point(click[0][0],click[0][1]);
	G_wait_click(click[1]);
	G_point(click[1][0],click[1][1]);
	G_rgb(0,0,1);
	G_line(click[0][0],click[0][1],click[1][0],click[1][1]);
	G_rgb(1,0,0);
	G_circle(click[0][0],click[0][1],5);
	G_circle(click[1][0],click[1][1],5);
	
	G_wait_key();
	
	d=sqrt((click[0][0]-click[1][0])*(click[0][0]-click[1][0]) + (click[0][1]-click[1][1])*(click[0][1]-click[1][1]));
	
	sl = d/n;
	
	G_wait_key();
	
	dx=(click[0][0]-click[1][0])/n;
	dy=(click[0][1]-click[1][1])/n;
	
	i=0;
	while(i<n){ // SQUARE NEEDS TO BE A MULTIDIMENSIONAL ARRAY IN ORDER TO STORE BOTH X and Y VALUES
		square[0][0]=click[0][0]+dx*i;
		square[1][0]=click[0][1]+dy*i;
		
		square[0][1]=click[0][0]+dx*i;
		square[1][1]=click[0][1]+dy*(i+1);
		
		square[0][2]=square[0][1]-dy;
		square[1][2]=square[1][1]+dx;
		
		square[0][3]=square[0][0]-dy;
		square[1][3]=square[1][0]+dx;
		
		i++;
	}
	
	G_wait_key();
}