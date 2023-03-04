
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


#include "peticion.h"
#include <pthread.h>
#include <semaphore.h>

const int MAX_PETICIONES = 5;

pthread_mutex_t mutex;
pthread_cond_t  copied;
int             is_copied;

void * servicio ( void * p )
{
      peticion_t  pet;

      // copy parameters...
      memmove(&pet,(peticion_t*)p, sizeof(peticion_t));

      // signal data is copied
      pthread_mutex_lock(&mutex) ;
      is_copied = 1 ;
      pthread_cond_signal(&copied) ;
      pthread_mutex_unlock(&mutex) ;

      // process and response
      fprintf(stderr, "Iniciando servicio\n");
      responder_peticion(&pet);

      fprintf(stderr, "Terminando servicio\n");
      pthread_exit(0);
      return NULL;
}

void * receptor ( void * param )
{
     int i;
     peticion_t  p;
     pthread_t   th_hijo[MAX_PETICIONES];

     // for each request, a new thread...
     for (i=0; i<MAX_PETICIONES; i++)
     {
	  // receive request and new thread treat it
          recibir_peticion(&p);
          pthread_create(&(th_hijo[i]), NULL, servicio, &p);

          // wait data is copied
          pthread_mutex_lock(&mutex) ;
	  while (!is_copied) {
                 pthread_cond_wait(&copied, &mutex) ;
	  }
          is_copied = 0 ;
          pthread_mutex_unlock(&mutex) ;
     }

     // wait for each thread ends
     for (i=0; i<MAX_PETICIONES; i++) {
	  pthread_join(th_hijo[i], NULL) ;
     }

     pthread_exit(0);
     return NULL;
}

int main ( int argc, char *argv[] ) 
{
    struct timeval timenow;
    long t1, t2;
    pthread_t thr;

    // t1
    gettimeofday(&timenow, NULL) ;
    t1 = (long)timenow.tv_sec * 1000 + (long)timenow.tv_usec / 1000 ;

    // receptor()
    pthread_create(&thr, NULL, receptor, NULL);
    pthread_join(thr, NULL);

    // t2
    gettimeofday(&timenow, NULL) ;
    t2 = (long)timenow.tv_sec * 1000 + (long)timenow.tv_usec / 1000 ;

    // imprimir t2-t1...
    printf("Tiempo total: %lf\n", (t2-t1)/1000.0);
    return 0;
}

