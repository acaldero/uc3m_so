#!/bin/sh
set -x
 
gcc -Wall -g -o peticion.o -c peticion.c
gcc -Wall -g -o 1 1_sequential.c -lpthread peticion.o
gcc -Wall -g -o 2 2_fork.c -lpthread peticion.o
gcc -Wall -g -o 3 3_threads_ondemand.c -lpthread peticion.o
gcc -Wall -g -o 4 4_threads_pool.c -lpthread peticion.o

