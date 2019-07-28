#include <cassert>

/* _________________________________________________________________________ */
template <class T>
Lista::Posicion & Lista::Posicion::operator--()
{
	assert(puntero! =primera);
	CeldaLista ∗aux=primera;
	while(aux→siguiente! =puntero)
		aux=aux→siguiente;
		puntero= aux;
		return ∗this;
}

/* _________________________________________________________________________ */
template <class T>
Lista<T>::Lista(const Lista<T> &l)
{
	cab= new CeldaLista;
	CeldaCola ∗src=c.primera;
	ultima=cab;
	while (src→siguiente! =0)
	{
		ultima→siguiente= new CeldaLista;
		src= src→siguiente;
		ultima= ultima→siguiente;
		ultima→elemento= src→elemento;
	}
	ultima→siguiente=0;
}

/* _________________________________________________________________________ */
template <class T>
Lista<T>::∼Lista() {
	CeldaLista ∗aux;
	while (cab! =0)
	{
	aux=cab;
	cab= cab→siguiente;
	delete aux;
	}
}

/* _________________________________________________________________________ */
template <class T>
Lista<T>& Lista<T>::operator= (const Lista<T> & l)
{
	Lista aux(l);
	CeldaLista ∗p;
	p= this→cab;
	this→cab= aux→cab;
	aux→cab=p;
	p= this→ultima;
	this→ultima= aux→ultima;
	aux→ultima=p;
	return ∗this;
}

/* _________________________________________________________________________ */
template <class T>
Lista::Posicion Lista<T>::insertar(Lista::Posicion p,Tbase e)
{
	CeldaLista ∗q= new CeldaLista;
	q→siguiente=p.puntero→siguiente;
	p.puntero→siguiente=q;
	q→elemento= e;
	if (p.puntero==ultima) 
		ultima=q;
	return p; 
}

/* _________________________________________________________________________ */
template <class T>
Lista::Posicion Lista<T>::borrar(Lista::Posicion p)
{
	assert (p! =end());
	CeldaLista ∗q= p.puntero→siguiente;
	p.puntero→siguiente=q→siguiente;
	if (q==ultima)
		ultima=p.puntero;
	delete q;
	return p;
}






