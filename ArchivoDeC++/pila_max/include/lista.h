#ifndef _LISTA_H_
# define _LISTA_H_

template <class T>
struct CeldaLista
{
	T elemento;
	CeldaLista ∗siguiente;
};

template <class T>
class Lista
{
		CeldaLista ∗cab;
		CeldaLista ∗ultima; // Para end()
	public:
		class Posicion 
		{
				CeldaLista ∗puntero;
				CeldaLista ∗primera; // para operator–
			public:
				Posicion(): puntero(0),primera(0) {}
				//Posicion(const Posicion& p);
				∼Posicion():{
					delete puntero;
					delete primera;
				}
				//Posicion& operator= (const Posicion& p);
				Posicion& operator++() 
				{
					puntero= puntero→siguiente;
					return ∗this;
				}
				Posicion& operator--();
				bool operator==(const Posicion& p)
					{ return puntero==p.puntero; }
				bool operator! =(const Posicion& p)
					{ return puntero! =p.puntero; }
				friend class Lista;
		};
		Lista() {
			ultima= cab= new CeldaLista;
			cab→siguiente= 0;
		}
		Lista(const Lista<T> &l);
		∼Lista();
		Lista<T> & operator= (const Lista<T>& l);
		void set (Posicion p, Tbase e) {
			p.puntero→siguiente→elemento= e;
		}
		Tbase get (Posicion p) const {
			return p.puntero→siguiente→elemento;
		}
		Posicion insertar(Posicion p, Tbase e);
		Posicion borrar(Posicion p);
		Posicion begin() const {
			Posicion p;
			p.puntero= p.primera= cab;
			return p;
		}
		Posicion end() const {
			Posicion p; p.puntero= ultima; p.primera= cab;
			return p;
		}
};