#ifndef __COLA_H_
#define __COLA_H_

#include <iostream>

using namespace std;

struct CeldaCola{
	char elemento;
	CeldaCola *sig;
};

class Cola{
	private:
		CeldaCola *primera;
		CeldaCola *ultima;
	public:
		Cola();
		Cola(const Cola &c);
		~Cola();
		bool Vacia() const;
		void Poner(char c);
		void Quitar();
		char Frente();	
		Cola & operator=(const Cola &c);
};

#endif