#!/bin/sh
set -x
 
gcc -Wall -g -o race                race.c                -lpthread
gcc -Wall -g -o race_sol            race_sol.c            -lpthread

gcc -Wall -g -o interlock           interlock.c           -lpthread
gcc -Wall -g -o interlock_sol       interlock_sol.c       -lpthread

gcc -Wall -g -o sync_child_mnc      sync_child_mnc.c      -lpthread
gcc -Wall -g -o sync_child_mnc_sol  sync_child_mnc_sol.c  -lpthread

gcc -Wall -g -o p-c_sem   p-c_sem.c   -lpthread
gcc -Wall -g -o r-w_sem   r-w_sem.c   -lpthread

gcc -Wall -g -o p-c_mnc   p-c_mnc.c   -lpthread
gcc -Wall -g -o r-w_mnc   r-w_mnc.c   -lpthread

# rm race race_sol interlock interlock_sol sync_child_mnc sync_child_mnc_sol p-c_sem  r-w_mnc p-c_mnc r-w_sem 

