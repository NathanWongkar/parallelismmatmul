PROGS := mm_seq mm_proc mm_nproc mm_nthreads mm_openmp
CFLAGS := -O3 -Wall -Werror -Wextra -fopenmp
CC := gcc
TESTS := test2 test32 test500


all : ${PROGS}

test : ${TESTS}

mm_% : mm_%.c mm_test.c mm_test.h
	${CC} mm_$*.c mm_test.c -o $@ -I . ${CFLAGS}

mmf_% : mm_%.c mm_test.c mm_test.h
	${CC} mm_$*.c mm_test.c -D DOUBLE_MM -o $@ -I . ${CFLAGS}

mmi_% : mm_%.c mm_test.c mm_test.h
	${CC} mm_$*.c mm_test.c -D INTEGER_MM -o $@ -I . ${CFLAGS}

test% : test%.txt ${PROGS}
	./mm_seq test$*.txt > tmp; diff -B tmp test$*.txt;
	./mm_proc test$*.txt > tmp; diff -B tmp test$*.txt;
	./mm_nproc test$*.txt > tmp; diff -B tmp test$*.txt;
	./mm_nthreads test$*.txt > tmp; diff -B tmp test$*.txt;
	./mm_openmp test$*.txt > tmp; diff -B tmp test$*.txt;

benchmark : ${PROGS}
	echo mm_seq for test500.txt;
	time -p ./mm_seq test500.txt 1> tmp;
	echo ----------------------------------;
	echo mm_proc for test500.txt;
	time -p ./mm_proc test500.txt 1> tmp;
	echo ----------------------------------;
	echo mm_nproc for test500.txt;
	time -p ./mm_nproc test500.txt 1> tmp;
	echo ----------------------------------;
	echo mm_nthreads for test500.txt;
	time -p ./mm_nthreads test500.txt 1> tmp;
	echo ----------------------------------;
	echo mm_openmp for test500.txt;
	time -p ./mm_openmp test500.txt 1> tmp;

.PRECIOUS: ./mm_seq ./mm_proc ./mm_nproc ./mm_threads ./mm_openmp

clean :
	rm -f ${PROGS} *~
