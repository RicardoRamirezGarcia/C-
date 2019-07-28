/**
  * @file cola.h
  * @brief Fichero cabecera del TDA Cola
  *
  * Gestiona una secuencia de elementos con facilidades para la inserción y
  * borrado de elementos en un extremo
  */

#ifndef __VECTOR_DINAMICO_H__
#define __VECTOR_DINAMICO_H__

#include "vectordinamico.cpp"

/**
 *  @brief T.D.A. 	Vector Dinamico
 *
 *
 * Una instancia @e c del tipo de dato abstracto  sobre un dominio @e T es
 * una sucesión finita de elementos del mismo con un funcionamiento @e FIFO
 * (First In, First Out}). En una cola, las operaciones de inserción tienen
 * lugar en uno de los extremos, denominado @e final de la cola, mientras que
 * el borrado y consulta se lleva a cabo en el otro extremo, denominado 
 * @e frente de la cola. Una cola de longitud @e n la denotamos

 * - <a1,a2,a3,..,an<

 * En esta cola, tendremos acceso únicamente al elemento del @e Frente,
 * es decir, a @e a1. El borrado o consulta de un elemento será sobre @e a1,
 * mientras que la inserción de un nuevo elemento se hará después de
 * @e an (final de la cola).
 *
 * Si n=0 diremos que la cola está vacía.
 *
 * El espacio requerido para el almacenamiento es O(n), donde n es el número 
 * de elementos de la cola.
 *
 * @author 
 * @date 
*/

template <class T>
class VectorDinamico
{	
	private:
		T *datos;			///<vector dinamino para los datos
		int nelementos;		///<numero de elemtos del vector
	public:
		VectorDinamico();
		VectorDinamico(const VectorDinamico<T> &V);
		~VectorDinamico();
		void resize()
		void poner();
		VectorDinamico& operator= (const VectorDinamico<T> &V);
		int size();
		const T operator[](int pos);
	
};