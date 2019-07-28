#include <iostream>
//#include "cola.h"
#include "pila.h"

using namespace std;
	
int main()
{
	//Cola q;
	Pila <char> p();
	char dato;

	cout << "Escriba una frase " << endl;
	while((dato=cin.get()) != '\n')
	{
		if (dato!= ' ')
		{
			//q.Poner(dato);
			p.Poner(dato);
		}
	}

	/*bool palindromo=true;

	while(!p.Vacia() && palindromo){
		if(p.Tope() != q.Frente())
			palindromo=false;
		p.Quitar();
		q.Quitar();
	}

	if(palindromo)
		cout << " Esta frase es un palindromo " << endl;
	else 
		cout << " Esta frase  NO es un palindromo " << endl;*/

	/*while(q.Frente() != '\n')
	{
		cout << q.Frente() << endl;
		q.Quitar();
	}

	cout << endl;*/

	while(p.Size() != 0)
	{
		cout << p.Tope() << endl;
		p.Quitar();
	}
	
}








