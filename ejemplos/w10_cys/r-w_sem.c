
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
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h> 

int dato = 5;       /* resource */
int n_readers = 0;  /* num. of readers */
sem_t sem_reader;   /* control access to n_readers */
sem_t mutex;        /* control access to dato */

void *Writer ( void *arg ) ;
void *Reader ( void *arg ) ;

int main ( int argc, char *argv[] )
{
   pthread_t th1, th2, th3, th4;

   sem_init(&mutex, 0, 1);
   sem_init(&sem_reader, 0, 1);

   pthread_create(&th1, NULL, Reader, NULL);
   pthread_create(&th2, NULL, Writer, NULL);
   pthread_create(&th3, NULL, Reader, NULL);
   pthread_create(&th4, NULL, Writer, NULL);
   pthread_join(th1, NULL);
   pthread_join(th2, NULL);
   pthread_join(th3, NULL);
   pthread_join(th4, NULL);

   sem_destroy(&mutex);
   sem_destroy(&sem_reader);

   return 0;
}

void *Reader ( void *arg )
{
  sem_wait(&sem_reader);
  n_readers = n_readers + 1;
  if (n_readers == 1)
      sem_wait(&mutex);
  sem_post(&sem_reader);

  printf("Reader: data=%d\n", dato);
  sleep(1) ;

  sem_wait(&sem_reader);
  n_readers = n_readers - 1;
  if (n_readers == 0)
      sem_post(&mutex);
  sem_post(&sem_reader);

  pthread_exit(0);
}

void *Writer ( void *arg )
{
   sem_wait(&mutex);
   dato = dato + 2;
   sem_post(&mutex);

   pthread_exit(0);
}

