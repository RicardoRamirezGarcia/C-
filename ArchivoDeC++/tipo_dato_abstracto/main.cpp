#include "matriz.h"
#include "utilidades.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main(){
	int filas,columnas;
	Matriz a,b,amasb,amenosb;

	cout <<"introduzca el numero de filas "<<endl;
	cin >> filas;
	cout <<"introduzca el numero de columnas "<<endl;
	cin >> columnas;

	cout <<"introduzca los elementos de a "<<endl;
	leerMatriz(a);
	cout <<"introduzca los elementos de b "<<endl;
	leerMatriz(b);

	crearMatriz(a,filas,columnas);
	crearMatriz(b,filas,columnas);
	crearMatriz(amasb,filas,columnas);
	crearMatriz(amenosb,filas,columnas);

	cout << "Resultados "<<endl;
	cout << "A :"<< endl;
	escribirMatriz(a);
	cout << "B :"<< endl;
	escribirMatriz(b);
	cout << "AMASB :"<< endl;
	escribirMatriz(amasb);
	cout << "AMENOSB :"<< endl;
	escribirMatriz(amenosb);

	destruirMatriz(a);
	destruirMatriz(b);
	destruirMatriz(amasb);
	destruirMatriz(amenosb);
	
}











