#include "pila.h"

Pila::Pila()
{
	nelem=0;
}
Pila::Pila(const Pila &p)
{
	nelem=p.nelem;
	for(int i=0;i<nelem;i++){
		letras[i]=p.letras[i];
	}
}
bool Pila::Vacia() const
{
	if(nelem==0)
		return true;
	else
		return false;
}
void Pila::Poner(char c)
{
	letras[nelem+1]=c;
	nelem++;
}
void Pila::Quitar()
{
	nelem--;
}
char Pila::Tope()
{
	return letras[nelem];
}

int Pila::Nelem()
{
	return nelem;
}






