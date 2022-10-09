#include "FPToolkit.c"
#include "M2d_matrix_toolsS.c"
#include "maxpolytools.c"
#include <math.h>
#include <stdio.h>

int main() {
	double mat[3][3];
	printf("make_identity\n");
	M2d_make_identity(mat);
	M2d_print_mat(mat);
	printf("\n");

	printf("translating by 50,60\n");
	M2d_make_translation(mat, 50, 60);
	M2d_print_mat(mat);
	printf("\n");

	printf("scaling by 2\n");
	M2d_make_scaling(mat, 2, 2);
	M2d_print_mat(mat);
	printf("\n");

	printf("rotating by 90 degrees\n");
	M2d_make_rotation(mat, 2 * M_PI);
	M2d_print_mat(mat);
	printf("\n");
}
