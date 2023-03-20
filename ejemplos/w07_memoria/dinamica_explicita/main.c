
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
#include <dlfcn.h>

void (*hola)(void);

int main()
{
   void * dbd ;

   dbd = dlopen("libhola.so", RTLD_LAZY);
   hola = dlsym(dbd, "hola");
   hola();
   dlclose(dbd);

   return 0;
}

