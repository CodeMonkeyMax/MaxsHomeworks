
#include "M2d_matrix_toolsS.c"

int main() {
	double a[3][3] = {{1, 2, 3}, {4, -1, 2}, {-3, 4, 7}};

	double b[3][3] = {{-3, 7, 6}, {1, 4, 5}, {8, 1, -2}};

	double c[3][3], d[3][3];

	M2d_mat_mult(c, a, b);
	// printf("Matrix c: \n");
	M2d_print_mat(c);
	// printf("Done with test 1\n");
	printf("\n");

	M2d_make_identity(d);
	for (int i = 1; i <= 3; i++) {
		// printf("i = %d\n", i);
		// printf("d:\n");
		// M2d_print_mat(d);
		M2d_mat_mult(d, c, d);
		// printf("c:\n");
		// M2d_print_mat(c);
		// printf("d:\n");
		// M2d_print_mat(d);
		// printf("\n\n");
	}
	M2d_print_mat(d);
	printf("\n");

	double x[100] = {100, 130, 140, 170};
	double y[100] = {70, 230, 515, 431};

	M2d_mat_mult_points(x, y, c, x, y, 4);

	for (int i = 0; i < 4; i++) {
		printf("%12.4lf %12.4lf\n", x[i], y[i]);
	}

	double e[3][3], A[2] = {100, 200};
	M2d_copy_mat(e, a);
	M2d_mat_mult_pt(A, e, A);
	printf("%lf %lf\n", A[0], A[1]);
}
