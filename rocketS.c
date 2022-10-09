#include "FPToolkit.c"
#include "M2d_matrix_tools.c"


int main()
{
  // rocket
  double rx[8] = {0, 16,  7,  7,  0, -7, -7, -16 } ;
  double ry[8] = {0,  0, 15, 35, 50, 35, 15,   0 } ;

  G_init_graphics(700,700) ;  

  G_rgb(0,0,0) ;
  G_clear() ;
  G_rgb(0,1,0) ;
  G_fill_polygon(rx,ry,8) ;
  G_wait_key() ;
}
