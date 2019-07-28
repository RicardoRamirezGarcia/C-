
struct Matriz{
	double **datos;
	int filas,columnas;
};

void crearMatriz(Matriz &m,int f,int c){
	m.datos=new double *[f];
	for(int i=0;i<f;i++)
		m.datos[i]=new double [c];
	m.filas=f;
	m.columnas=c;
}

int filasMatriz(const Matriz &m){
	return m.filas;
}

int columnasMatriz(const Matriz &m){
	return m.columnas;
}

void setMatriz(Matriz &m,int f,int c,double v){
	m.datos[f][c]=v;
}

float getMatriz(const Matriz &m,int f,int c){
	return m.datos[f][c];   
}

void destruirMatriz(const Matriz &m){
	for(int i=0;i<m.filas;i++)
		delete[] m.datos[i];
	delete[] m.datos;
}




































