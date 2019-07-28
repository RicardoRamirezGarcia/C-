//---------------------------------------------------------------
//               FUNCIONES PRIVADAS
//---------------------------------------------------------------
//DESTRUIR
//---------------------------------------------------------------
template <class T>
void ArbolGeneral<T>::destruir(nodo * n)
{
	if (n!=0){
		destruir(n->izqda);
		destruir(n->drcha);
		delete n;
	}
}
//----------------------------------------------------------------
//COPIAR
//----------------------------------------------------------------
template <class T>
void ArbolGeneral<T>::copiar(nodo * & dest, nodo * orig)
{
	if (orig == 0)
		dest = 0;
	else
	{
		//Si el nodo no es nulo
		dest = new nodo;
		dest->etiqueta = orig->etiqueta;
		dest->padre = orig->padre;
		dest->izqda = orig->izqda;
		dest->drcha = orig->drcha;

		copiar(dest->izqda, orig->izqda);
		copiar(dest->drcha, orig->drcha);
	}
}
//----------------------------------------------------------------
//CONTAR
//----------------------------------------------------------------
template <class T>
int ArbolGeneral<T>::contar(const nodo * n) const
{
	if (n==0)
		return 0;
	else
		return 1+contar(n->izqda)+contar(n->drcha);
}
//---------------------------------------------------------------
//SONIGUALES
//---------------------------------------------------------------
template <class T>
bool ArbolGeneral<T>::soniguales(const nodo * n1, const nodo * n2) const
{
	if (n1==0 && n2==0)
		return true;
	else if (n1==0 || n2==0)
		return false;
	else if (n1->etiqueta!=n2->etiqueta)
		return false;
	else if (!soniguales(n1->izqda,n2->izqda))
		return false;
	else if (!soniguales(n1->drcha,n2->drcha))
		return false;
	else
		return true;
}
//---------------------------------------------------------------
//LEE ARBOL
//---------------------------------------------------------------
template <class T>
void ArbolGeneral <T>::lee_arbol(std::istream& in, nodo * & nod){
	char c;
	in >> c;                     //Lectura de un carácter
	if (c=='n'){                 //Si es 'n'
		nod= new nodo;
		in >> nod->etiqueta;
		lee_arbol(in,nod->izqda);
		lee_arbol(in,nod->drcha);
		if (nod->izqda!=0)
			nod->izqda->padre=nod;
		if (nod->drcha!=0)
			nod->drcha->padre=nod;
	}
	else nod= 0;                 //Si no es 'n' hay un error en la entrada
								 //o no hay más caracteres que leer,
							     //y devolvemos un árbol nulo
}
//---------------------------------------------------------------
//ESCRIBE ARBOL
//---------------------------------------------------------------
template <class T>
void ArbolGeneral<T>::escribe_arbol(std::ostream& out, nodo * nod) const{
	if (nod==0)
		out << "x ";
	else {
		out << "n "<< nod->etiqueta << " ";
		escribe_arbol(out,nod->izqda);
		escribe_arbol(out,nod->drcha);
	}
}

