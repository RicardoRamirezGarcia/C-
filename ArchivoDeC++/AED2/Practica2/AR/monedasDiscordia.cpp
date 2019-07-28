#include <stdlib.h>  // Funcion exit
#include <string.h>  // Funcion memset
#include <iostream>  // Variables cin y cout
#include <sys/time.h>
#include <list>
using namespace std;

#define MAX_N 300

//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int difPeso;                  	// Diferencia de peso
int* valores;                 	// Vector de los valores de monedas
bool* validas;			// Monedas que aún se pueden coger
int* pesos;			// Vector de pesoss de cada tipo de moneda
int* solucionesDevolver;		// Vector solucion 1
int* solucionesRecibir;	// Vector solucion 2
double* pesoValor;
int N;				// Numero de tipos
int V;				// Valor a Recibir

long long mseconds(){
  struct timeval t;
  gettimeofday(&t, NULL);
//Guarda en t los segundos y microsegundos transcurridos desde una fecha fija
//Se pasa todo a microsegundos
  return t.tv_sec*1000000 + t.tv_usec;
}

void generadorDeCasos(int n){
	//SE LEEN LOS DOS VALORES DE ENTRADA (CANTIDAD,TIPOS)
	N  = n;
	V = 400;
	//QUITAMOS LA RESTRINCION PARA HACER EL CALCULO
	//SE CREAN TODOS LOS VECTORES DINAMICOS DEL TAMAÑO DEL NUMERO DE TIPOS DE FORMA QUE OCUPEN SOLO EL ESPACIO EN MEMORIA NECESARIO
	valores = new int[N];
	pesos = new int[N];
	validas = new bool[N];
	solucionesDevolver = new int[N];
	solucionesRecibir = new int[N];
	pesoValor = new double[N];
	//SE LEEN LOS VALORES DE LAS MONEDAS
	valores[0] = 1;
	for(int i = 1; i < N; i++){
	valores[i] = (rand()%99)+1;
	}
	//SE LEEN LOS PESOS DE LAS MONEDAS
	for(int j = 0; j < N; j++){
	pesos[j] = (rand()%99)+1;
	}
	//SE RELLENA LA TABLA PESOVALOR A PARTIR DE LAS DOS TABLAS ANTERIORES.
	for(int k = 0; k < N; k++){
	pesoValor[k] = (float)pesos[k]/(float)valores[k];
	}
}

/*
* Esta función se utiliza para leer las variables por pantalla, seguidamente se
* los vectores necesario para la resolucion del ejercicio.
*/
void leerEntrada(void){
	//SE LEEN LOS DOS VALORES DE ENTRADA (CANTIDAD,TIPOS)
	cin >> N >> V;
	if ((N>MAX_N)||(N<0)||(V<0)) {
   		cerr << "Los valores de entrada son incorrectos\n";
    		exit(0);
  	}
	//SE CREAN TODOS LOS VECTORES DINAMICOS DEL TAMAÑO DEL NUMERO DE TIPOS DE FORMA QUE OCUPEN SOLO EL ESPACIO EN MEMORIA NECESARIO
	valores = new int[N];
	pesos = new int[N];
	validas = new bool[N];
	solucionesDevolver = new int[N];
	solucionesRecibir = new int[N];
	pesoValor = new double[N];
	//SE LEEN LOS VALORES DE LAS MONEDAS
	for(int i = 0; i < N; i++){
	cin >> valores[i];
	}
	//SE LEEN LOS PESOS DE LAS MONEDAS
	for(int j = 0; j < N; j++){
	cin >> pesos[j];
	}
	//SE RELLENA LA TABLA PESOVALOR A PARTIR DE LAS DOS TABLAS ANTERIORES.
	for(int k = 0; k < N; k++){
	pesoValor[k] = (float)pesos[k]/(float)valores[k];
	}
}

