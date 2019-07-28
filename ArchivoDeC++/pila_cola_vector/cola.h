#ifndef __COLA_H
#define __COLA_H

#include <iostream>

using namespace std;

class Cola{
	private:
		char letras[500];
		int nelem;
	public:
		Cola();
		Cola(const Cola &c);
		//~Cola();
		bool Vacia() const;
		void Poner(char c);
		void Quitar();
		char Frente();	
		//Cola & operator=(const Cola &c);
};

#endif