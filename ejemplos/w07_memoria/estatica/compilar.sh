#!/bin/sh
set -x

# librería estática
gcc -Wall -g -o libhola.o -c libhola.c
ar rcs libhola.a libhola.o

# ejecutable con librería estática
gcc -Wall -g -o main main.c -lhola -L./
./main

