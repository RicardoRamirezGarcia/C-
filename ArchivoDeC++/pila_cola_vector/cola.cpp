#include "cola.h"

Cola::Cola()
{
	nelem=0;
}
Cola::Cola(const Cola &c)
{
	nelem=c.nelem;
	for(int i=0;i<nelem;i++){
		letras[i]=c.letras[i];
	}
}
/*Cola::~Cola()
{
	
}*/
bool Cola::Vacia() const
{
	if(nelem==0)
		return true;
	else
		return false;
}
void Cola::Poner(char c)
{
	char aux[500];
	aux[0]=c;
	for(int i=0;i<400;i++){
		aux[i+1]=letras[i];
	}
	for(int i=0;i<400;i++){
		letras[i]=aux[i];
	}
	nelem++;
}
void Cola::Quitar()
{
	nelem--;
}
char Cola::Frente()
{
	return letras[nelem];
}
/*Cola & Cola::operator=(const Cola &c)
{

}*/

























