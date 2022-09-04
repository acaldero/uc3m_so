
/*
 *  Copyright 2020-2022 ARCOS.INF.UC3M.ES
 *
 *  This file is part of Operaring System Labs (OSL).
 *
 *  OSL is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  OSL is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with OSL.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS     5

pthread_t threads[NUM_THREADS];

void *th_function ( void *arg )
{
    printf("Hello world from thread #%ld!\n", (long)arg) ;
    pthread_exit(NULL) ;
}

int main ( int argc, char *argv[] )
{
    for (int t=0; t<NUM_THREADS; t++)
    {
           int rc = pthread_create(&(threads[t]), NULL, th_function, (void *)(long)t) ;
           if (rc)
           {
	       printf("ERROR from pthread_create(): %d\n", rc) ;
	       exit(-1) ;
	   }
    }

    for (int t=0; t<NUM_THREADS; t++)
    {
           int rc = pthread_join(threads[t], NULL) ;
           if (rc)
           {
	       printf("ERROR from pthread_join(): %d\n", rc) ;
	       exit(-1) ;
	   }
    }

    pthread_exit(NULL) ;
}

