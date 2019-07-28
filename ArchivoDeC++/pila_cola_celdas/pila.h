#ifndef __PILA_H_
#define __PILA_H_

#include <iostream>

using namespace std;

struct Celda{
	char elemento;
	Celda *sig;
};

class Pila{
	private:
		Celda *primera;
	public:
		Pila();
		Pila(const Pila &p);
		~Pila();
		bool Vacia() const;
		void Poner(char c);
		void Quitar();
		char Tope();	
		Pila & operator=(const Pila &p);
};

#endif