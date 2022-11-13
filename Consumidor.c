/* PROCESO CONSUMIDOR */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>

#define KEY 100
#define MB 0      // ID del semáforo Manipulación del Buffer
#define EL 1       // ID del semáforo Espacio Libre
#define ED 2      // ID del semáforo Elemento Disponible
#define TAMBUFFER 5      // TAMaño del BUFFER

 
int main () {
   /* Declaración de variables */
   int i;
   int numEstrato;   /* número de contactos a visualizar */
   int semid;  /* ID al conjunto de semáforos */
   int shmid;  /* ID a la memoria compartida para almacenar el buffer */
 
   struct DatosPersona {
    char nombre;
    char apellidos;
    char numIdentificacion[10];
      //Aquí vienen declarados todos los datos de un contacto
   } contacto, *addr;   /* contacto se utiliza para almacenar los datos de un contacto */
                                   /* *addr es un puntero a la memoria compartida */

 
  struct sembuf sem_oper;  /* Para las operaciones wait y signal con semáforos */
  union semun {
int val;
struct semid_ds *semstat;
unsigned short *array;
  } arg;
  
 
  /* Creamos un conjunto de 3 semáforos */
  semid=semget(KEY, 3, 0770 | IPC_CREAT);
  if (semid == -1) {
     printf(“\nError en la creación de los semáforos”);
     exit(1);  /* Error 1: error en la creación de semáforos */
  }
 
  /* Inicializamos los semáforos */
  arg.array = (unsigned short *) malloc (sizeof (short)*3);
  arg.array[MB] = 1;
  arg.array[EL] = TAMBUFFER;
  arg.array[ED] = 0;
  semctl (semid, 3, SETALL, arg);
 
   /* Crear la memoria compartida */
  shmid = shmget(KEY, calcular el tamaño, 0770 | IPC_CREAT);
  if (shmid == -1) {
    printf(“\nError en la creación de la Memoria compartida”);
    exit(2);  /* Error 2: error al crear la Memoria compartida */
  }
 
  /* Enlazar la memoria compartida al proceso */
  addr = shmat(shmid, 0, 0);
 
   /* Determinar el número de contactos a obtener */
   Aquí viene el código que determina el número de contactos
 
   /* Repetir para cada contacto obtenido del productor */
   for (i=0; i<numContactos; i++) {
      /* Wait (Elemento disponible) */
      sem_oper.sem_num = ED; /* Seleccionamos semáforo Elemento Disponible */
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
      Aqui viene el código de la sección crítica del consumidor
 
 
      /* Signal (Manipulación del buffer) */
      sem_oper.sem_num = MB;
      sem_oper.sem_op = 1;
      semop (semid, &sem_oper, 1);
 
      /* Signal (Espacio libre) */
      sem_oper.sem_num = EL;
      sem_oper.sem_op = 1;
      semop (semid, &sem_oper, 1);
 
      /* Consumir el elemento */
      Aquí viene el código de Consumir el elemento
 
   }  /* fin de for */
 
   /* Eliminamos el conjunto de semáforos */
   semctl (semid, 3, IPC_RMID, 0);
 
   /* Separamos la memoria compartida del proceso */
   shmdt(addr);
 
   /* Eliminamos la memoria compartida */
   /* Esta operación lo realiza uno de los procesos */
   shmctl(shmid, IPC_RMID, 0);
 
   /* liberamos la memoria dinámica */
   free (arg.array);
 
   return 0;
}  /* fin de main */