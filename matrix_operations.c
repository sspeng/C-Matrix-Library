#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

Matrix * matrix_add ( Matrix * A, Matrix * B ) {
  ASSERT ( A->rows == B->rows && A->columns == B->columns );
  Matrix * C = matrix_new ( A->rows, A->columns );
  for ( int i=0; i<A->rows; i++ ) {
    for ( int j=0; j<A->columns; j++ ) {
      matrix_set(C, i, j, matrix_get(A,i,j) + matrix_get(B,i,j) );
    }
  }
  return C;
}

Matrix * matrix_minor ( Matrix * M, int n ) {
  ASSERT ( 0 <= n && n < M->columns );
  Matrix * P = matrix_new ( M->rows - 1, M->columns - 1 );
  for ( int i=1; i<M->rows; i++ ) {
    for ( int j=0; j<n; j++ ) {
      matrix_set(P,i-1,j,matrix_get(M,i,j));
    }
  }
  for ( int i=1; i<M->rows; i++ ) {
    for ( int j=n+1; j<M->columns; j++ ) {
      matrix_set(P,i-1,j-1,matrix_get(M,i,j));
    }
  }
  return P;
}

Matrix * matrix_minors ( Matrix * M, int m, int n ) { // finds minor matrix of M, where the mth row and nth column are "crossed out"
  int i, j;
  int k = 0; // current row of P
  int l = 0; // current column of P
  ASSERT ( (m>=0 && m<(M->rows)) && (n>=0 && n<(M->columns)) ) // make sure m and n are within range
  ASSERT ( M->rows == M->columns ); // non-square matrices cannot have minor matrices
  Matrix * P = matrix_new ( M->rows - 1, M->columns - 1 );

  for ( i=0; i<(M->rows); i++ ) { // check each element in each row of M
    for ( j=0; j<(M->columns); j++ ) { // check each element in each column of M
      if ( (j!=n) && (i!=m) ) { // if the element is not on either of the "crossed out" rows/columns
        matrix_set ( P, k, l, matrix_get (M, i, j) );
        l++;
        if ( l > ((P->columns)-1) ) { // make sure l doesn't go past the dimensions of P
          l = 0;
          k++;
        }
      }
    }
  }
  return P;
}

Matrix * matrix_scale ( Matrix * M, double s ) {
  int i, j; // number of rows and columns in matrix M
  int m, n; // current row and column in matrix M

  i = M->rows;
  j = M->columns;
  Matrix * N = matrix_new ( i, j );
  for ( m=0; m<i; m++ ) { // for each row in the matrix
    for ( n=0; n<j; n++ ) {
      matrix_set ( N, m, n, s*(matrix_get(M,m,n)) );
    }
  }
  return N;
}

Matrix * matrix_transpose ( Matrix * M ) {
  int i, j; // current row and column of N in for loop

  Matrix * N = matrix_new ( M->columns, M->rows );
  for ( i=0; i<(M->columns); i++ ) { // for each row in N
    for ( j=0; j<(M->rows); j++ ) { // for each column in N
      matrix_set ( N, i, j, matrix_get(M,j,i) );
    }
  }
  return N; // returns newly transposed matrix
}

Matrix * matrix_mult ( Matrix * A, Matrix * B ) {
  int m, n; // current row and column in N for for loop
  int i;
  double sum; // keeps track of current dot product

  ASSERT ( A->columns == B->rows ); // check dimensions
  Matrix * N = matrix_new ( A->rows, B->columns );
  for ( m=0; m<(A->rows); m++ ) { // for each row of N
    for ( n=0; n<(B->columns); n++ ) { // for each column of N
      sum = 0; // each new entry of N has a new dot product
      for ( i=0; i<(A->columns); i++ ) { // dot product of mth row A and nth column B
        sum += matrix_get (A,m,i) * matrix_get (B,i,n);
      }
      matrix_set ( N, m, n, sum );
    }
  }
  return N;
}

Matrix * matrix_power ( Matrix * M, int n ) {
  int i;
  Matrix * I;
  Matrix * J;
  Matrix * L = M;
  Matrix * N = M;
  ASSERT ( M->rows == M->columns ); // non-square matrices are not defined for exponentiation

  if ( n < 0 ) {
    ASSERT ( matrix_det ( M ) != 0.0 ); // only invertible matrices can have negative powers
    I = matrix_inverse ( M );
    J = I;
    for ( i=0; i<(abs(n)-1); i++ ) {
      J = matrix_mult ( J, I );
    }
    return J;
  } else if ( n == 0 ) {
    return matrix_identity ( M->rows );
  } else if ( n == 1 ) {
    return M;
  } else {
    for ( i=0; i<(n-1); i++ ) {
      N = matrix_mult ( N, L );
    }
    return N;
  }
}

Matrix * matrix_inverse ( Matrix * M ) {
  int i, j;
  double c = -1.0; // used for applying cofactors
  ASSERT ( matrix_det ( M ) != 0.0 ); // singular matrices cannot be inverted

  // find matrix of minors and apply cofactors
  Matrix * MM = matrix_new ( M->rows, M->columns );
  for ( i=0; i<(M->rows); i++ ) { // for each row in the matrix of minors
    c = c * (-1.0);
    for ( j=0; j<(M->columns); j++ ) { // for each column in the matrix of minors
      matrix_set ( MM, i, j, c * (matrix_det(matrix_minors(M,i,j))) );
      c = c * (-1.0);
    }
  }
  MM = matrix_scale ( matrix_transpose(MM), ( 1.0/(matrix_det(M)) ) );
  return MM;
}

double matrix_det ( Matrix * M ) {
  ASSERT ( M->rows == M->columns ); // non-square matrices cannot have determinants
  if ( M->rows == 1 && M->columns == 1 ) {
    return matrix_get(M,0,0);
  } else {
    double sign = 1,
           sum = 0;
    for ( int i=0; i<M->columns; i++ ) {
      Matrix * P = matrix_minor ( M, i );
      sum += sign * matrix_get(M,0,i) * matrix_det(P);
      sign *= -1;
      matrix_destroy ( P );
    }
    return sum;
  }
}

int matrix_equal ( Matrix * A, Matrix * B ) {
  int i, j; // row and column of matrix A
  int k, l; // row and column of matrix B
  int n, m; // row and column during for loop

  i = A->rows;
  j = A->columns;
  k = B->rows;
  l = B->columns;

  if ( (i != k) || (j != l) ) { // matrices with different dimensions cannot be equal
    return ( 0 );
  }
  for ( m=0; m<i; m++ ) { // for each row of the matrix
    for ( n=0; n<j; n++ ) { // for each column of the matrix
      if ( matrix_get(A,m,n) != matrix_get(B,m,n) ) {
        return ( 0 );
      }
    }
  }
  return ( 1 );
}
