#include <iostream>
#include <algorithm>

//constructor de copia
/*template <class T>
Pila<T>::Pila(const Pila<T> &p){
	if(p.primera!=0){
		Celda *orig=p.primera;
		Celda *nueva;
		primera=nueva=new Celda(orig->elemento,0);
		orig=orig->siguiente;
		while(orig!=0){
			nueva->siguiente=new Celda(orig->elemento,0);
			nueva=nueva->siguiente;
			orig=orig->siguiente;
		}
	}
	else
		primera=0;
	num_elem=p.num_elem;
}
//destructor
template <class T>
Pila<T>::~Pila(){
	Celda *aux;
	while(primera!=0){
		aux=primera;
		primera=primera->siguiente;
		delete aux;
	}
}*/
//operador de asignacion
/*template <class T>
Pila & Pila<T>::operator=(const Pila<T> &p){
	Pila<T> aux(p);
	std::swap(this->primera,aux.primera);
	std::swap(this->num_elem,aux.num_elem);

	return *this;
}*/
//Poner
template <class T>
void Pila<T>::Poner(const T& elem){
	primera=new Celda(elem,primera);
	num_elem++;
}
//Quitar
template <class T>
void Pila<T>::Quitar(){
	assert(primera!=0);
	Celda *aux=primera;
	primera=primera->siguiente;
	delete aux;
	num_elem--;
}






