/*
* Esta función se utiliza para los vecores que se crean dinamicamente despues
* de leer los valores.
*/
void liberarVariables(){
	delete[] valores;
	delete[] validas;
	delete[] pesos;
	delete[] solucionesDevolver;
	delete[] solucionesRecibir;
	delete[] pesoValor;

}

/*
* Esta función recorre el array de validas y comprueba si alguno de los elementos
* aun no ha sido escogido por el algoritmo de avance rapido.
*/
bool hayValidas(){
	for(int i = 0; i < N; i++){
		if(validas[i] == true) return true;
	}
	return false;
}

/*
* Esta funcion recorre el array solucionDevolver y va sumando en un contador los
* valores de los objetos seleccionados. Finalmente comprueba que ese valor es una
* solucion comparando si es igual al valor que se quiere.
*/
bool solucionDevolver(){
	int cont = 0;
	for(int i = 0; i < N; i++){
		cont = cont + solucionesDevolver[i]*valores[i];
	}
	if(cont == V) return true;
	return false;
}

/*
* Esta funcion recorre el array solucionRecibir y va sumando en un contador los
* valores de los objetos seleccionados. Finalmente comprueba que ese valor es una
* solucion comparando si es igual al valor que se quiere.
*/
bool solucionRecibir(){
	int cont = 0;
	for(int i = 0; i < N; i++){
		cont = cont + solucionesRecibir[i]*valores[i];
	}
	if(cont == V) return true;
	return false;
}

/*
* Esta funcion recorre el array solucionDevolver y va sumando en un contador los
* valores de los objetos seleccionados. Finalmente devuelve el valor.
*/
int valorDevolver(){
	int cont = 0;
	for(int i = 0; i < N; i++){
		cont = cont + solucionesDevolver[i]*pesos[i];
	}
	return cont;
}

/*
* Esta funcion recorre el array solucionRecibir y va sumando en un contador los
* valores de los objetos seleccionados. Finalmente devuelve el valor.
*/
int valorRecibir(){
	int cont = 0;
	for(int i = 0; i < N; i++){
		cont = cont + solucionesRecibir[i]*pesos[i];
	}
	return cont;
}

/*
* Esta función se encarga de seleccionar el elemento optimo que no se haya seleccionados
* ya para ello coge el objeto que mas proporcion peso valor tenga y si empatan coge el que
* mas vale.
*/
int seleccionarDevolver(){
	int j = 0;
	while(!validas[j]) j++;
	int max = j;
	for(int i = 0; i < N;i++){
		if(validas[i]){
			if(pesoValor[i] >= pesoValor[max]) {
				if(pesoValor[i] == pesoValor[max]){
					if(valores[i] >= valores[max]) max = i;
				} else {
					max = i;
				}
			}
		}
	}
	return max;
}


/*
* Esta función se encarga de seleccionar el elemento optimo que no se haya seleccionados
* ya para ello coge el objeto que mas proporcion peso valor tenga y si empatan coge el que
* menos vale.
*/
int seleccionarRecibir(){
	int j = 0;
	while(!validas[j]) j++;
	int min = j;
	for(int i = 0; i < N;i++){
		if(validas[i]){
			if(pesoValor[i] <= pesoValor[min]) {
				if(pesoValor[i] == pesoValor[min]){
					if(valores[i] <= valores[min]) min = i;
				} else {
					min = i;
				}
			}
		}
	}
	return min;
}

/*
* Comprueba si lo que queda para devolver la cantidad deseada es menor que
* el valor del elemento actual y devuelve true o false.
*/
bool factibleDevolver(int elem){
	int x = 0;
	for(int i = 0; i < N;i++){
		x = x + solucionesDevolver[i]*valores[i];
	}
	if((V-x)/valores[elem] == 0) return false;
	return true;
}

/*
* Comprueba si lo que queda para devolver la cantidad deseada es menor que
* el valor del elemento actual y devuelve true o false.
*/
bool factibleRecibir(int elem){
	int x = 0;
	for(int i = 0; i < N;i++){
		x = x + solucionesDevolver[i]*valores[i];
	}
	if((V-x)/valores[elem] == 0) return false;
	return true;
}

