/*
 * mm_openmp.c
 *
 *  Created on: Jan 5, 2021
 *      Author: toky
 */

#include <omp.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <mm_test.h>

void mm (size_t N, NUMTYPE * A, NUMTYPE * B, NUMTYPE * C) {

  #pragma omp parallel
  for (unsigned int x = 0 ; x < N ; x++) {
    for (unsigned int y = 0 ; y < N ; y++) {
      unsigned int tidx = x + y * N ;
      C[tidx] = 0;
      for (unsigned int d = 0 ; d < N ; d++) {
        C[tidx] += A[d + y * N] * B[x + d * N] ;
      }
    }
  }
}