//-----------------------------------------------------------------
//               FUNCIONES PUBLICAS
//-----------------------------------------------------------------
//CONSTRUCTOR
//-----------------------------------------------------------------
template <class T>
inline ArbolGeneral<T>::ArbolGeneral(){
	laraiz = 0;  //El constructor por defecto crea un árbol vacío
}
//---------------------------------------------------------------
//CONSTRUCTOR CON PARAMETRO  (crea un nodo raiz que solo tiene valor en el campo etiqueta)
//---------------------------------------------------------------
template <class T>
ArbolGeneral<T>::ArbolGeneral(const T& e)
{
	laraiz = new nodo;
	laraiz->padre =
	laraiz->izqda =
	laraiz->drcha = 0;
	laraiz->etiqueta = e;
}
//---------------------------------------------------------------
//CONSTRUCTOR DE COPIA
//---------------------------------------------------------------
template <class T>
ArbolGeneral<T>::ArbolGeneral (const ArbolGeneral<T>& v)
{
	copiar (laraiz,v.laraiz); //Llamamos a copiar desde la raíz
	if (laraiz!=0)            //Si no es el árbol vacío
		laraiz->padre= 0;     //actualizamos el padre
}
//---------------------------------------------------------------
//DESTRUCTOR
//---------------------------------------------------------------
template <class T>
inline ArbolGeneral<T>::~ArbolGeneral(){
	destruir(laraiz);  //Destruye llamando a destruir desde la raíz
}
//---------------------------------------------------------------
//OPERADOR DE ASIGNACION
//---------------------------------------------------------------
template <class T>
ArbolGeneral<T> &
ArbolGeneral<T>::operator = (const ArbolGeneral<T>&v){
	if (this!=&v){
		destruir(laraiz);         //destructor
		copiar (laraiz,v.laraiz); //constructor de copia
		if (laraiz!=0)
			laraiz->padre= 0;
	}
	return *this;
}
//---------------------------------------------------------------
//ASIGNA UNA ETIQUETA A UN NODO
//---------------------------------------------------------------
template <class T>
void ArbolGeneral<T>::AsignaRaiz(const T& e){
	destruir(laraiz);
	laraiz = new nodo;
	laraiz->padre =
	laraiz->izqda =
	laraiz->drcha = 0;
	laraiz->etiqueta= e;
}
//---------------------------------------------------------------
//DEVULVE EL NODO RAIZ
//---------------------------------------------------------------
template <class T>
inline typename ArbolGeneral<T>::Nodo
ArbolGeneral<T>::raiz() const{
	return laraiz;
}
//---------------------------------------------------------------
//DEVULVE EL HIJO MAS A LA IZQUIERDA DE UN NODO
//---------------------------------------------------------------
template <class T>
inline typename ArbolGeneral<T>::Nodo
ArbolGeneral<T>::hijomasizquierda(const Nodo p) const{
	assert(p!=0);
	return (p->izqda);
}
//---------------------------------------------------------------
//DEVULVE EL HERANO DE LA DERECHA DE UN NODO
//---------------------------------------------------------------
template <class T>
typename ArbolGeneral<T>::Nodo ArbolGeneral<T>::hermanoderecha(const Nodo p) const{
	assert(p!=0);
	return (p->drcha);
}
//---------------------------------------------------------------
//DEVUELVE EL NODO PADRE DE UN NODO
//---------------------------------------------------------------
template <class T>
typename ArbolGeneral<T>::Nodo ArbolGeneral<T>::padre(const Nodo p) const{
	assert(p!=0);
	return (p->padre);
}
//--------------------------------------------------------------
//DEVULVEN LA ETIQUETA DE UN NODO
//---------------------------------------------------------------
template <class T>
T& ArbolGeneral<T>::etiqueta(const Nodo p){
	assert(p!=0);
	return (p->etiqueta);
}
//---------------------------------------------------------------
template <class T>
const T& ArbolGeneral<T>::etiqueta(const Nodo p) const{
	assert(p!=0);
	return (p->etiqueta);
}
//---------------------------------------------------------------
//COPIA EL SUBARBOL COLGANTE DE NOD EN LA RAIZ
//---------------------------------------------------------------
template <class T>
void ArbolGeneral<T>::asignar_subarbol(const ArbolGeneral<T>& orig,
 const Nodo nod){
	destruir(laraiz);
	copiar(laraiz,nod);
	if (laraiz!=0)
		laraiz->padre=0;
}
//---------------------------------------------------------------
//PODA EL HIJO IZQ DE UN NODO
//---------------------------------------------------------------
template <class T>
void ArbolGeneral<T>::podar_hijomasizquierda(Nodo n, ArbolGeneral<T>& dest){
	assert(n!=0);
	Nodo *res = 0;
	if (n->izqda!=0)
	{
		res= n->izqda;
		n->izqda = res->drcha;
		res->padre = res->drcha = 0;
	}
}
//---------------------------------------------------------------
//PODA EL HERMANO DERECHA DE UN NODO
//---------------------------------------------------------------
template <class T>
void ArbolGeneral<T>::podar_hermanoderecha(Nodo n, ArbolGeneral<T>& dest){
	assert(n!=0);
	destruir(dest.laraiz);    //Destruimos el árbol destino
	dest.laraiz=n->drcha;     //Copia el hijo derecha de n en la raíz de dest
	if (dest.laraiz!=0) {     //Si el subárbol copiado no es vacío,
		dest.laraiz->padre=0; //actualizamos el padre
		n->drcha=0;           //y actualizamos el hijo a la derecha
	}
}
//---------------------------------------------------------------
//INSERTA UN HIJO A LA IZQUIERDA
//---------------------------------------------------------------
template <class T>
void ArbolGeneral<T>::insertar_hijomasizquierda(Nodo n, ArbolGeneral<T>& rama)
{
	assert(n!=0);
	if (!rama.empty())
	{
		rama.laraiz->drcha = n->izqda;
		rama.laraiz->padre = n;
		n->izqda = rama.laraiz;
		rama.laraiz=0;
	}
}
//---------------------------------------------------------------
//INSERTA HERMANO DERECHA A UN NODO
//---------------------------------------------------------------
template <class T>
void ArbolGeneral<T>::insertar_hermanoderecha(Nodo n, ArbolGeneral<T>& rama){
	assert(n!=0);
	if (!rama.empty())
	{
		rama.laraiz->drcha = n->drcha;
		rama.laraiz->padre = n->padre;
		n->drcha = rama.laraiz;
		rama.laraiz=0;
	}
}
//---------------------------------------------------------------
//DESTRUIR EL ARBOL
//---------------------------------------------------------------
template <class T>
void ArbolGeneral<T>::clear(){
	destruir(laraiz);
	laraiz= 0;
}
//---------------------------------------------------------------
//DEVUELVE EL NUMERO DE NODOS DEL ARBOL
//---------------------------------------------------------------
template <class T>
inline int ArbolGeneral<T>::size() const{
	return contar(laraiz);
}
//---------------------------------------------------------------
//DEVUELVE SI EL ARBOL ESTA VACIO
//---------------------------------------------------------------
template <class T>
inline bool ArbolGeneral<T>::empty() const{
	return (laraiz==0);
}
//---------------------------------------------------------------
//OPERADOR DE IGUALDAD
//---------------------------------------------------------------
template <class T>
inline bool ArbolGeneral<T>::operator==(const ArbolGeneral<T>& v) const{
	return soniguales(laraiz,v.laraiz);
}
//---------------------------------------------------------------
//OPERADOR ED DESIGUALDAD
//---------------------------------------------------------------
template <class T>
inline bool ArbolGeneral<T>::operator!=(const ArbolGeneral<T>& v) const{
	return !(*this==v);
}
//---------------------------------------------------------------
//OPERADOR DE ENTRADA
//---------------------------------------------------------------
template <class T>
inline istream& operator>> (istream& in, ArbolGeneral<T>& v){
	v.lee_arbol(in,v.laraiz);
	return in;
}
//---------------------------------------------------------------
//OPERADOR DE SALIDA
//---------------------------------------------------------------
template <class T>
inline ostream& operator<< (ostream& out, const ArbolGeneral<T>& v){
	v.escribe_arbol(out,v.laraiz);
	return out;
}
//--------------------------------------------------------------
//ITERADOR ITER_PREORDEN
//---------------------------------------------------------------
template<class T>
ArbolGeneral<T>::iter_preorden::iter_preorden()
{
	it = typename ArbolGeneral<T>::Nodo();
	raiz = it;
	level = 0;
}
template <class T>
ArbolGeneral<T>::iter_preorden::iter_preorden(const ArbolGeneral<T>::iter_preorden & i) : it(i.it), raiz(i.it), level(i.level) {}

