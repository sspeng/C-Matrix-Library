C Matrix Library
================

### Featured Operations
###### Building Matrices
- Create a matrix with a defined number of rows and columns, and user-defined
values
- Create a matrix with a random number of rows and columns, and random
values
- Create an identity matrix with a defined number of rows and columns, given by
a user-defined value of n
- Import a pre-existing matrix

###### Matrix Operations
- Addition, Subtraction
- Multiplication, Division
- Scaling by a double, s
- Raising a matrix to an integer power, n
- Finding the inverse of a matrix (if it exists)

### Testing
1. Testing matrix_equal:
  I tested matrices of different sizes against each other (which resulted in the
  desired output of 0), matrices of equal sizes but different values (output is
  0), matrices of equal sizes and equal values (output is 1), and the n identity
  matrix against the matrix multiplication of AA^-1 of dimension 1. The final
  case resulted in a 0 because of the "-0.00000000"s that arose from the
  multiplication of negative values in the matrices.

2. Testing matrix_identity:
  I tested matrices with negative dimensions (output is ASSERT error), a
  dimension of 1 (output is a 1x1 matrix), and positive dimensions (correct
  output, which is an nxn matrix with 1s down the diagonal and 0s everywhere
  else).

3. Testing matrix_scale:
  I tested matrices by inputting scalars that were positive, negative, zero,
  and non-integer. The expected output was received.

4. Testing matrix_transpose:
  I tested matrices of all sizes, square and non-square. The expected output
  was received.

5. Testing matrix_mult:
  I tested multiplication of two matrices whose dimensions are not allowed
  (output was an ASSERT error, as expected), and multiplication of two matrices
  whose dimensions are allowed (output was the product matrix, as expected).

6. Testing matrix_power:
  I tested this function with inputting negative values (-1 results in just the
  inverse of the matrix (assuming it's an invertible matrix) and any other
  negative number results in the inverse of the matrix multiplied by itself
  abs(n) times, as expected), inputting zero for the n value (results in the
  identity matrix, which is expected), inputting 1 for the n value (results in
  the original matrix, which is expected), and inputting positive integers for
  n (results in the correct final matrix, as checked against a matrix
  multiplication calculator). All of the previously mentioned tests were with
  square matrices. Any input of a non-square matrix results in an ASSERT error,
  which is expected as non-square matrices are not defined for exponentiation.

7. Testing matrix_inverse:
  I tested this function by inputting square matrices with zero determinants
  (results in an ASSERT error which is expected, since singular matrices cannot
  be inverted) and non-zero determinants. The outputted inverse matrix was
  checked against an inverse matrix calculator. The outputted inverse matrix was
  also multiplied with the original matrix using matrix_mult, and then printed
  using matrix_print to make sure that the identity matrix was outputted. Any
  test input with a non-square matrix resulted in an ASSERT error, which is
  expected since non-square matrices cannot have inverses.
