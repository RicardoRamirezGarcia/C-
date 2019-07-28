#include "matriz.h"

void sumarMatriz(Matriz &res,const Matriz &m1,const Matriz &m2){
	for(int i=0;i<filasMatriz(res),++i)
		for(int j=0;j<columnasMatriz(res),++j)
			setMatriz(res,i,j,getMatriz(m1,i,j)+getMatriz(m2,i,j));
}

void restarMatriz(Matriz &res,const Matriz &m1,const Matriz &m2){
	for(int i=0;i<filasMatriz(res);++i)
		for(int j=0;j<columnasMatriz(res);++j)
			setMatriz(res,i,j,getMatriz(m1,i,j)-getMatriz(m2,i,j));
}

void leerMatriz(Matriz &m){
	double dato;
	for(int i=0;i<filasMatriz(m);++i)
		for(int j=0;j<columnasMatriz(m);++j){
			cout<< "Elemento ("<<i<<","<<j<<") : ";
			cin>> dato;
			setMatriz(m,i,j,dato);
		}
}

void escribirMatriz(Matriz &m){
	double dato;
	for(int i=0;i<filasMatriz(m);++i)
		for(int j=0;j<columnasMatriz(m);++j){
			dato=getMatriz(m,i,j);
			cout<< setw(8) << dato << " " ;
		}
	cout <<endl;
}