template <class T>
ArbolGeneral<T>::iter_preorden::iter_preorden(ArbolGeneral<T>::Nodo n) : it(n), level(0) {}

template<class T>
T & ArbolGeneral<T>::iter_preorden::operator*()
{
	return (*it).etiqueta;
}

template<class T>
typename ArbolGeneral<T>::Nodo & ArbolGeneral<T>::iter_preorden::operator&()
{
	return it;
}

template<class T>
int ArbolGeneral<T>::iter_preorden::getlevel() const
{
	return level;
}

template<class T>
typename ArbolGeneral<T>::iter_preorden & ArbolGeneral<T>::iter_preorden::operator ++()
{
	if (it==0)
		return *this;

	if (it->izqda != 0)
	{
		it = it->izqda;
		level++; // Incrementamos el nivel
	}
	else if (it->drcha != 0)
	{
		it = it->drcha;
	}
	else
	{

		while ( (it->padre != 0) && (it->padre->drcha == it || it->padre->drcha == 0))
		{
			it = it->padre;
			level--; // Decrementamos el nivel
		}

		if (it->padre == 0)
			it = typename ArbolGeneral<T>::Nodo();
		else
		{
			it = it->padre->drcha;
			level--; // Decrementamos el nivel
		}

	}

	return *this;
}

