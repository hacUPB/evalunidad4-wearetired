/* PROCESO PRODUCTOR */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>


#define KEY 100
#define MB 0      // ID del semáforo Manipulación del Buffer
#define EL 1       // ID del semáforo Espacio Libre
#define ED 2      // ID del semáforo Elemento Disponible
#define TAMBUFFER 5      // TAMaño del BUFFER


 
int main (argc, argv)
   int argc;
   char **argv; {
 

   /* Declaración de variables */
   int i;
   int numEstrato;   /* número de contactos a visualizar */
   int semid;                /* ID al conjunto de semáforos */
   int shmid;                /* ID a la memoria compartida para almacenar el buffer */
 

   struct DatosPersona {
    char nombre;
    char apellidos;
    char numIdentificacion[10];
     // Aquí vienen declarados todos los datos de un contacto
   } contacto, *addr;   /* contacto se utiliza para almacenar los datos de un contacto */
                                 /* *addr es un puntero a la memoria compartida */
 
   struct sembuf sem_oper;  /* Para las operaciones wait y signal con semáforos */
 
   /* Determinar el número de contactos a producir */
   //Aquí viene el código que determina el número de contactos
    
 

   /* Acceder a un conjunto de 3 semáforos ya existente */
   semid=semget(KEY, 3, 0770);
   if (semid == -1) {
      printf(“\nError en el acceso al conjunto de semáforos”);
      exit(1);  /* Error 1: error en el acceso al conjunto de semáforos */
   }
 
   /* OJO: No hay que inicializar los semáforos. Lo ha hecho el proceso Consumidor */
 
   /* Acceder a la memoria compartida */
  shmid = shmget(KEY, calcular el tamaño, 0770);
  if (shmid == -1) {
    printf(“\nError en la creación de la Memoria compartida”);
    exit(2);  /* Error 2: error al crear la Memoria compartida */
  }
 
  /* Enlazar la memoria compartida al proceso */
  addr = shmat(shmid, 0, 0);

   /* Pasarle al Consumidor el número de contactos que se va a producer */
    Aquí viene el código para indicarle al consumidor cuantos contactos tiene que consumir
 
   /* Repetir para cada contacto /*/
   for (i=0; i<numContactos; i++) {
       /* Producir elemento */
       Aquí viene el código de producir un elemento
 
      /* Wait (Espacio libre) */
      sem_oper.sem_num = EL; /* Seleccionamos semáforo Espacio Libre */
      sem_oper.sem_op = -1; /* Decrementar 1 (hace un wait) */
      sem_oper.sem_flg = SEM_UNDO;  /* Para evitar interbloqueos si
                                                                un proceso acaba inesperadamente */
      semop (semid, &sem_oper, 1);
 
      /* Wait (Manipulación del buffer) */
      sem_oper.sem_num = MB;
      sem_oper.sem_op = -1;
      sem_oper.sem_flg = SEM_UNDO;  /* No es necesario porque ya
                                                                 se ha hecho anteriormente */
      semop (semid, &sem_oper, 1);
 
      /* Sección crítica: Para acceder al buffer que será el recurso no compartible */
      Aqui viene el código de la sección crítica del productor
 
 
       /* Signal (Manipulación del buffer) */
       sem_oper.sem_num = MB;
       sem_oper.sem_op = 1;
       semop (semid, &sem_oper, 1);
 
       /* Signal (Elemento Disponible) */
       sem_oper.sem_num = ED;
       sem_oper.sem_op = 1;
       semop (semid, &sem_oper, 1);
 
   }  /* fin de for */
 
   /* Separamos la memoria compartida del proceso */
   shmdt(addr);
 
   return 0;
}  /* fin de main */