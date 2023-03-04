
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

static long petid = 0;

void recibir_peticion (peticion_t * p) 
{
   int delay;
   fprintf(stderr, "Recibiendo petición\n");
   p->id = petid++;
  
   /* Simulación de tiempo de E/S */
   delay = rand() % 5;
   sleep(delay);

   fprintf(stderr,"Petición %ld recibida después de %d segundos\n", p->id, delay);
}

void responder_peticion (peticion_t * p) 
{
  int delay;
  char *mz;

  fprintf(stderr, "Enviando petición %ld\n", p->id);

  /* Simulación de tiempo de procesamiento */
  mz = malloc(1000000) ;
  for (int i=0; i<1000000; i++) { mz[i] = 0; }
  free(mz) ;

  /* Simulación de tiempo de E/S */
  delay = rand() % 20;
  sleep(delay);

  fprintf(stderr, "Petición %ld enviada después de %d segundos\n",  p->id, delay);
}

