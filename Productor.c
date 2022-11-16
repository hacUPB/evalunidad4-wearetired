#include <stdio.h> 
#include <string.h> 
#include <errno.h> 
#include <pthread.h> 
//#include <semaphore.h>

#define SUMSIZE 100 
#define BUFSIZE 8

int sum = 0; 
int cont= 0;
int conCedula = 123497824;
pthread_mutex_t mxShared;
/*sem_t items; 
sem_t slots;*/

typedef struct Gobierno
{
   double ingresoM;
   int cedula;
}Pers;

void put_item(Pers); 
void get_item(Pers *);



static void *producer(void *arg1)
{
   int i;

   for (i = 1; i <= SUMSIZE; i++)
   {
      pthread_mutex_lock(&mxShared);
      Pers persona;
      conCedula = conCedula+100;
      persona.cedula = conCedula;
      int ingresoM=rand()%10000;
      persona.ingresoM = ingresoM;
      put_item(persona);
      
      pthread_mutex_unlock(&mxShared);
   }
   return NULL;
}

static void *consumer(void *arg2)
{
   int i; 
   Pers myitem;

   for (i = 1; i <= SUMSIZE; i++)
   {
      get_item(&myitem);
      if (myitem.ingresoM > 2500)
      {
         printf("Usuario con cédula: %d\n",myitem.cedula);
         printf("Tiene un ingreso de: %d y pertenece al rango 2 \n",myitem.ingresoM);
      }
      else if (myitem.ingresoM < 2500)
      {
         printf("Usuario con cédula: %d\n",myitem.cedula);
         printf("Tiene un ingreso de: %d y pertenece al rango 1 y morirá \n",myitem.ingresoM);
      }
   }
   return NULL;
}

/*void main (void)
{
   pthread_t prodtid;
   pthread_t constid;
   int i, total;

   printf("Se segmenta el usuario: %f\n", cont);

   total = 0;
   for (i = 1; i <= SUMSIZE; i++)
   total += i*i;
   printf("The checksum is %f\n", total);

   //sem_init(&items, 0, 0);
   //sem_init(&slots, 0, BUFSIZE);

   pthread_create(&prodtid, NULL, producer, NULL);
   pthread_create(&constid, NULL, consumer, NULL);

   pthread_join(prodtid, NULL);
   pthread_join(constid, NULL);

   printf("The threads produced the sum %d\n", sum);

   pthread_mutex_destroy(&mxShared);
   return 0;
}*/
