#include <stdlib.h>  // Funcion exit
#include <string.h>  // Funcion memset
#include <iostream>  // Variables cin y cout
#include <list>
using namespace std;

#define MAX_N 300

//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int difPeso;                  	// Diferencia de peso
int* valores;                 	// Vector de los valores de monedas
int* pesos;			// Vector de pesoss de cada tipo de moneda
int* solucionesDar;		// Vector solucion 1
int* solucionesRecibir;	// Vector solucion 2
int* solucionFinalDar;
int* solucionFinalRecibir;
int N;				// Numero de tipos
int V;				// Valor a Recibir
int minValDar;  //EL minimo valor de monedas.
int tam;
int pDar = 0,pRecibir = 0;



/*
* Esta funcion se encarga de leer los datos por pantalla y crear las vectores pertinentes
* para la resolucion del problema.
*/
void leerEntrada(void){
	//SE LEEN LOS DOS VALORES DE ENTRADA (CANTIDAD,TIPOS)
	cin >> N >> V;
	if ((N>MAX_N)||(N<0)||(V<0)) {
   		cerr << "Los valores de entrada son incorrectos\n";
      exit(0);
  	}	//SE CREAN TODOS LOS VECTORES DINAMICOS DEL TAMAÑO DEL NUMERO DE TIPOS DE FORMA QUE OCUPEN SOLO EL ESPACIO EN MEMORIA NECESARIO
	valores = new int[N];
	pesos = new int[N];
	solucionesRecibir = new int[N];
  solucionFinalDar = new int[N];
  solucionFinalRecibir = new int[N];

	//SE LEEN LOS VALORES DE LAS MONEDAS
  int min;
  cin >> valores[0];
  min = valores[0];
	for(int i = 1; i < N; i++){
	cin >> valores[i];
  if(valores[i] < min) min = valores[i];
}
  tam = V/min;

  solucionesDar = new int[tam];
  solucionesRecibir = new int[tam];
	//SE LEEN LOS PESOS DE LAS MONEDAS
	for(int j = 0; j < N; j++){
	cin >> pesos[j];
	}
}

/*
* Libera los vectores que se han declarado dinamicamente.
*/
void liberarVariables(){
	/*
	delete[] valores;
  //cout << "SE LIBERA valores" << endl;
	delete[] pesos;
  //cout << "SE LIBERA pesos" << endl;
	delete[] solucionesRecibir;
  //cout << "SE LIBERA solucionesRecibir" << endl;
  	delete[] solucionFinalDar; //DA PROBLEMAS
  //cout << "SE LIBERA solucionFinalDar" << endl;
  	delete[] solucionesDar; // DA PROBLEMAS
  //cout << "SE LIBERA solucionesDar" << endl;
*/
}


/*
* GenerarDar se encarga de ganerar un hermano a partir de un nivel y una solucion
* para eso comprueba si es el primer nodo de ese nivel para esa solucion y si no lo es
* suma uno, si lo es lo inicializa al valor del padre lo que hace que no se puedan
* repetir soluciones.
*/
void generarDar(int nivel){
  if(solucionesDar[nivel] == -1){
    if(nivel == 0) solucionesDar[nivel] = 0;
    else solucionesDar[nivel] = solucionesDar[nivel-1];
  }else {
      solucionesDar[nivel] = solucionesDar[nivel] + 1;
  }
}

/*
* GenerarRecibir se encarga de ganerar un hermano a partir de un nivel y una solucion
* para eso comprueba si es el primer nodo de ese nivel para esa solucion y si no lo es
* suma uno, si lo es lo inicializa al valor del padre lo que hace que no se puedan
* repetir soluciones.
*/
void generarRecibir(int nivel){
  if(solucionesRecibir[nivel] == -1){
    if(nivel == 0) solucionesRecibir[nivel] = 0;
    else solucionesRecibir[nivel] = solucionesRecibir[nivel-1];
  }else {
      solucionesRecibir[nivel] = solucionesRecibir[nivel] + 1;
  }
}

