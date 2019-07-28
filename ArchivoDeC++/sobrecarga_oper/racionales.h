#ifndef __RACIONALES_H
#define __RACIONALES_H

#include <iostream>

using namespace std;

class Racional{
	private:
		int numerador,denominador;
	public:
		Racional(int i,int j): numerador(i),denominador(j) {}
		int Numerador()	const {return numerador;} 
		int Denominador() const  {return denominador;}
};

inline Racional operator+(Racional &r1,Racional &r2){
	return Racional(r1.Numerador()+r2.Numerador(),r1.Denominador()+r2.Denominador());
}


#endif