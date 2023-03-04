
/*
 *  Copyright 2020-2023 ARCOS.INF.UC3M.ES
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
#include <unistd.h>
#include <pthread.h>

long acc ;
//pthread_mutex_t mutex_1;

void *th_main_1 ( void *arg )
{
    register int a1 ;

    //pthread_mutex_lock(&mutex_1) ;
    for (int j=0; j<2; j++)
    {
         a1  = acc ;
             printf("main_1 sees acc=%d...\n", a1) ;
         a1  = a1 + 1 ;
         acc = a1 ;
             printf("main_1 updates acc=%d...\n", a1) ;
	 sleep(1) ;
    }
    //pthread_mutex_unlock(&mutex_1) ;

    pthread_exit(NULL) ;
}

void *th_main_2 ( void *arg )
{
    register int a2 ;

    //pthread_mutex_lock(&mutex_1) ;
    for (int j=0; j<2; j++)
    {
         a2  = acc ;
             printf("main_2 sees acc=%d...\n", a2) ;
         a2  = a2 - 1 ;
         acc = a2 ;
             printf("main_2 updates acc=%d...\n", a2) ;
	 sleep(1) ;
    }
    //pthread_mutex_unlock(&mutex_1) ;

    pthread_exit(NULL) ;
}

int main ( int argc, char *argv[] )
{
    int rc ;
    pthread_t threads[2];

    // Initialize...
    acc = 0 ;
    //pthread_mutex_init(&mutex_1, NULL) ;

    // Create threads...
    rc = pthread_create(&(threads[0]), NULL, th_main_1, NULL) ;
    if (rc) {
	printf("ERROR from pthread_create(): %d\n", rc) ;
	exit(-1) ;
    }
    rc = pthread_create(&(threads[1]), NULL, th_main_2, NULL) ;
    if (rc) {
	printf("ERROR from pthread_create(): %d\n", rc) ;
	exit(-1) ;
    }

    // Join threads...
    rc = pthread_join(threads[0], NULL) ;
    if (rc) {
	printf("ERROR from pthread_join(): %d\n", rc) ;
	exit(-1) ;
    }
    rc = pthread_join(threads[1], NULL) ;
    if (rc) {
	printf("ERROR from pthread_join(): %d\n", rc) ;
	exit(-1) ;
    }

    printf(" >>>>> acc = %ld\n", acc) ;

    // Destroy...
    //pthread_mutex_destroy(&mutex_1) ;

    pthread_exit(NULL) ;
}

