
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


#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include "peticion.h"


#define MAX_BUFFER 128
peticion_t  buffer[MAX_BUFFER];


int  n_elementos  = 0;
int  ha_arrancado = 0;
int  fin = 0;

pthread_mutex_t  mutex;
pthread_cond_t   no_lleno;
pthread_cond_t   no_vacio;
pthread_cond_t   arrancado;
pthread_cond_t   parado;

const int MAX_PETICIONES = 5;
const int MAX_SERVICIO   = 5;

void * receptor ( void * param )
{
       peticion_t p;
       int i, pos_receptor = 0;

       for (i=0; i<MAX_PETICIONES; i++)
       {
            recibir_peticion(&p);
            fprintf(stderr,"receptor: recepción de petición\n");

	    // lock when not full...
            pthread_mutex_lock(&mutex);
            while (n_elementos == MAX_BUFFER) {
                   pthread_cond_wait(&no_lleno, &mutex);
	    }

	    // inserting element into the buffer
            buffer[pos_receptor ] = p;
            pos_receptor = (pos_receptor +1) % MAX_BUFFER;
            n_elementos++;

	    // signal not empty...
            pthread_cond_signal(&no_vacio);
            pthread_mutex_unlock(&mutex);
       }

       fprintf(stderr,"receptor: finalizando\n");

       // signal end
       pthread_mutex_lock(&mutex);
       fin=1;
       pthread_cond_signal(&no_vacio);
       pthread_mutex_unlock(&mutex);

       fprintf(stderr, "receptor: Finalizado\n");
       pthread_exit(0);
       return NULL;

}

void * servicio ( void * param )
{
      peticion_t p;
      int pos_servicio = 0;

      // signal initializate...
      pthread_mutex_lock(&mutex);
      ha_arrancado = 1;
      pthread_cond_signal(&arrancado);
      pthread_mutex_unlock(&mutex);

      for (;;)
      {
	   // lock when not empty and not ended...
           pthread_mutex_lock(&mutex);
           while (n_elementos == 0)
	   {
                if (fin==1) {
                     fprintf(stderr,"servicio: finalizando\n");
                     pthread_cond_signal(&parado);
                     pthread_mutex_unlock(&mutex);
                     pthread_exit(0);
                }

                pthread_cond_wait(&no_vacio, &mutex);
           } // while

	   // removing element from buffer...
           p = buffer[pos_servicio];
           pos_servicio = (pos_servicio + 1) % MAX_BUFFER;
           n_elementos--;

	   // signal not full...
           pthread_cond_signal(&no_lleno);
           pthread_mutex_unlock(&mutex);

	   // process and response...
           fprintf(stderr, "servicio: sirviendo posicion %d\n", pos_servicio);
           responder_peticion(&p);
    }

    pthread_exit(0);
    return NULL;
}

int main ( int argc, char *argv[] )
{
    struct timeval timenow;
    long t1, t2;
    pthread_t thr;
    pthread_t ths[MAX_SERVICIO];

    // initialize
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&no_lleno, NULL);
    pthread_cond_init(&no_vacio, NULL);
    pthread_cond_init(&arrancado, NULL);
    pthread_cond_init(&parado, NULL);

    // create threads
    for (int i=0;i<MAX_SERVICIO;i++)
    {
          pthread_create(&ths[i], NULL, servicio, NULL);

          // wait thread is started
          pthread_mutex_lock(&mutex) ;
	  while (!ha_arrancado) {
                 pthread_cond_wait(&arrancado, &mutex) ;
	  }
          ha_arrancado = 0 ;
          pthread_mutex_unlock(&mutex) ;
    }

    // t1
    gettimeofday(&timenow, NULL) ;
    t1 = (long)timenow.tv_sec * 1000 + (long)timenow.tv_usec / 1000 ;

          // receptor...
          pthread_create(&thr, NULL,receptor, NULL);

          // wait thread is started
          pthread_mutex_lock(&mutex) ;
	  while ( (!fin) || (n_elementos > 0) ) {
                 pthread_cond_wait(&parado, &mutex) ;
	  }
          pthread_mutex_unlock(&mutex) ;

    // t2
    gettimeofday(&timenow, NULL) ;
    t2 = (long)timenow.tv_sec * 1000 + (long)timenow.tv_usec / 1000 ;

    // finalizar
    pthread_join(thr, NULL);
    for (int i=0; i<MAX_SERVICIO; i++) {
         pthread_join(ths[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&no_lleno);
    pthread_cond_destroy(&no_vacio);
    pthread_cond_destroy(&arrancado);
    pthread_cond_destroy(&parado);

    // imprimir t2-t1...
    printf("Tiempo total: %lf\n", (t2-t1)/1000.0);
    return 0;
}

