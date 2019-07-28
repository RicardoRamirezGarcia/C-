#include "binario.h"
#include <iostream>
//#include "cola.h"

using namespace std;

//hacer un nodo raiz y hoja con etiqueta 'e'
CeldaArbolB *CreaRaiz(const int e){
	CeldaArbolB *n = new CeldaArbolB;
	n->elemento=e;
	n->padre=0;
	n->izquierda=0;
	n->derecha=0;
}

CeldaArbolB *InsertarHijoIzquierda(CeldaArbolB *T1,CeldaArbolB *n,CeldaArbolB *&T2){
	CeldaArbolB *res =n->izquierda;
	//si habia hijo a la izquierda le quito que tenga padre
	if(res!=0)
		res->padre=0;
	//se le mete el nuevo hijo a el nodo
	n->izquierda=T2;
	if(T2!=0)
		T2->padre=n;
	return res;
}	

void EscribirArbol(const CeldaArbolB *T){
	if(T==0)
		cout << "x" <<endl;
	else{
		cout << "n " << T->elemento << ' ';
		EscribirArbol(T->izquierda);
		EscribirArbol(T->derecha);
	}
}


int main(){
	//Crear el padre
	CeldaArbolB *n=CreaRaiz(0);
	//insertar hijos
	CeldaArbolB *uno=new CeldaArbolB(n,1,'i');
	CeldaArbolB *otro=new CeldaArbolB(n,2,'d');

	CeldaArbolB *hij=new CeldaArbolB(uno,5,'i');

	cout << " " << n->elemento << endl;
	cout << n->izquierda->elemento << " " << n->derecha->elemento << endl;

	CeldaArbolB *t2=CreaRaiz(3);
	CeldaArbolB *t2der=new CeldaArbolB(t2,4,'d');

	CeldaArbolB *nuevo=InsertarHijoIzquierda(n,uno,t2);
	cout << nuevo->elemento << endl;	//tiene que ser 0

	EscribirArbol(n);	
	
}



















