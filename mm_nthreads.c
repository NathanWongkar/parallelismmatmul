/*
 * mm_nthreads.c
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
#include <pthread.h>

// reference
// https://www.geeksforgeeks.org/create-n-child-process-parent-process-using-fork-c/

// create a structure to hold all the information of the arguments
struct Args {
  size_t N;
  NUMTYPE * A;
  NUMTYPE * B;
  NUMTYPE * shared_variable;
  size_t row;
};

// create a fuction to run when the threa is created
void * thread_mm (void * arg_input) {
  struct Args * arg = (struct Args *)arg_input;
  unsigned int i = arg->row;
  unsigned int N = arg->N;
  for (unsigned int x = 0 ; x < N ; x++) {
    unsigned int tidx = x + i * N;
    (arg->shared_variable)[tidx] = 0;
    for (unsigned int d = 0 ; d < N ; d++) {
      (arg->shared_variable)[tidx] += (arg->A)[d + i * N] * (arg->B)[x + d * N];
    }
  }
  return NULL;
};

void mm (size_t N, NUMTYPE * A, NUMTYPE * B, NUMTYPE * C) {
  int * shared_variable = mmap(NULL, N * N * sizeof(NUMTYPE),
			       PROT_READ | PROT_WRITE,
			       MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  struct Args arg;
  arg.N = N;
  arg.A = A;
  arg.B = B;
  arg.shared_variable = shared_variable;
  arg.row = 0;

  pthread_t thread_id;
  int rc;
  for (unsigned int i = 0; i < N; i++) {
    arg.row = i;
    rc = pthread_create(&thread_id, NULL, thread_mm, (void *)&arg);
    assert(rc ==0);

    // wait for thread to finish
    rc = pthread_join(thread_id, NULL);
    assert(rc ==0);
  };
  for (unsigned int i = 0; i < (N * N); i++) {
    //printf("assigning to C");
    C[i] = shared_variable[i];
  }
}

