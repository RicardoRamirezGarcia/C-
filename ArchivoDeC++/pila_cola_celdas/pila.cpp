#include "pila.h"

Pila::Pila()
{
	primera=0;
}
Pila::Pila(const Pila &p)
{
	if(p.primera==0)
		primera=0;
	else{
		primera= new Celda;
		primera->elemento=p.primera->elemento;
		Celda *aux=p.primera;
		Celda *dest=primera;
		while(aux->sig != 0){
			dest->sig=new Celda;
			aux=aux->sig;
			dest=dest->sig;
			dest->elemento=aux->elemento;
		}
		dest->sig=0;
	}
}
Pila::~Pila(){
	Celda *aux;
	while(primera!= 0){
		aux=primera;
		primera=primera->sig;
		delete aux;
	}	
}
bool Pila::Vacia() const
{
	return primera==0;
}
void Pila::Poner(char c)
{
	Celda *aux=new Celda;
	aux->elemento=c;
	aux->sig=primera;
	primera=aux;
}
void Pila::Quitar()
{
	Celda *aux=primera;
	primera=primera->sig;
	delete aux;
}
char Pila::Tope()
{
	return primera->elemento;
}


Pila & Pila::operator=(const Pila &p){
	Pila paux(p);
	Celda *aux;
	aux=this->primera;
	this->primera=paux.primera;
	paux.primera=aux;
	return *this;
}





