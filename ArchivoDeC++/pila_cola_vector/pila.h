#ifndef __PILA_H
#define __PILA_H

#include <iostream>

using namespace std;

class Pila{
	private:
		char letras[500];
		int nelem;
	public:
		Pila();
		Pila(const Pila &p);
		//~Cola();
		bool Vacia() const;
		void Poner(char c);
		void Quitar();
		char Tope();	
		int Nelem();
		//Cola & operator=(const Cola &c);
};

#endif