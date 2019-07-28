
/**
  * @file palabra.h
  * @brief Fichero cabecera del TDA palabra
  *
  */

#ifndef _PALABRA_H
#define _PALABRA_H

#include <string>
#include <iostream>
#include <vector>


using namespace std;

/**
  *  @brief T.D.A. palabra
  *
  * Una instancia @e c del tipo de datos abstracto @c palabra es un objeto
  * del conjunto del vocabulario de diferentes idiomas, compuestos por una palabra en el idioma
  * origen,y un conjunto de palabras con sus traducciones. Lo representamos
  *
  * origen;traducida1;traducida2....
  *
  * Un ejemplo de su uso:
  * @include pruebatraductor.cpp
  *
  * @author Felix Ramirez Garcia
  * @date Noviembre de 2015
  */

class Palabra{
	private:

/**
  * @page reppalabra Rep del TDA palabra
  *
  *
  * @section fapalabra Función de abstracción
  *
  * Un objeto válido @e rep del TDA palabra representa al valor
  *
  * (rep.origen;rep.traducidas[i];rep.traducidas[i+1]) donde i empieza en '0' y va aumentando segun el numero de traduciones que tiene la palabra origen
  *
  */

		string origen;	/**< origen */
		vector <string> traducidas;	/**< traducidas */
//operaciones
	public:
/**
  * @brief Constructor por defecto de la clase. Crea una palabra vacia, con origen y traducidas como vectores de char vacios
  */
		Palabra();

/**
  * @brief Constructor de la clase
  * @param datos vector de string a construir con un string origen y sus traducidas
  * @return Crea la palabra origen con sus traducidas
  */
		Palabra(vector <string> datos);

/**
  * @brief Getpalabra
  * @return Devuelve un string con la palabra en el idioa origen
  */
		string GetPalabra();

/**
  * @brief GetTraducidas
  * @return Devuelve un vector de string con las traducidas de origen
  */
		vector <string> GetTraducidas();

/**
  * @brief Entrada de una palabra desde istream
  * @param is stream de entrada
  * @param P es la palabra que recibe is 
  * @retval La palabra leida es P
  * @pre La entrada tiene el formato (rep.origen;rep.traducidas[i];rep.traducidas[i+1]...) donde i empieza en '0' y va aumentando segun el numero de traduciones que tiene la palabra origen
  */
		friend istream& operator>>(istream &is,Palabra &P);	
};

#endif