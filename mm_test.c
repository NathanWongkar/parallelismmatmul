#include <mm_test.h>

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <sys/time.h>


int main (int argc, char** argv) {

  assert (argc == 2);
  assert (argv);
  
  // printf("Opening file\n");
  FILE *ftest_file;
  int mat_size;

  ftest_file = fopen(argv[1], "r");
  /* get the size of each matrix */
  if(fscanf(ftest_file, "%d", &mat_size)){};

  /*initialise the matrix*/
  // printf("Initialising matrix A\n");
  NUMTYPE *A = (NUMTYPE*) malloc(mat_size * mat_size * sizeof(NUMTYPE));
  for (int y = 0; y < mat_size; y++) {
    for (int x = 0; x < mat_size; x++) {
      if(fscanf(ftest_file, NUMFORMAT, &A[x + y * mat_size])){};
    } 
  }

  // printf("Initialising matrix B\n");
  NUMTYPE *B = (NUMTYPE*) malloc(mat_size * mat_size * sizeof(NUMTYPE));
  for (int y = 0; y < mat_size; y++) {
    for (int x = 0; x < mat_size; x++) {
      if(fscanf(ftest_file, NUMFORMAT, &B[x + y * mat_size])){};
    } 
  }

  // printf("Initialising matrix C\n");
  NUMTYPE *C = (NUMTYPE*) malloc(mat_size * mat_size * sizeof(NUMTYPE));
  for (int y = 0; y < mat_size; y++) {
    for (int x = 0; x < mat_size; x++) {
      if(fscanf(ftest_file, NUMFORMAT, &C[x + y * mat_size])){};
    } 
  }

  fclose(ftest_file);

  /* initialising D */
  NUMTYPE *D = (NUMTYPE*) malloc(mat_size * mat_size * sizeof(NUMTYPE));

  /* applying matrix multiplication */
  mm(mat_size, A, B, D);
  
  /* assert that C == D */
  /*for (int y = 0; y < mat_size; y++) {
    for (int x = 0; x < mat_size; x++) {
      assert(C[x + y * mat_size] == D[x + y * mat_size]);
    } 
    }*/

  /* Output */
  printf("%d\n", mat_size);
  // printf("Matrix A: \n");
  for (int y = 0; y < mat_size; y++) {
    for (int x = 0; x < mat_size; x++) {
      printf(NUMFORMAT, A[x + y * mat_size]);
      if (x != mat_size - 1) {
        printf(" ");
      }
    } 
    printf("\n");
  }

  // printf("Matrix B: \n");
  for (int y = 0; y < mat_size; y++) {
    for (int x = 0; x < mat_size; x++) {
      printf(NUMFORMAT, B[x + y * mat_size]);
      if (x != mat_size - 1) {
        printf(" ");
      }
    } 
    printf("\n");
  }

  // printf("Matrix D: \n");
  for (int y = 0; y < mat_size; y++) {
    for (int x = 0; x < mat_size; x++) {
      printf(NUMFORMAT, D[x + y * mat_size]);
      if (x != mat_size - 1) {
        printf(" ");
      }
    } 
    printf("\n");
  }
}
