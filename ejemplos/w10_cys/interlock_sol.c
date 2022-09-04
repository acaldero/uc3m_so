
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
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex_1;
pthread_mutex_t mutex_2;

void *th_main_1 ( void *arg )
{
    pthread_mutex_lock(&mutex_1) ;
    sleep(1) ;
    pthread_mutex_lock(&mutex_2) ;

    printf("Hello from main_1...\n") ;

    pthread_mutex_unlock(&mutex_2) ;
    pthread_mutex_unlock(&mutex_1) ;

    pthread_exit(NULL) ;
}

void *th_main_2 ( void *arg )
{
    pthread_mutex_lock(&mutex_1) ; // OK
    sleep(1) ;
    pthread_mutex_lock(&mutex_2) ; // OK

    printf("Hello from main_2...\n") ;
    sleep(1) ;

    pthread_mutex_unlock(&mutex_2) ;
    pthread_mutex_unlock(&mutex_1) ;

    pthread_exit(NULL) ;
}

int main ( int argc, char *argv[] )
{
    int rc ;
    pthread_t threads[2];

    // Initialize mutexes...
    pthread_mutex_init(&mutex_1, NULL) ;
    pthread_mutex_init(&mutex_2, NULL) ;

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
    for (int t=0; t<2; t++)
    {
         rc = pthread_join(threads[t], NULL) ;
         if (rc) {
	     printf("ERROR from pthread_join(): %d\n", rc) ;
	     exit(-1) ;
	 }
    }

    // Destroy mutexes...
    pthread_mutex_destroy(&mutex_1) ;
    pthread_mutex_destroy(&mutex_2) ;

    pthread_exit(NULL) ;
}

