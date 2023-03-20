#!/bin/sh
set -x

# librería dinámica
gcc -Wall -g -fPIC -o libhola.o -c libhola.c
#gcc -shared -Wl,-soname,libhola.so -o libhola.so.1.0 libhola.o
#ln -s libhola.so.1.0 libhola.so
gcc -shared -o libhola.so libhola.o

# ejecutable con librería estática
#gcc -Wall -g -o main main.c -lhola -L./
gcc -Wall -g -o main main.c -ldl
env LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. ./main

