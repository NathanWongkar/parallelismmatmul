/*
 * mm_proc.c
 *
 *  Created on: Jan 5, 2021
 *      Author: toky
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <mm_test.h>


void mm (size_t N, NUMTYPE * A, NUMTYPE * B, NUMTYPE * C) {
  // create a shared variable
  int * shared_variable = mmap(NULL, N * N * sizeof(NUMTYPE),
			       PROT_READ | PROT_WRITE,
			       MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  // fork
  int child_pid = fork();

  // check if clone is successful
  if (child_pid == -1) {
    exit(EXIT_FAILURE); // failed clone
  }

  unsigned int child_iter_end = N/2;
 
  if (child_pid == 0) {
    for (unsigned int x = 0 ; x < N ; x++) {
      for (unsigned int y = 0 ; y < child_iter_end ; y++) {
	unsigned int tidx = x + y * N ;
	shared_variable[tidx] = 0;
	for (unsigned int d = 0 ; d < N ; d++) {
	  //printf("tidx is %d, y: %d, x: %d, d: %d\n", tidx, y, x, d);
	  shared_variable[tidx] += A[d + y * N] * B[x + d * N] ;
	}
      }
    }
    exit(0);
  } else {
    for (unsigned int x = 0; x < N ; x++) {
      for (unsigned int y = child_iter_end ; y < N ; y++) {
	unsigned int tidx = x + y * N ;
	shared_variable[tidx] = 0;
	for (unsigned int d = 0 ; d < N ; d++) {
	  // printf("tidx is %d, y: %d, x: %d, d: %d\n", tidx, y, x, d);
	  shared_variable[tidx] += A[d + y * N] * B[x + d * N] ;
	}
      }
    }
    wait(0);
  }
  for (unsigned int i = 0; i < (N * N); i ++) {
    // printf("Assigning to C");
    C[i] = shared_variable[i];
  }
}

