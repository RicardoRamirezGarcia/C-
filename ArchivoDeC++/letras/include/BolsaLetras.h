#ifndef __BolsaLetras_h__
#define __BolsaLetras_h__

#include <set>
#include <iostream>
#include <string>
#include "ConjuntoLetras.h"
#include "Letra.h"

using namespace std;

/**
 * @brief TDA BolsaLetras
 * @details Almacena tantas veces las letras repetidas como indica su valor en repeticiones
 *
 */
class BolsaLetras
{

private:

 	/**
 	 * @brief Representación de la bolsa de letras (un multiset)
 	 */
 	multiset<Letra, Letra::cmp> bolsa;

public:

	/**
	 * @brief Devuelve Tamaño del conjunto de letras (abecedario)
	 *
	 * @return Tamaño del conjunto de letras
	 */
	int size()
	{
		return bolsa.size();
	}

	/**
	 * @brief Obtiene una letra en base a su posicion
	 *
	 * @param n posicion de la letra
	 */
    const Letra & operator[](int n) const
    {
		multiset<Letra>::iterator it = bolsa.begin();
		advance(it, n);  //incrementa el iterador n posiciones
		return *it;
    };

	/**
	 * @brief Pinta una bolsa de letras en un objeto ostream (os)
	 *
	 * @param os la referencia al ostream donde escribir
	 * @param bl Bolsa de Letras desde el que leer
	 */
	friend ostream & operator<<(ostream & os, const BolsaLetras &bl)
	{
		set<Letra>::iterator it = bl.bolsa.begin();

		for (; it!=bl.bolsa.end(); ++it )
			os << *it << endl;

		return os;
	}

	/**
	 * @brief Llena una bolsa de letras desde un istream
	 *
	 * @param is la referencia al istream desde el que leer
	 * @param bl Bolsa de Letras en el que escribir
	 */
	friend ConjuntoLetras & operator>>(ConjuntoLetras &cl, BolsaLetras &bl)
	{ 
		// Recorremos las letras
		for (int i=0; i<cl.size(); i++)
		{
			Letra letra = cl[i];
			//y creamos tantas letras en la bolsa como cantidad tenga cada letra
			for (int j=0; j<&letra; j++)
			{
				bl.bolsa.insert(letra);
			} 
		}
		return cl;
	}

};

#endif