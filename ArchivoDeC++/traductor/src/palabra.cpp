 #include <iostream>
#include <vector>
#include <string>
#include "palabra.h"

using namespace std;

//Constructor por defecto
Palabra::Palabra()
{
	origen="";
	for(unsigned i=0;i<traducidas.size();i++)
	{
		traducidas[i]="";
	}
}
//Constructor por parametros
Palabra::Palabra(vector <string> datos)
{
	unsigned j=1;
	origen=datos[0];
	for(unsigned i=0;i<datos.size();i++)
	{
		traducidas[i]=datos[j];
		j++;
	}
}
//consultor de origen
string Palabra::GetPalabra()
{
	return origen;
}
//consultor de traducidas
vector <string> Palabra::GetTraducidas()
{
	return traducidas;
}
//Operador >>
istream& operator>>(istream &is,Palabra &P)
{
	string auxiliar;
	getline(is,auxiliar); //voy cojiendo de linea en linea
	unsigned i=0;
	//primero cojo la palabra en el idioma origen hasta el primer ';'
	while(auxiliar[i]!=';')
	{
		P.origen.push_back(auxiliar[i]);
		i++;
	}
	//despues cojo sus traducciones que van separadas por ';' hasta el final de la linea
	while(i<auxiliar.size())
	{
		if(auxiliar[i]==';')
		{
			P.traducidas.push_back("");	//crea una hueco en el vector traducidas cada vez que encuentra un ';'
			i++;
		}
		P.traducidas[P.traducidas.size()-1].push_back(auxiliar[i]);	//inserto cada traducida en la ultima posicion 
		i++;
	}
	return is;
}
