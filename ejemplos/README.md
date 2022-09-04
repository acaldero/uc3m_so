## Materiales usados en ARCOS.INF.UC3M.ES bajo licencia [CC BY-NC 4.0](http://creativecommons.org/licenses/by-nc/4.0/) 

## Sistemas Operativos (2021-2022)

1. ### <ins>POSIX threads</ins>

   1.1. <ins>¿Qué son y cómo se crean los hilos o threads?</ins>

      **Ejemplo**: Programar una función main que crea 5 hilos y espera a que todos los hilos terminen. Cada hilo imprime "Hello world from thread &lt;id. del hilo&gt;!\n".
 
      **Código**:
      * <a href="https://github.com/acaldero/labs/blob/main/GII_Sistemas_Operativos/w06_hilos/ths_creatjoin.c">ths_creatjoin.c</a>

      **Compilar y ejecutar**:
      ```
      gcc -Wall -g -o ths_creatjoin ths_creatjoin.c -lpthread
      ./ths_creatjoin
      ```

      **Videos suplementarios**:
      * <a href="https://www.youtube.com/watch?v=n5qrEotEWfI">Repaso a los conceptos en hilos</a>
      * <a href="https://www.youtube.com/watch?v=akf9UG7Z5Go">Principales llamadas POSIX de hilos con ejemplos</a>
   
