#include <iostream>
#include <vector>
#include <string>
#include "palabra.h"
#include "traductor.h"
//constructor vacio
Traductor::Traductor(){

}
//consultor de las traduciones de origen
vector <string> Traductor::GetTraducciones(string &origen)
{
	bool encontrada=false;
	vector<string> traducid;
	for(unsigned i=0;i<traduc.size() && encontrada==false;i++)
	{
		if(origen==traduc.at(i).GetPalabra())
		{
			traducid=traduc.at(i).GetTraducidas();
			encontrada=true;		
		}
	}
	return traducid;
}
//Operador >>
istream& operator>>(istream &is,Traductor &T)
{
	while(is.good())
	{
		Palabra aux;
		is>>aux;
		T.traduc.push_back(aux);		
	}
	return is;
}
