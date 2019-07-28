#include "cola.h"
#include <cassert>

Cola::Cola()
{
	primera=0;
	ultima=0;
}
Cola::Cola(const Cola &c)
{
	if(primera==0)
		primera=ultima=0;
	else{
		primera=new CeldaCola;
		primera->elemento=c.primera->elemento;
		CeldaCola *aux=c.primera;
		ultima=primera;
		while(aux->sig != 0){
			ultima->sig= new CeldaCola;
			aux= aux-> sig;
			ultima= ultima-> sig;
			ultima->elemento=aux->elemento;		
		}
		ultima->sig=0;
	}
}
Cola::~Cola()
{
	CeldaCola *aux;
	while(primera != 0){
		aux=primera;
		primera=primera->sig;
		delete aux;
	}	
}
bool Cola::Vacia() const
{
	return primera==ultima;
}
void Cola::Poner(char c)
{
	CeldaCola *aux=new CeldaCola;
	aux->elemento=c;
	aux->sig=0;
	if(primera==0)
		primera=ultima=aux;
	else{
		ultima->sig=aux;
		ultima=aux;
	}
}
void Cola::Quitar()
{
	assert (primera != 0);
	CeldaCola *aux=primera;
	primera=primera->sig;
	delete aux;
	if(primera==0)
		ultima=0;
}
char Cola::Frente()
{
	return primera->elemento;
}
Cola & Cola::operator=(const Cola &c)
{
	Cola caux(c);
	CeldaCola *aux;
	aux=this->primera;
	this->primera=caux.primera;
	caux.primera=aux;
	aux=this->ultima;
	this->ultima=caux.ultima;
	caux.ultima=aux;
	return *this;
}