2. ### <ins>Comunicación y sincronización entre hilos</ins>

   2.1. <ins>¿Qué pasa si (1) dos o más hilos (2) comparten una variable (3) al menos uno modifica la variable (4) y se hace de forma no atómica?</ins>

      **Ejemplo**: Programar un ejemplo de condición de carrera entre dos hilos.
 
      **Código**:
      * <a href="https://github.com/acaldero/labs/blob/main/GII_Sistemas_Operativos/w10_cys/race.c">race.c</a>
      * <a href="https://github.com/acaldero/labs/blob/main/GII_Sistemas_Operativos/w10_cys/race_sol.c">race_sol.c</a>

      **Compilar y ejecutar**:
      ```
      : código con problema: tres ejecuciones con posibles diferentes resultados
        gcc -Wall -g -o race     race.c     -lpthread
        ./race; ./race; ./race
      : código con solución:
        gcc -Wall -g -o race_sol race_sol.c -lpthread
        ./race_sol
      ```

      **Video suplementario**:
      * <a href="https://www.youtube.com/watch?v=PxjgVYgpGkk&t=471s">Condiciones de carrera</a>  
   
   2.2. <ins>¿Qué pasa si se solapa el uso de dos o más mutex y no se sigue el mismo orden de petición de bloqueo de los mutex usados?</ins>

      **Ejemplo**: Programar un ejemplo de interbloqueo entre dos hilos.
 
      **Código**:
      * <a href="https://github.com/acaldero/labs/blob/main/GII_Sistemas_Operativos/w10_cys/interlock.c">interlock.c</a>
      * <a href="https://github.com/acaldero/labs/blob/main/GII_Sistemas_Operativos/w10_cys/interlock_sol.c">interlock_sol.c</a>

      **Compilar y ejecutar**:
      ```
      : código con problema (hay que terminar con control-c la ejecución):
        gcc -Wall -g -o interlock     interlock.c     -lpthread
        ./interlock
      : código con solución:
        gcc -Wall -g -o interlock_sol interlock_sol.c -lpthread
        ./interlock_sol
      ```

      **Video suplementario**:
      * <a href="https://www.youtube.com/watch?v=PxjgVYgpGkk&t=924s">Condiciones de interbloqueo</a>   
   
   2.3. <ins>¿Cómo podemos hacer que la ejecución de un hilo se espere hasta que se ejecute un código de otro hilo?</ins>

      **Ejemplo**: Programar un ejemplo de sincronización entre un hilo main y los hilos creados con pthread_create.
 
      **Códigos**:
      * <a href="https://github.com/acaldero/labs/blob/main/GII_Sistemas_Operativos/w10_cys/sync_child_mnc.c">sync_child_mnc.c</a>
      * <a href="https://github.com/acaldero/labs/blob/main/GII_Sistemas_Operativos/w10_cys/sync_child_mnc_sol.c">sync_child_mnc_sol.c</a>

      **Compilar y ejecutar**:
      ```
      : código con problema de no imprimir los identificadores de los hilos bien:
        gcc -Wall -g -o sync_child_mnc     sync_child_mnc.c     -lpthread
        ./sync_child_mnc ; ./sync_child_mnc
      : código con solución:
        gcc -Wall -g -o sync_child_mnc_sol sync_child_mnc_sol.c -lpthread
        ./sync_child_mnc_sol
      ```
   
      **Videos suplementarios**:
      * <a href="https://www.youtube.com/watch?v=EupaagvNpR0&t=807s">Funcionamiento de los mutex y conditions</a>   
   
   2.4. <ins>¿Cómo resolver el problema de productor-consumidor usando semáforos?</ins>

      **Ejemplo**: Programar un ejemplo de productor-consumidor (buffer acotado) entre dos hilos usando semáforos.
 
      **Código**:
      * <a href="https://github.com/acaldero/labs/blob/main/GII_Sistemas_Operativos/w10_cys/p-c_sem.c">p-c_sem.c</a>

      **Compilar y ejecutar**:
      ```
      gcc -Wall -g -o p-c_sem p-c_sem.c -lpthread
      ./p-c_sem
      ```

      **Videos suplementarios**:
      * <a href="https://www.youtube.com/watch?v=EupaagvNpR0&t=235s">Productor-consumidor con semáforos</a>   
      * <a href="https://www.youtube.com/watch?v=EupaagvNpR0&t=24s">Repaso a cómo funcionan los semáforos</a>      

   2.5. <ins>¿Cómo resolver el problema de lectores-escritores usando semáforos?</ins>

      **Ejemplo**: Programar un ejemplo de lectores-escritores entre dos hilos usando semáforos.
 
      **Código**:
      * <a href="https://github.com/acaldero/labs/blob/main/GII_Sistemas_Operativos/w10_cys/r-w_sem.c">r-w_sem.c</a>

      **Compilar y ejecutar**:
      ```
      gcc -Wall -g -o r-w_sem r-w_sem.c -lpthread
      ./r-w_sem
      ```
  
   2.6. <ins>¿Cómo resolver el problema de productores-consumidores usando mutex y conditions de POSIX?</ins>

      **Ejemplo**: Programar un ejemplo de productores-consumidores (bounded buffer) entre dos hilos usando mutex + conditions.
 
      **Código**:
      * <a href="https://github.com/acaldero/labs/blob/main/GII_Sistemas_Operativos/w10_cys/p-c_mnc.c">p-c_mnc.c</a>

      **Compilar y ejecutar**:
      ```
      gcc -Wall -g -o p-c_mnc p-c_mnc.c -lpthread
      ./p-c_mnc
      ```

      **Videos suplementarios**:
      * <a href="https://www.youtube.com/watch?v=8fdum4cvlvI">Ejemplo simple de productor-consumidor con mutex y conditions de POSIX</a>
      * <a href="https://www.youtube.com/watch?v=EupaagvNpR0&t=813s">Repaso a cómo funcionan los mutex y conditions de POSIX</a>
   
   2.7. <ins>¿Cómo resolver el problema de lectores-escritores usando mutex y conditions de POSIX?</ins>
   
      **Ejemplo**: Programar un ejemplo de lectores-escritores entre dos hilos usando mutex + conditions.
 
      **Código**:
      * <a href="https://github.com/acaldero/labs/blob/main/GII_Sistemas_Operativos/w10_cys/r-w_mnc.c">r-w_mnc.c</a>

      **Compilar y ejecutar**:
      ```
      gcc -Wall -g -o r-w_mnc r-w_mnc.c -lpthread
      ./r-w_mnc
      ```


