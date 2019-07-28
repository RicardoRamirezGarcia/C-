#define CUAL_COMPILA 3

#if CUAL_COMPILA==1
	#include <pila_max_vd.h>
#elif CUAL_COMPILA==2
	#include <pila_max_lista.h>
#else
	#include <pila_max_cola.h>
#endif
