
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


#define MAX_BUFFER        16     /* buffer size */
#define DATA_TO_PRODUCE   50     /* data to be produced */

pthread_mutex_t mutex;           /* shared buffer access mutex */
pthread_cond_t no_full;          /* controls the filling of the buffer */
pthread_cond_t no_empty;         /* controls the emptying of the buffer */
int n_elements;                  /* number of elements in the buffer */
int buffer[MAX_BUFFER];          /* common buffer */

void *Producer ( void *arg )
{
  int dato, i ,pos = 0;
  for(i=0; i<DATA_TO_PRODUCE; i++)
  {
    dato = i;
    printf("Produce data=%d\n", dato);
    pthread_mutex_lock(&mutex);
    while (n_elements == MAX_BUFFER) {
           pthread_cond_wait(&no_full, &mutex);
    }

    buffer[pos] = i;
    pos = (pos + 1) % MAX_BUFFER;
    n_elements ++;

    pthread_cond_signal(&no_empty);
    pthread_mutex_unlock(&mutex);
  }

  pthread_exit(0);
  return NULL ;
}


void *Consumer ( void *arg )
{
  int dato, i ,pos = 0;

  for(i=0; i<DATA_TO_PRODUCE; i++)
  {
    pthread_mutex_lock(&mutex);
    while (n_elements == 0) {
           pthread_cond_wait(&no_empty, &mutex);
    }

    dato = buffer[pos];
    pos = (pos + 1) % MAX_BUFFER;
    n_elements --;

    pthread_cond_signal(&no_full);
    pthread_mutex_unlock(&mutex);
    printf("Consume data=%d\n", dato);
  }

  pthread_exit(0);
  return NULL ;
}

int main ( int argc, char *argv[] )
{
    pthread_t th1, th2;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&no_full, NULL);
    pthread_cond_init(&no_empty, NULL);

    pthread_create(&th1, NULL, Producer, NULL);
    pthread_create(&th2, NULL, Consumer, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&no_full);
    pthread_cond_destroy(&no_empty);

    return 0;
}