/*
* Solucion calcula si la solucion actual es solucion accediendo a valores, multiplicando cada
* elemento de la solucion por su valor y sumandolo en un contador que finalmente se
* compara con el valor que se quiere conseguir, si es igual se devuelve true y si no false.
*/
bool solucionDar(int nivel){
  int cont = 0;
  for(int i = 0; i <= nivel;i++){
    cont = cont + valores[solucionesDar[i]];
  }
  return (cont == V);
}


/*
* Solucion calcula si la solucion actual es solucion accediendo a valores, multiplicando cada
* elemento de la solucion por su valor y sumandolo en un contador que finalmente se
* compara con el valor que se quiere conseguir, si es igual se devuelve true y si no false.
*/
bool solucionRecibir(int nivel){
  int cont = 0;
  for(int i = 0; i <= nivel;i++){
    cont = cont + valores[solucionesRecibir[i]];
  }
  return (cont == V);
}

/*
* La funcion valor devuelve el valor que vale la solucion actual recorriendo el vector solucion,
* sumando el valor de todos los elementos en una variable y devolviendolo.
*/
int valorDar(){
  int cont = 0;
  for(int i = 0; i < tam;i++){
    cont = cont + valores[solucionesDar[i]];
  }
  return cont;
}

/*
* La funcion valor devuelve el valor que vale la solucion actual recorriendo el vector solucion,
* sumando el valor de todos los elementos en una variable y devolviendolo.
*/
int valorRecibir(){
  int cont = 0;
  for(int i = 0; i < tam;i++){
    cont = cont + valores[solucionesRecibir[i]];
  }
  return cont;
}

/*
* La funcion peso devuelve el peso que vale la solucion actual recorriendo el vector solucion,
* sumando el peso de todos los elementos en una variable y devolviendolo.
*/
int pesoDar(){
  int cont = 0;
  for(int i = 0; i < tam;i++){
    cont = cont + pesos[solucionesDar[i]];
  }
  return cont;
}

/*
* La funcion peso devuelve el peso que vale la solucion actual recorriendo el vector solucion,
* sumando el peso de todos los elementos en una variable y devolviendolo.
*/
int pesoRecibir(){
  int cont = 0;
  for(int i = 0; i < tam;i++){
    cont = cont + pesos[solucionesRecibir[i]];
  }
  return cont;
}

/*
* Calcula cual es la moneda que menos vale.
*/
int min(int inic){
  int minimo = valores[inic];
  for(int i = inic+1; i < N; i++){
    if(valores[i] < minimo) minimo = valores[i];
  }
  return minimo;
}

/*
* Esta función comprueba si dada una solucion y un nivel se puede bajar o hay
* que retroceder.
*/
bool criterioDar(int nivel){
    return ((nivel < tam)&&(valorDar()+min(solucionesDar[nivel]) <= V));
}

/*
* Esta función comprueba si dada una solucion y un nivel se puede bajar o hay
* que retroceder.
*/
bool criterioREcibir(int nivel){
    return ((nivel < tam)&&(valorRecibir()+min(solucionesRecibir[nivel]) <= V));
}

/*
* Cumprueba para un determinado nivel y solucion si hay más hermanos en ese nivel,
* comprobando en solucion[nivel] si el valor es menor que el numero de tipos.
*/
bool masHermanosDar(int nivel){
  return (solucionesDar[nivel]+1 < N);
}

/*
* Cumprueba para un determinado nivel y solucion si hay más hermanos en ese nivel,
* comprobando en solucion[nivel] si el valor es menor que el numero de tipos.
*/
bool masHermanosRecibir(int nivel){
  return (solucionesRecibir[nivel]+1 < N);
}

/*
* Esta función copia una array pasada por parametro, elemento a elemento y la
* devuelve haciendo que la asignacion de arrays no sea por puntero si no que sea
* a una copia en memoria.
*/
int* copiarArray(int* fuente){
  int* aux = new int[tam];
  for(int i = 0; i < tam ; i++) aux [i] = fuente[i];
  return aux;
}

