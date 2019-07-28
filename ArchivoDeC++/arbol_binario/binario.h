#ifndef ARBOL_B_
#define ARBOL_B_


#include <iostream>

using namespace std;

struct CeldaArbolB{
			int elemento;
			CeldaArbolB *padre,*izquierda,*derecha;

			CeldaArbolB(){
				padre=izquierda=derecha=0;
			}

			//INSERTAR UN HIJO 
			CeldaArbolB(CeldaArbolB *&pa,int e,char izde){
				elemento=e;
				padre=pa;
				if(izde=='i')
					pa->izquierda=this;
				else if(izde=='d')
					pa->derecha=this;
				izquierda=derecha=0;
			}
};

#endif
