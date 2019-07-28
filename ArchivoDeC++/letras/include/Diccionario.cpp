//---------------------------------------------------------------
//CONSTRUCTOR
//---------------------------------------------------------------
Diccionario::Diccionario()
{
	//Creamos el nodo raiz y le ponemos un valor 
	info nodo_raiz('*', false);
	datos = ArbolGeneral<info>(nodo_raiz);
}
//---------------------------------------------------------------
//DEVULVE EL NUMERO DE APARICIONES DE 'c'
//---------------------------------------------------------------
int Diccionario::getApariciones(const char c)
{
	int apariciones = 0;
	//Recorremos el arbol
	for (ArbolGeneral<info>::iter_preorden it = datos.begin(); it!=datos.end(); ++it)
	{
		char c_tree = (*it).c; //Caracter actual del arbol
		if (c_tree == tolower(c))	//Si se encuentra el valor
			apariciones++;
	}
	return apariciones;
}
//---------------------------------------------------------------
//DEVUELVE UN VECTOR CON LAS PALABRAS DE LONGITUD 'longitud'
//---------------------------------------------------------------
vector<string> Diccionario::PalabrasLongitud(int longitud)
{
	vector<string> palabras;
	for (iterator it_dic = begin(); it_dic != end(); ++it_dic)
	{
		if ((*it_dic).size() == longitud)
			palabras.push_back(*it_dic);
	}
	return palabras;
}
//---------------------------------------------------------------
//DEVULVE SI 'palabra' ESTA EN EL DICCIONARIO
//---------------------------------------------------------------
bool Diccionario::Esta(string palabra)
{
	for (iterator it_dic = begin(); it_dic != end(); ++it_dic)
	{
		string cad = *it_dic;
		if (palabra == cad)
			return true;
	}
	return false;
}
//---------------------------------------------------------------
//INSERTA UNA CADENA
//---------------------------------------------------------------
void Diccionario::insertar_cadena( string palabra, int i, ArbolGeneral<info>::Nodo n)
{
	ArbolGeneral<info>::Nodo p,nuevo_nodo;
	info x;

	if (i == palabra.size()) // Si es la siguiente a la última letra 
	{
		datos.etiqueta(n).final = true;
	}
	else
	{
		bool salir = false;
		p= datos.hijomasizquierda(n);
		while ( p!=0 && !salir)
		{
			x = datos.etiqueta(p);
			if (x.c == palabra[i])
				salir = true;
			else
				p=datos.hermanoderecha(p);
		}
		if (salir)
			insertar_cadena(palabra,++i,p);
		else
		{
			char letra = palabra[i];
			// Realmente no es necesario, ya que se re-marca al final de la palabra
			bool ultima = (i == palabra.size() - 1);

			// Creamos un nuevo info (letra)
			x = info(letra, ultima);

			// Creamos un nuevo arbol con el nodo nuevo
			ArbolGeneral<info> aux(x);

			// Lo insertamos
			datos.insertar_hijomasizquierda(n, aux);

			// Obtenemos el nodo recien insertado
			nuevo_nodo = datos.hijomasizquierda(n);

			insertar_cadena(palabra,++i,nuevo_nodo);
		}
	}
}
//---------------------------------------------------------------
//OPERADOR DE ENTRADA
//---------------------------------------------------------------
istream& operator>> (istream & is,Diccionario &D)
{
	string palabra;
	while (getline(is, palabra))
	{
		D.insertar_cadena(palabra,0, D.datos.raiz());
	}
	return is;
}
//---------------------------------------------------------------
//OPERADOR DE SALIDA
//---------------------------------------------------------------
ostream & operator<<(ostream & os, Diccionario &D)
{
	Diccionario::iterator it = D.begin();
	for (; it!=D.end(); ++it)
	{
		os << (*it) << endl;
	}
	return os;
}
//---------------------------------------------------------------
//ITERADOR
//---------------------------------------------------------------
Diccionario::iterator::iterator()
{
	arbol = ArbolGeneral<info>();
	it = arbol.end();
	cad = "";  //mantiene los caracteres desde el nivel 1 hasta donde se encuentra it.
	level = 0;
}

Diccionario::iterator::iterator(Diccionario dic)
{
	arbol = dic.datos;
	it =  arbol.begin();
	cad = "";
	level = 0;
}

string Diccionario::iterator::operator*()
{
	return cad;
}

Diccionario::iterator & Diccionario::iterator::operator ++()
{

	if ((*it).final)
	{
		++it;

		int level_actual = it.getlevel();

		// Si el nivel es 0 es que estamos al final del arbol (ha vuelto a a la raiz)
		if (level_actual == 0)
		{
			// ...ponemos el iterador en situacion de .end()
			arbol = ArbolGeneral<info>();
			it = arbol.begin();
			cad = "";  //mantiene los caracteres desde el nivel 1 hasta donde se encuentra it.
			level = 0;

			return *this;
		}

		if (level_actual > level)
		{
			cad.push_back((*it).c);
			level++;
		}
		else if (level_actual <= level)
		{

			int diff =  level - level_actual;

			// Si da un numero negativo es porque estamos en el final del arbol
			int caracteres_a_borrar = cad.size() - diff -1;

			cad.erase(caracteres_a_borrar);

			cad.push_back((*it).c);

			level = level_actual;

		}

	}

	while (!(*it).final)
	{
		++it;

		int level_actual = it.getlevel();

		if (level_actual > level)
		{
			cad.push_back((*it).c);
			level++;
		}

	} 

	return *this;
}

bool Diccionario::iterator::operator ==(const Diccionario::iterator &i)
{
	return it == i.it;
}

bool Diccionario::iterator::operator !=(const Diccionario::iterator &i)
{
	return it != i.it;
}


ostream & Diccionario::iterator::operator<<(ostream & os)
{
	os << cad;
	return os;
}

Diccionario::iterator Diccionario::begin()
{
	return iterator(*this);
}

Diccionario::iterator Diccionario::end()
{
	return iterator();
}