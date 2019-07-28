#ifndef __ConjuntoLetras_h__
#define __ConjuntoLetras_h__

#include <set>
#include <iostream>
#include <string>
#include "Letra.h"

using namespace std;

/**
 * @brief TDA ConjuntoLetras
 * @details se llena desde un fichero
 *
 */
class ConjuntoLetras
{

private:

 	/**
 	 * @brief Representación del conjunto de letras (un set)
 	 */
 	set<Letra, Letra::cmp> abecedario;

public:

	/**
	 * @brief Devuelve Tamaño del conjunto de letras (abecedario)
	 *
	 * @return Tamaño del conjunto de letras
	 */
	int size()
	{
		return abecedario.size();
	}

	/**
	 * @brief Obtiene una letra en base a su posicion
	 *
	 * @param n posicion de la letra
	 */
    const Letra & operator[](int n) const
    {
		set<Letra>::iterator it = abecedario.begin();
		advance(it, n); //incrementa el iterador n posiciones
		return *it;
    };

    /**
     * @brief Obtiene la puntuación de una palabra
     *
     * @param p le pasamos la palabra como string
     * @return Un entero con la suma de las puntuaciones de las letras de la palabra
     */
    int puntuacion(string p)
    {
    	int puntos = 0;

    	// Para cada letra en la palabra...
    	for (int i=0;i<p.size(); i++)
    	{
    		bool salir = false;

    		// ...la busca en el conjunto...
    		for (set<Letra>::iterator it = abecedario.begin(); !salir && it!=abecedario.end(); ++it )
    		{
    			Letra l = *it;
    			// ... y si coincide...
    			if (p[i] == tolower(*l))
    			{
    				// ...incrementa el contador de puntos
					puntos  +=  it->getPuntos();
					salir = true;
	    		}
    		}
    	}

		return puntos;
    }

	/**
	 * @brief Pinta un conjunto de letras en un ostream
	 *
	 * @param os referencia al ostream donde escribir
	 * @param cl Conjunto de Letras desde el que leer
	 */
	friend ostream & operator<<(ostream & os, const ConjuntoLetras &cl)
	{
		set<Letra>::iterator it = cl.abecedario.begin();

		for (; it!=cl.abecedario.end(); ++it )
			os << *it << endl;

		return os;
	}

	/**
	 * @brief Llena un conjunto de letras desde un istream
	 *
	 * @param is la referencia al istream desde el que leer
	 * @param cl Conjunto de Letras en el que escribir
	 */
	friend istream & operator>>(istream & is, ConjuntoLetras &cl)
	{
		//Obtenemos la primera línea que hay que ignorar
		string primera_linea;
		getline(is, primera_linea);

		while (is)
		{
			char c;
			int n, p;

			// Obtenemos los valores (char, int, int)
			is >> c >> n >> p;

			// Creamos una nueva letra
			Letra l(c, n, p);

			// Agregamos la letra al conjunto
			cl.abecedario.insert(l);
		}

		return is;
	}

};


#endif  















