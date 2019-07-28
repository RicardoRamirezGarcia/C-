#ifndef _pila_celda_h_
#define _pila_celda_h_

#include <cassert>

template <class T>
class Pila{
	private :
		struct Celda{
			T elemento;
			Celda * siguiente;
			//-------------------------------
			Celda(): siguiente(0){}
			Celda(const T &elem,Celda *sig){
				elemento=elem;
				siguiente=sig;
			}
			Celda & operator=(const Celda *C){
				elemento=C.elemento;
				siguiente=C.siguiente;
			}				 
		};
		Celda * primera;
		int num_elem;
	public:
		Pila(): primera(0),num_elem(0){}
		//Pila(const Pila<T> &p);	//en cpp
		//~Pila(); //en cpp
		//Pila & operator=(const Pila<T> &p); //en cpp
		bool Vacia() const {
			return primera==0;
		}
		T & Tope(){
			assert(primera!=0);
			return primera->elemento;
		}
		void Poner(const T& elem); //en cpp
		void Quitar(); //en cpp
		int Size() const {return num_elem;}
				
};

#include "pila.cpp"
#endif