template<class T>
bool ArbolGeneral<T>::iter_preorden::operator == (const iter_preorden &i)
{
	return it == i.it;
}

template<class T>
bool ArbolGeneral<T>::iter_preorden::operator != (const iter_preorden &i)
{
	return it != i.it;
}

template<class T>
typename ArbolGeneral<T>::iter_preorden ArbolGeneral<T>::begin()
{
	return iter_preorden(laraiz);
}

template<class T>
typename ArbolGeneral<T>::iter_preorden ArbolGeneral<T>::end()
{
	return iter_preorden(typename ArbolGeneral<T>::Nodo());
}
// --------------------------------------------------------------
//ITERADOR CONST_ITER_PREORDEN
//---------------------------------------------------------------
template<class T>
ArbolGeneral<T>::const_iter_preorden::const_iter_preorden()
{
	it = typename ArbolGeneral<T>::Nodo();
	raiz = it;
	level = 0;
}

template <class T>
ArbolGeneral<T>::const_iter_preorden::const_iter_preorden(const ArbolGeneral<T>::const_iter_preorden & i) : it(i.it), raiz(i.it), level(0) {}

template <class T>
ArbolGeneral<T>::const_iter_preorden::const_iter_preorden(ArbolGeneral<T>::Nodo n) : it(n) {}

template<class T>
const T & ArbolGeneral<T>::const_iter_preorden::operator*()
{
	return *it;
}

template<class T>
int ArbolGeneral<T>::const_iter_preorden::getlevel() const
{
	return level;
}

template<class T>
typename ArbolGeneral<T>::const_iter_preorden & ArbolGeneral<T>::const_iter_preorden::operator ++()
{
	if (it==0)
		return *this;

	if (it->izqda != 0)
	{
		it = it->izqda;
		level++; // Incrementamos el nivel
	}
	else if (it->drcha != 0)
	{
		it = it->drcha;
	}
	else
	{

		while ( (it->padre != 0) && (it->padre->drcha == it || it->padre->drcha == 0))
		{
			it = it->padre;
			level--; // Decrementamos el nivel
		}

		if (it->padre == 0)
			it = typename ArbolGeneral<T>::Nodo();
		else
		{
			it = it->padre->drcha;
			level--; // Decrementamos el nivel
		}

	}

	return *this;
}

template<class T>
bool ArbolGeneral<T>::const_iter_preorden::operator == (const const_iter_preorden &i)
{
	return it == i.it;
}

template<class T>
bool ArbolGeneral<T>::const_iter_preorden::operator != (const const_iter_preorden &i)
{
	return it != i.it;
}

template<class T>
typename ArbolGeneral<T>::const_iter_preorden ArbolGeneral<T>::begin() const
{
	return const_iter_preorden(laraiz);
}

template<class T>
typename ArbolGeneral<T>::const_iter_preorden ArbolGeneral<T>::end() const
{
	return const_iter_preorden(typename ArbolGeneral<T>::Nodo());
}