/*
*La funcion backTracking genera una solucion en forma de vector que se construye
* como si fuera un arbol, va llamando en una iteracion a todas las funciones descritas
* anteriormente, primero generando un nuevo nodo en el primer nivel luego comprobando
* si ese nodo forma una solucion y si es la mejor solucion hasta el momento, despues
* ver si se puede bajar de nivel si si no se puede subir, así hasta que llege al nodo 0
*/
int backTrackingDar(void){
  int nivel = 0;
  int voa = 0;
  int* soa = new int[tam];
  for(int i = 0; i < tam; i++){
    solucionesDar[i] = -1;
    soa[i] = 0;
  }
  do{
    //cout << endl << endl;
      generarDar(nivel);
      if ((solucionDar(nivel)) && (pesoDar() > voa)) {
        voa = pesoDar();
        soa = copiarArray(solucionesDar); //SE PUEDE MEJORAR
      }

    if(criterioDar(nivel)){
      nivel = nivel + 1;
    } else {
      while(!masHermanosDar(nivel) && (nivel > -1)) {
        //RETROCEDER
        solucionesDar[nivel] = -1;
        nivel = nivel -1;

      }
    }
  }while(nivel > -1);
  if(voa == 0) {
    return -1;
  } else {

    for(int s = 0; s < tam; s++){
      solucionFinalDar[s]= 0;
    }
    for(int s = 0; s < tam; s++){
      if(soa[s] < 0)  break;
      solucionFinalDar[soa[s]]++;
    }

  }
	return voa;
}

/*
*La funcion backTracking genera una solucion en forma de vector que se construye
* como si fuera un arbol, va llamando en una iteracion a todas las funciones descritas
* anteriormente, primero generando un nuevo nodo en el primer nivel luego comprobando
* si ese nodo forma una solucion y si es la mejor solucion hasta el momento, despues
* ver si se puede bajar de nivel si si no se puede subir, así hasta que llege al nodo 0
*/
int backTrackingRecibir(void){
  int nivel = 0;
  int voa = 999999999;
  int* soa = new int[tam];
  for(int i = 0; i < tam; i++){
    solucionesRecibir[i] = -1;
    soa[i] = 0;
  }
  do{
    //cout << endl << endl;
      generarRecibir(nivel);
      if ((solucionRecibir(nivel)) && (pesoRecibir() < voa)) {
        voa = pesoRecibir();
        soa = copiarArray(solucionesRecibir); //SE PUEDE MEJORAR
      }

    if(criterioREcibir(nivel)){
      nivel = nivel + 1;
    } else {
      while(!masHermanosRecibir(nivel) && (nivel > -1)) {
        //RETROCEDER
        solucionesRecibir[nivel] = -1;
        nivel = nivel -1;
      }
    }
  }while(nivel > -1);
  if(voa == 999999999) {
    return -1;
  } else {

    for(int s = 0; s < tam; s++){
      solucionFinalRecibir[s]= 0;
    }
    for(int s = 0; s < tam; s++){
      if(soa[s] < 0)  break;
      solucionFinalRecibir[soa[s]]++;
    }

  }
	return voa;
}

/*
* Pinta la diferencia de los pesos de las soluciones de los dos avances rapidos
* y cada uno de los dos vectores solucion.
*/
void pintarResultados(void) {
	if((pDar < 0)||(pRecibir < 0)) cout << "IMPOSIBLE" << endl;
	else {
		cout << pDar - pRecibir << endl;
		for(int i = 0; i < N-1;i++){
			cout << solucionFinalDar[i] << " ";
		}
		cout << solucionFinalDar[N-1] << endl;
		for(int j = 0; j < N-1;j++){
			cout << solucionFinalRecibir[j] << " ";
		}
		cout << solucionFinalRecibir[N-1] << endl;
	}
}
//////////////////////////////////////////////////////////////
////////////        PROGRAMA PRINCIPAL        ////////////////
//////////////////////////////////////////////////////////////

int main (void)
{
  int T;
  cin >> T;
  for (int i= 0; i<T; i++) {
  	leerEntrada();
    pDar = backTrackingDar();
  	pRecibir = backTrackingRecibir();
  	pintarResultados();
  	liberarVariables();
  }
}
