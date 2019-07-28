
template <class T>
VectorDInamico<T>::VectorDinamico()
{
	datos=0;
	nelementos=0;
}

template <class T>
VectorDinamico<T>::VectorDinamico(const VectorDinamico<T> &V)
{
	if (V.datos!=0)			//Si tiene elementos
	{
		nelementos=V.nelementos;
		datos=new T [nelementos];
		for(int i=0;i<V.nelementos;i++)
		{
			datos[i]=V.datos[i];		
		}
	}else{					//Si no tiene
		datos=0;
		nelementos=0;
	}        
}

template <class T>
VectorDinamico<T>::~VectorDinamico()
{
	delete [] datos;
}

template <class T>
VectorDinamico<T> &VectorDinamico<T>::operator= (const VectorDinamico<T> &V)
{
	if (this != &V)
	{
		delete [] datos;
		if (V.datos!=0)			//Si tiene elementos
		{
			nelementos=V.nelementos;
			datos=new T [nelementos];
			for(int i=0;i<V.nelementos;i++)
			{
				datos[i]=V.datos[i];		
			}
		}else{					//Si no tiene
			datos=0;
			nelementos=0;
		}
	}
	return *this;	
}

template <class T>
void VectorDinamico<T>::resize(int nuevotam)
{
	T aux;
	aux=new T[nuevotam];
	if(nuevotam<nelementos)
	{
		for(int i=0;i<nuevotam;i++)	
			aux[i]=datos[i];
	else{
		for(int i=0;i<nelementos;i++)
		{
			aux[i]=datos[i];
		}
	delete [] datos;
	nelementos=nuevotam;
	datos=aux;
	delete [] aux;
}

template <class T>
void VectorDinamico<T>::poner(T dato)
{
	this.resize(nelementos+1);
	datos[nelementos]=dato;
	nelementos++;
}

template <class T>
int VectorDinamico<T>::size();
{
	return nelementos;
}

template <class T>
const T VectorDinamico<T>::operator[](int pos)
{
	return datos[pos];
}

istream& operator<<(istream &os,VectorDinamico &V)
{
	while(is.good())
	{
		Palabra aux;
		is>>aux;
		T.traduc.push_back(aux);		
	}
	return is;
}
