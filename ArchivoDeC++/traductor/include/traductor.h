
/**
  * @file palabra.h
  * @brief Fichero cabecera del TDA palabra
  *
  */

#ifndef _TRADUCTOR_H
#define _TRADUCTOR_H

#include <vector>
#include "palabra.h"
#include <string>

using namespace std;

/**
  *  @brief T.D.A. traductor
  *
  * Una instancia @e c del tipo de datos abstracto @c traductor es un objeto
  * del conjunto del vocabulario de diferentes idiomas, compuesto por un vector de palabras en idioma origen y con sus traducidas
  * Lo representamos
  *
  * origen1;traducida1;traducida2;origen2;traducida3;traducida4.....
  *
  * Un ejemplo de su uso:
  * @include pruebatraductor.cpp
  *
  * @author Felix Ramirez Garcia
  * @date Noviembre de 2014
  */

class Traductor
{
	private:
/**
  * @page reptraductor Rep del TDA traductor
  *
  *
  * @section fatraductor Función de abstracción
  *
  * Un objeto válido @e rep del TDA traductor representa al valor
  *
  * (rep.origen1;rep.traducidas1;rep.traducidas2;rep.origen2;rep.traducidas3;rep.traducidas4....) 
  *
  */
		vector<Palabra> traduc;	/**< traduc */
	public:
/**
  * @brief Constructor por defecto de la clase. Crea un traductor vacio.
  */
		Traductor();
/**
  * @brief GetTraducciones
  * @return Devuelve un vector de string con las traducidas de origen
  */
		vector <string> GetTraducciones(string &origen);
/**
  * @brief Entrada de un traductor desde istream
  * @param is stream de entrada
  * @param T es eltraductor que recibe is 
  * @retval El traductor leido es T
  * @pre La entrada tiene el formato (rep.origen1;rep.traducidas1;rep.traducidas2;rep.origen2;rep.traducidas3;rep.traducidas4....) 
  */
		friend istream& operator>>(istream &is,Traductor &T);	
};

#endif
