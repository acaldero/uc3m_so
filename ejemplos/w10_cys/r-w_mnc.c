
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


int dato = 5;                   /* resource */
int n_readers = 0;              /* number of readers*/
pthread_mutex_t mutex;          /* control access to dato */
pthread_mutex_t mutex_readers;  /* control access to n_readers */

void *Reader ( void *arg )
{
  pthread_mutex_lock(&mutex_readers);
  n_readers++;
  if (n_readers == 1) {
      pthread_mutex_lock(&mutex);
  }
  pthread_mutex_unlock(&mutex_readers);

  /* read dato */
  printf("Reader: data=%d\n", dato);
  sleep(1) ;

  pthread_mutex_lock(&mutex_readers);
  n_readers--;
  if (n_readers == 0) {
      pthread_mutex_unlock(&mutex);
  }
  pthread_mutex_unlock(&mutex_readers);

  pthread_exit(0);
  return NULL;
}

void *Writer ( void *arg )
{
   pthread_mutex_lock(&mutex);

   /* modify the resource */
   dato = dato + 2;
 
   pthread_mutex_unlock(&mutex);

   pthread_exit(0);
   return NULL;
}

int main ( int argc, char *argv[] )
{
    pthread_t th1, th2, th3, th4;

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&mutex_readers, NULL);

    pthread_create(&th1, NULL, Reader, NULL);
    pthread_create(&th2, NULL, Writer, NULL);
    pthread_create(&th3, NULL, Reader, NULL);
    pthread_create(&th4, NULL, Writer, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    pthread_join(th4, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&mutex_readers);
    return 0;
}