3. ### <ins>Servidores concurrentes</ins>

   3.1. <ins>¿Cómo sería un servidor de peticiones totalmente secuencial?</ins>

      **Ejemplo**: Programar una función main que simule un servidor que secuencialmente le llegan peticiones y las trata una a una.

      **Código**:
      * <a href="https://github.com/acaldero/labs/blob/main/GII_Sistemas_Operativos/w11_servidores/peticion.h">peticion.h</a>
      * <a href="https://github.com/acaldero/labs/blob/main/GII_Sistemas_Operativos/w11_servidores/peticion.c">peticion.c</a>
      * <a href="https://github.com/acaldero/labs/blob/main/GII_Sistemas_Operativos/w11_servidores/1_sequential.c">1_sequential.c</a>

      **Compilar y ejecutar**:
      ```
      gcc -Wall -g -o peticion.o -c peticion.c
      gcc -Wall -g -o 1 1_sequential.c -lpthread peticion.o
      ./1
      ```

      **Video suplementario**:
      * <a href="https://www.youtube.com/watch?v=nDyYrpFYG-4&t=0s">Qué es un servidor de peticiones</a>
   
   3.2. <ins>¿Cómo sería un servidor de peticiones totalmente paralelo con procesos pesados?</ins>

      **Ejemplo**: Programar una función main que simula un servidor que le llegan peticiones, crea un proceso (fork) y el proceso hijo trata la petición asociada.

      **Código**:
      * <a href="https://github.com/acaldero/labs/blob/main/GII_Sistemas_Operativos/w11_servidores/peticion.h">peticion.h</a>
      * <a href="https://github.com/acaldero/labs/blob/main/GII_Sistemas_Operativos/w11_servidores/peticion.c">peticion.c</a>
      * <a href="https://github.com/acaldero/labs/blob/main/GII_Sistemas_Operativos/w11_servidores/1_sequential.c">2_fork.c</a>

      **Compilar y ejecutar**:
      ```
      gcc -Wall -g -o peticion.o -c peticion.c
      gcc -Wall -g -o 2 2_fork.c -lpthread peticion.o
      ./2
      ```
   
      **Video suplementario**:
      * <a href="https://www.youtube.com/watch?v=nDyYrpFYG-4&t=394s">Ejemplo de servidor de peticiones basado en procesos (fork)</a>

   3.3. <ins>¿Cómo sería un servidor de peticiones totalmente paralelo con procesos ligeros o hilos?</ins>

      **Ejemplo**: Programar una función main que simula un servidor que le llegan peticiones, crea un hilo y el hilo creado trata la petición asociada.

      **Código**:
      * <a href="https://github.com/acaldero/labs/blob/main/GII_Sistemas_Operativos/w11_servidores/peticion.h">peticion.h</a>
      * <a href="https://github.com/acaldero/labs/blob/main/GII_Sistemas_Operativos/w11_servidores/peticion.c">peticion.c</a>
      * <a href="https://github.com/acaldero/labs/blob/main/GII_Sistemas_Operativos/w11_servidores/1_sequential.c">3_threads_ondemand.c</a>

      **Compilar y ejecutar**:
      ```
      gcc -Wall -g -o peticion.o -c peticion.c
      gcc -Wall -g -o 3 3_threads_ondemand.c -lpthread peticion.o
      ./3
      ```

      **Video suplementario**:
      * <a href="https://www.youtube.com/watch?v=nDyYrpFYG-4&t=551s">Ejemplo de servidor de peticiones basado en hilos</a>

   3.4. <ins>¿Cómo sería un servidor de peticiones totalmente paralelo con procesos ligeros o hilos pre-creados?</ins>

      **Ejemplo**: Programar una función main que simula un servidor que crea varios hilos que esperan en sus conditions asociadas, le llegan peticiones y para cada una manda una señal a un hilo pre-creado que se encarga de atender a dicha petición y volver a esperar en la condition al terminar.

      **Código**:
      * <a href="https://github.com/acaldero/labs/blob/main/GII_Sistemas_Operativos/w11_servidores/peticion.h">peticion.h</a>
      * <a href="https://github.com/acaldero/labs/blob/main/GII_Sistemas_Operativos/w11_servidores/peticion.c">peticion.c</a>
      * <a href="https://github.com/acaldero/labs/blob/main/GII_Sistemas_Operativos/w11_servidores/1_sequential.c">4_threads_pool.c</a>

      **Compilar y ejecutar**:
      ```
      gcc -Wall -g -o peticion.o -c peticion.c
      gcc -Wall -g -o 4 4_threads_pool.c -lpthread peticion.o
      ./4
      ```

      **Video suplementario**:
      * <a href="https://www.youtube.com/watch?v=nDyYrpFYG-4&t=940s">Ejemplo de servidor de peticiones basado en hilos pre-creados</a>
   
