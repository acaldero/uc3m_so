
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

#define NUM_THREADS  5

/*
int             is_copied; // boolean to say "is copied"
pthread_mutex_t mutex_1;   // protect the is_copied global variable, shared by thread, modified but might be not atomically modified
pthread_cond_t  cond_cp;   // condition to wait if boolean said we need to wait
*/

void *th_function ( void *arg )
{
    int *p_thid ;

    p_thid = (int *)arg ;

    /*
    pthread_mutex_lock(&mutex_1) ;
    is_copied = 1 ;
    pthread_cond_signal(&cond_cp) ;
    pthread_mutex_unlock(&mutex_1) ;
    */

    printf("Hello world from thread #%d!\n", *p_thid) ;
    pthread_exit(NULL) ;
}

int main ( int argc, char *argv[] )
{
    int t, rc ;
    pthread_t threads[NUM_THREADS];

    /*
    // Initialize
    pthread_mutex_init(&mutex_1, NULL) ;
    pthread_cond_init(&cond_cp, NULL) ;
    */

    // Create threads...
    for (t=0; t<NUM_THREADS; t++)
    {
           /*
           is_copied = 0;
           */

           rc = pthread_create(&(threads[t]), NULL, th_function, (void *)&t) ;
           if (rc)
           {
	       printf("ERROR from pthread_create(): %d\n", rc) ;
	       exit(-1) ;
	   }
	   
	   /*
	   pthread_mutex_lock(&mutex_1) ;
           while (0 == is_copied) {
                  pthread_cond_wait(&cond_cp, &mutex_1) ;
           }
	   pthread_mutex_unlock(&mutex_1) ;
	   */
    }

    // Join threads...
    for (t=0; t<NUM_THREADS; t++)
    {
           rc = pthread_join(threads[t], NULL) ;
           if (rc)
           {
	       printf("ERROR from pthread_join(): %d\n", rc) ;
	       exit(-1) ;
	   }
    }

    /*
    // Destroy...
    pthread_mutex_destroy(&mutex_1) ;
    pthread_cond_destroy(&cond_cp) ;
    */

    pthread_exit(NULL) ;
}

