#include <stdio.h>
#include "matrix.h"

int main ( int argc, char * argv[] ) {
	Matrix * A = matrix_new ( 5, 5 );

  matrix_set ( A, 0, 0, 1 ); matrix_set ( A, 0, 1, 0 ); matrix_set ( A, 0, 2, 7 ); matrix_set ( A, 0, 3, 3 ); matrix_set ( A, 0, 4, 6 );
  matrix_set ( A, 1, 0, 3 ); matrix_set ( A, 1, 1, 4 ); matrix_set ( A, 1, 2, 42 ); matrix_set ( A, 1, 3, 1 ); matrix_set ( A, 1, 4, 23 );
  matrix_set ( A, 2, 0, 3 ); matrix_set ( A, 2, 1, 2 ); matrix_set ( A, 2, 2, 32 ); matrix_set ( A, 2, 3, 2 ); matrix_set ( A, 2, 4, 21 );
  matrix_set ( A, 3, 0, 8 ); matrix_set ( A, 3, 1, 1 ); matrix_set ( A, 3, 2, 9 ); matrix_set ( A, 3, 3, 7 ); matrix_set ( A, 3, 4, 25 );
	matrix_set ( A, 4, 0, 2 ); matrix_set ( A, 4, 1, 6 ); matrix_set ( A, 4, 2, 2 ); matrix_set ( A, 4, 3, 2 ); matrix_set ( A, 4, 4, 9 );

	printf ( "A:\n" );
	matrix_print ( A );
	printf ( "\n" );

	Matrix * B = matrix_random ( 6, 6 );
	matrix_print ( B );
	printf ( "\n" );
	Matrix * C = matrix_inverse ( B );
	Matrix * D = matrix_mult ( B, C );

	matrix_print ( C );
	printf ( "\n" );
	matrix_print ( D );
	printf ( "\n" );

}