/*
* Inserta en la posicion correspondiente a la moneda elem el numero maximo de
* monedas de ese tipo que se pueden meter para completar
*/
void insertarDevolver(int elem) {
	int x = 0;
	for(int i = 0; i < N;i++){
		x = x + solucionesDevolver[i]*valores[i];
	}
	solucionesDevolver[elem] = (V-x)/valores[elem];
}

/*
* Inserta en la posicion correspondiente a la moneda elem el numero maximo de
* monedas de ese tipo que se pueden meter para completar
*/
void insertarRecibir(int elem) {
	int x = 0;
	for(int i = 0; i < N;i++){
		x = x + solucionesRecibir[i]*valores[i];
	}
	solucionesRecibir[elem] = (V-x)/valores[elem];
}

/*
* La función de avanceRapidoRecibir se encarga de ir cogiendo una a una las monedas
* necesarias para componer la solución, para ello ello en cada iteracion va eligiendo
* la moneda más adecuada, una vez que selecciona una moneda esa moneda se descarta
* y no se vuelve a seleccionar. Utiliza las funciones que hacen referencia a recibir.
*/
void avanceRapidoDevolver(void){
	//inicializar los vectores necesarios
	for(int i = 0; i < N;i++){
		validas[i] = true;
		solucionesDevolver[i] = 0;
	}
	int x;//MONEDA QUE SE SELECIONA EN CADA ITERACION

	while(hayValidas() && !solucionDevolver()){
		x = seleccionarDevolver();
		validas[x] = false;
		if(factibleDevolver(x)) insertarDevolver(x);
	}
	if(!solucionDevolver()) cout << "No se ha encontrado la solcucion" << endl;
}

/*
* La función de avanceRapidoRecibir se encarga de ir cogiendo una a una las monedas
* necesarias para componer la solución, para ello ello en cada iteracion va eligiendo
* la moneda más adecuada, una vez que selecciona una moneda esa moneda se descarta
* y no se vuelve a seleccionar. Utiliza las funciones que hacen referencia a Devolver.
*/
void avanceRapidoRecibir(void){
	//inicializar los vectores necesarios
	for(int i = 0; i < N;i++){
		validas[i] = true;
		solucionesRecibir[i] = 0;
	}

	int x;//MONEDA QUE SE SELECIONA EN CADA ITERACION

	while(hayValidas() && !solucionRecibir()){
		x = seleccionarRecibir();
		validas[x] = false;
		if(factibleRecibir(x)) insertarRecibir(x);
	}
	if(!solucionRecibir()) cout << "No se ha encontrado la solcucion" << endl;
}

/*
* Pinta la diferencia de los pesos de las soluciones de los dos avances rapidos
* y cada uno de los dos vectores solucion.
*/
void pintarResultados(void) {
	cout << valorDevolver() - valorRecibir() << endl;
	for(int i = 0; i < N-1;i++){
		cout << solucionesDevolver[i] << " ";
	}
	cout << solucionesDevolver[N-1] << endl;
	for(int j = 0; j < N-1;j++){
		cout << solucionesRecibir[j] << " ";
	}
	cout << solucionesRecibir[N-1] << endl;

}
//////////////////////////////////////////////////////////////
////////////        PROGRAMA PRINCIPAL        ////////////////
//////////////////////////////////////////////////////////////

int main (void)
{
  int T;//= 300;
  cin >> T;
	//long long ti,tf;
	//cout << "n" << "\t" << "tiempo" << endl;
  for (int i= 0; i<T; i++) {
		leerEntrada();
		//generadorDeCasos((i+1)*100);
		//ti = mseconds();
  	avanceRapidoRecibir();
		avanceRapidoDevolver();
		//tf = mseconds();
		pintarResultados();
		//cout << (i+1)*100 << "\t" << (tf - ti) << endl;
		//cerr << (i+1)*100 << "\t" << (tf - ti) << endl;
		liberarVariables();
  }
}
