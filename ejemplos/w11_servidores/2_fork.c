
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


#include "peticion.h"
#include <sys/types.h>
#include <sys/wait.h>

const int MAX_PETICIONES = 5;

void  receptor ( void )
{
    peticion_t p;
    int pid, hijos=0;

    for (int i=0; i<MAX_PETICIONES; i++)
    {
       recibir_peticion(&p);

       pid = fork();
       if (pid<0)  { perror("Error en la creación del hij");}
       if (pid==0) { responder_peticion(&p); exit(0); }   /* HIJO */
       if (pid!=0) { hijos++; }                           /* PADRE */
    }

    fprintf(stderr, "Esperando fin de %d hijos\n", hijos);
    while (hijos > 0)
    {
         pid = waitpid(-1, NULL, WNOHANG);
         if (pid > 0) { hijos--;  }
    } ;
}

int main ( int argc, char *argv[] )
{
    struct timeval timenow;
    long t1, t2;

    // t1
    gettimeofday(&timenow, NULL) ;
    t1 = (long)timenow.tv_sec * 1000 + (long)timenow.tv_usec / 1000 ;

    // receptor...
    receptor() ;

    // t2
    gettimeofday(&timenow, NULL) ;
    t2 = (long)timenow.tv_sec * 1000 + (long)timenow.tv_usec / 1000 ;

    // imprimir t2-t1...
    printf("Tiempo: %lf\n", (t2-t1)/1000.0);

    return 0;
}

