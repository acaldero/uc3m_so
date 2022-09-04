
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


#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h> 


/* buffer size*/ 
#define MAX_BUFFER        16
/* data to produce */
#define DATA_TO_PRODUCE   50

sem_t mutex;            /* critical section */ 
sem_t elements;         /* eltos in the buffer */
sem_t huecos;           /* spaces in the buffer */
int buffer[MAX_BUFFER]; /* shared buffer */

void *Producer ( void *arg ) ;
void *Consumer ( void *arg ) ;

int main ( int argc, char *argv[])
{
   pthread_t th1, th2; 

   /* initialize the semaphores */
   sem_init(&mutex,     0, 1);
   sem_init(&elements, 0, 0);
   sem_init(&huecos,    0, MAX_BUFFER);
      /* create threads */
   pthread_create(&th1, NULL, Producer, NULL);
   pthread_create(&th2, NULL, Consumer, NULL);

   /* wait for its completion */
   pthread_join(th1, NULL);
   pthread_join(th2, NULL);

   sem_destroy(&mutex);
   sem_destroy(&huecos);
   sem_destroy(&elements);
   return (0);
}

void *Producer ( void *arg )
{
   int pos = 0;
   int dato;
   int i;

   for (i=0; i<DATA_TO_PRODUCE; i++)
   {
      dato = i; /* produce... */
      printf("produce data=%d\n", dato) ;

      sem_wait(&huecos);
      sem_wait(&mutex);
      buffer[pos] = i;
      pos = (pos + 1) % MAX_BUFFER;
      sem_post(&mutex);
      sem_post(&elements);

   }

   pthread_exit(0);
   return NULL ;
}

void *Consumer ( void *arg )
{
   int pos = 0;
   int dato;
   int i;

   for (i=0; i<DATA_TO_PRODUCE; i++)
   {

      sem_wait(&elements);
      sem_wait(&mutex);
      dato = buffer[pos];
      pos = (pos + 1) % MAX_BUFFER;
      sem_post(&mutex);
      sem_post(&huecos);

      /* consume data */
      printf("consume data=%d\n", dato) ;
   }

   pthread_exit(0);
   return NULL ;
}

