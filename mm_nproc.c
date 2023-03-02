/*
 * mm_nproc.c
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
  // printf("Function called\n");
  int * shared_variable = mmap(NULL, N * N * sizeof(NUMTYPE),
			       PROT_READ | PROT_WRITE,
			       MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  int num_child = N;
  for (unsigned int i = 0; i < N; i++) {
    // fork
    // printf("forking\n");
    int child_pid = fork();

    // check if clone is successful
    if (child_pid == -1) {
      exit(EXIT_FAILURE); // failed clone
    }; 

    if (child_pid == 0) {
      for (unsigned int x = 0 ; x < N ; x++) {
	unsigned int tidx = x + i * N;
	shared_variable[tidx] = 0;
	for (unsigned int d = 0 ; d < N ; d++) {
	  //printf("tidx is %d, i: %d, x: %d, d: %d\n", tidx, i, x, d);
	  shared_variable[tidx] += A[d + i * N] * B[x + d * N];
	}
      }
      exit(0);
    }
  }
  while (num_child > 0){
    wait(0);
    --num_child;
  }
  for (unsigned int i = 0; i < (N * N); i++) {
    //printf("assigning to C");
    C[i] = shared_variable[i];
  }
}

