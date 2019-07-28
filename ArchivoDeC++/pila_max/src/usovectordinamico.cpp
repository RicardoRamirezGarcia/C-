#include <iostream>
#include "vectordinamico.h"

using namespace std;


int main(){
	
  VectorDinamico <int> v;
  int i;

  for ( i=0; i<10 ; i++) 
    v.poner(i);
  
	for(int j=0;j<i;j++)
		cout << v[j] << endl;
	
  VectorDinamico <float> w;
  int z;
  
  for ( z=0; z<10 ; z++) 
    w.poner(z/10.0);
  
	for(int j=0;j<i;j++)
	{ 
		cout << w[j] << endl;
	}

  return 0;
}