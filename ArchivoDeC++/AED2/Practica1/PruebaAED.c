#include <stdlib.h> 
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#define _NUMEROCASOS 1
#define _NUMEROVALORES 1

int progreso = 0;
int n = _NUMEROCASOS;
int incremento = _NUMEROCASOS /_NUMEROVALORES;

//Función para la barra de progreso
void barraProgreso(int i){

   int aux = (((i/incremento)*100)/_NUMEROVALORES)+1;

   if(aux > progreso){
    fprintf(stderr,"%d%%\r",aux);
    progreso = aux;
   }
   else progreso = aux;
   if(progreso == 100) fprintf(stderr,"\n");
}

//Función para sacar el tiempo.
  long long mseconds(){
      struct timeval t;
      gettimeofday(&t,NULL);
      return t.tv_sec*100000+t.tv_usec;
   }


char* concat(char a[],char b[]){
   char palabra[2];
   palabra[0] = a[0];
   palabra[1] = b[0];
   return palabra;
}

char* combinar(char* a, char* b){

   fprintf(stderr, "EL COMBINAR: %s de: %s con: %s\n",strcat(a,b),a,b );
   return strcat(b,a);
}

void imprimir(char cadena[], int longit){
   for(int i = 0; i < longit; i++){
      fprintf(stderr, "%c",cadena[i] );
   }
}

void imprimirln(char cadena[], int longit){
   for(int i = 0; i < longit; i++){
      fprintf(stderr, "%c",cadena[i] );
   }
   fprintf(stderr, "\n" ); 
}

/////////////////////////////////////////////////////////////
////////////        FUNCION RECURSIVA        ////////////////
/////////////////////////////////////////////////////////////

char* maxConsVocal(char cadena[],int n){

   if(n == 1){
      return cadena;
   }

   char subcad1[(n/2)];
   fprintf(stderr, "El tamaño del subarray 1 es: %d\n", (n/2));
   memcpy(subcad1,&cadena[0],n/2);
   fprintf(stderr, "El subarray 1 es: ");
   imprimirln(subcad1,2);
   //subcad1[strlen(subcad1)] = '\0';

   char subcad2[n-(n/2)];
   fprintf(stderr, "El tamaño del subarray 2 es: %d\n", n-(n/2));
   memcpy(subcad2,&cadena[n/2],n-(n/2));
   fprintf(stderr, "El subarray 2 es: ");
   imprimirln(subcad2,n-(n/2));
   //subcad2[strlen(cadena)] = '\0';

   //imprimirln(subcad1,strlen(subcad1));
   //imprimirln(subcad2,strlen(subcad2));
  // imprimir(cadena,strlen(cadena));
  // fprintf(stderr, " %s %ld\n",cadena, strlen(cadena));
   return combinar(maxConsVocal(subcad2,(n-(n/2))),maxConsVocal(subcad1,(n/2)));
}




//////////////////////////////////////////////////////////////
////////////        PROGRAMA PRINCIPAL        ////////////////
//////////////////////////////////////////////////////////////


int main (void)
{
  //Variables.
  int m,base;
  base = 0;
  long long tiempoIni,tiempoFin;
  ////////////////////////

  //Se pintan los indices.
  printf("n\t");
  for(int i = 1;i <= n; i+=incremento) printf("%d\t",i);
    printf("\nTiempo\t");
  /////////////////////////
   fprintf(stderr,"Se van a genererar %d datos\n", _NUMEROCASOS);
  for(int i = 1; i <= n; i+=incremento){
          tiempoIni = mseconds();



          ///////////////////////////////////////////////////
          char cadena[] = "adcd";
          fprintf(stderr,"Cadena Inicial: %s\n",cadena);
          fprintf(stderr,"Cadena Final: \n");
          imprimir(maxConsVocal(cadena,strlen(cadena)),4);
          //maxConsVocal(cadena,strlen(cadena)),strlen(cadena);
          //scanf("%s",cadena);
          ///////////////////////////////////////////////////




          tiempoFin = mseconds();
          barraProgreso(i);
    printf("%lld\t",(tiempoFin-tiempoIni));
  }
}


