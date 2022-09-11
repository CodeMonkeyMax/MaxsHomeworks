#include "FPToolkit.c"
int main(){
	int n;
	char q;
	printf("ENTER n: ");
	scanf("%d", &n);
	// create window
	// clear
	// calculate 
	float diagonal, extSeg, rad;
	diagonal = 600*sqrt(2);
	rad = diagonal/(2*sqrt(2)+(2*n-2));
	
	// graphics stuff
	G_init_graphics(600, 600);
	G_rgb(0.8,0.8,0.8);
	G_clear();
	q=G_wait_key();
}