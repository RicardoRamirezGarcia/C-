#include <stdlib.h>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string>
#include <iostream>
using namespace std;

#define _NUMEROCASOS 1000000
#define _NUMEROVALORES 1000

int progreso = 0;
int n = _NUMEROCASOS;
int incremento = _NUMEROCASOS /_NUMEROVALORES;

//Función para la barra de progreso
void barraProgreso(int i){

	int aux = (((i/incremento)*100)/_NUMEROVALORES)+1;

	if(aux > progreso){
		fprintf(stderr,"%d%%\r",aux);
		progreso = aux;
	}
	else progreso = aux;
	if(progreso == 100) fprintf(stderr,"\n");
}

//Función para sacar el tiempo.
long long mseconds(){
  struct timeval t;
  gettimeofday(&t, NULL);
//Guarda en t los segundos y microsegundos transcurridos desde una fecha fija
//Se pasa todo a microsegundos
  return t.tv_sec*1000000 + t.tv_usec;
}
/*
*La función es consonante devuelve verdadero o falso
*comparando el caracter c que se le pasa por parametro.
*/
bool esConsonante(char c){
	if(('a' == c)||('e' == c)||('i' == c)||('o' == c)||('u' == c)) return false;
	return true;
}

/*
*SE CORRESPONDE CON LA FUNCION ITERATIVA DEL ESQUEMA DEL DIVIDE Y VENCERAS
*La funcion iterativo es la resolución del problema de forma iterativa que  se
*aplica en los casos bases, a esta función se le pasa cadena como parametro y se
*se va recorriendo guardando en una variable string la cadena actual y la cadena
*maxima, la cual se actualiza cada vez que se encuentra una vocal en la secuencia
*consonante - vocal que se va alternado gracias a la variable buscando que indica
si se busca a continuacion una vocal o una consonante.
*/
string iterativo(string cadena){
	//INICIALIZACION DE VARIABLES
	string cadenaActual = "";
	string cadenaMaxima = "";
	int buscando; //BUSCANDO REPRESENTA EL ESTADO. SI ESTÁ A 0 ESTARÁ BUSCANDO CONSONANTE Y SI ESTÁ A 1 ESTARÁ BUSCANDO VOCALES.
	//BUSCA LA PRIMIERA CONSONANTE
	int i = 0;
	while((i < cadena.length())&&(!esConsonante(cadena[i]))) i++;
	if(i < cadena.length()){
		//HA ENCONTRADO LA PRIMERA CONSONANTE Y EMPIEZA EL CICLO PARA BUSCAR LA CADENA  DESESADA.
		buscando = 1; //UNA VEZ QUE SE HA ENCONTRADO LA PRIMERA CONSONANTE SE EMPIEZA A BUSCAR UNA VOCAL.
		cadenaActual = cadena[i];
		for(int j = i+1; j < cadena.length();j++){
			if(buscando == 0){ //SI ESTÁ BUSCANDO CONSONANTE.
				if(esConsonante(cadena[j])){ //SI ES CONSONANTE.
					cadenaActual = cadenaActual + cadena[j];
					buscando = 1;
				} else {
					cadenaActual = "";
				}
			} else { //PARA QUE LEA UNA LETRA EN CADA ITERACION.
				if(buscando == 1){//SI ESTÁ BUSCANDO UNA VOCAL.
					if(!esConsonante(cadena[j])){//SI ES VOCAL.
						cadenaActual = cadenaActual + cadena[j];
						if(cadenaActual.length() > cadenaMaxima.length()) cadenaMaxima = cadenaActual; //SE ACTUALIZA LA CADENA MAXIMA.
						buscando = 0;
					} else {
						cadenaActual = cadena[j];
						buscando = 1;
					}
				}
			}
		}
		//CUANDO ACABA LA ITERACION DEVOLVEMOS EL RESULTADO.
		return cadenaMaxima;
	} else {
		//SI NO HAY CONSONANTES DEVUELVE LA CADENA VACIA.
		return "";
	}
}
/*
*Una sencilla función auxiliar que ayuda a saber si una silaba es vocal - consonante.
*/
bool esVC(string a){
	if((!esConsonante(a[0]))&&(esConsonante(a[1]))) return true;
	return false;
}

/*
*Una sencilla función auxiliar que ayuda a saber si una silaba es consonante - vocal.
*/
bool esCV(string a){
	if((esConsonante(a[0]))&&(!esConsonante(a[1]))) return true;
	return false;
}

/*
*Una sencilla función auxiliar que ayuda a calcular el maximo entre dos cadenas.
*/
string max(string cad1, string cad2){
	if(cad1.size() >= cad2.size()) return cad1;
	return cad2;
}

/*
*Una sencilla función auxiliar que ayuda a calcular el maximo entre tres cadenas.
*/
string max(string cad1, string cad2, string cad3){
	if((cad1.size() >= cad2.size())&&(cad1.size() >= cad3.size())) return cad1;
	if((cad2.size() > cad1.size())&&(cad2.size() > cad3.size())) return cad2;
	return cad3;
}

/*
*SE CORRESPONDE CON LA FUNCION COMBINAR DEL ESQUEMA DEL DIVIDE Y VENCERAS
*esta funcion recibe como parametros cadena, izq y der que son tres cadenas,
*donde cadena es la cadena completa, izq es el maximo obtenido en la parte izquierda
*y der es el maximo obtenido en la parte derecha, se comprueba si se puede formar
*cadena valida en elcentro y una vez comprobado y obtenido la cadena maxima que se
*puede obtener en el centro se comprueba con los maximos de izquierda y derecha para
*saber cual es la más grande, finalmente se devuelve dicho valor.
*/
string combinar(string cadena, string izq, string der){
	string solucionI = "";
	string solucionD = "";
	string cadenaCentral = "";
	cadenaCentral = cadena.substr(((cadena.size()/2)-1),2);
	//CASOS BASE
	if(cadena.size() == 1){
		return "";
	}
	if(cadena.size() == 2){
		if (esCV(cadena)) return cadena;
		else return "";
	}
	if(cadena.size() == 3){
		if(esCV(cadenaCentral)) return cadenaCentral;
		else return der;
	}
	if(cadena.size() == 4){
		if(esCV(cadenaCentral)){
			return cadenaCentral;
		} else {
			return max(izq,der);
		}
	}
	if(cadena.size() == 5){
		if(esCV(cadenaCentral)){
			if(esCV(cadena.substr(3,2))) return cadenaCentral+cadena.substr(3,2);
			else return cadenaCentral;
		}else {
			string auxI = cadena.substr(0,2);
			string auxD = cadena.substr(2,2);
			if(esCV(auxI)&&esCV(auxD)) {
				//LA CADENA FORMADA POR LAS CUATRO LETRAS CENTRALES ES CORRECTA.
				return auxI+auxD;
			} else {
				return max(der,izq);
			}
		}
	}
	if((cadena.size() == 6)||(cadena.size() == 7)){
		if (esCV(cadenaCentral)){
			if(esCV(cadena.substr(4,2))) cadenaCentral = cadenaCentral+cadena.substr(4,2);
			if(esCV(cadena.substr(0,2))) cadenaCentral = cadena.substr(0,2)+cadenaCentral;
			return cadenaCentral;
		}else{
			string auxI = cadena.substr(1,2);
			string auxD = cadena.substr(3,2);
			if(esCV(auxI)&&esCV(auxD)) {
				//LA CADENA FORMADA POR LAS CUATRO LETRAS CENTRALES ES CORRECTA.
				return max(auxI+auxD,der,izq);
			} else {
				return max(der,izq);
			}
		}
	} else {
	  //SE OPTIENE LAS DOS LETRAS CENTRALES PARA POSTERIORMENTE PORDER IDENTIFICAR LOS CASOS.
	  if(esCV(cadenaCentral)){//SI LA CADENA CENTRAL ESTA FORMADA POR UNA VOCAL SEGUIDA DE UNA CONSONANTE.
		  //ITERACION POR LA DERECHA DE LA CADENA HASTA QUE SE ACABE O HASTA QUE NO HAYA UNA COMBINACION VALIDA.
		  //WHILE ...
		  float y = 1;
		  while((y <= cadena.size()-(cadena.size()/2))&&(esCV(cadena.substr(((cadena.size()/2)+y),2)))){
			  solucionD = solucionD + cadena.substr((cadena.size()/2)+y,2);
			  y+=2;
		  }
		  //ITERACION POR LA IZQUIERDA DE LA CADENA HASTA QUE SE ACABE O HASTA QUE NO HAYA UNA COMBINACION VALIDA.
		  //wHILE ...
		  float z = 1;
		  while((((cadena.size()/2)-z-2) >= 0)&&(esCV(cadena.substr((cadena.size()/2)-z-2,2)))){
			  solucionI = cadena.substr((cadena.size()/2)-z-2,2) + solucionI;
			  z+=2;
		  }
		  return max(solucionI+cadenaCentral+solucionD,der,izq);
	  } else {
		  if (esVC(cadenaCentral)){//SI LA CADENA CENTRAL ESTA FORMADA POR UNA CONSONANTE SEGUIDA DE UNA VOCAL.
			  //ENCONTRAR LA SIGUIENTE LETRA POR LA IZQUIERDA PARA VER SI SE PUEDE ACOPLAR AL PRINCIPIO DE LA CADENA CENTRAL.
			  string auxI = cadena.substr(((cadena.size()/2)-2),2);
			  //ENCONTRAR LA SIGUIENTE LETRA POR LA DERECHA PARA VER SI SE PUEDE ACOPLAR POR EL FINAL DE LA CADENA.
			  string auxD = cadena.substr(((cadena.size()/2)),2);
			  //COMPROBAR SI SE PUEDEN AÑADIR LAS DOS CADENAS A LA CADENA CENTRAL, UNA POR DELANTE Y OTRA POR DETRAS.

			  if(esCV(auxI)&&esCV(auxD)) {
				  //LA CADENA FORMADA POR LAS CUATRO LETRAS CENTRALES ES CORRECTA.
				  cadenaCentral = auxI+auxD;
			  }
			  else {
				  return max(der,izq);
			  }
			  //ITERACION POR LA DERECHA DE LA CADENA HASTA QUE SE ACABE O HASTA QUE NO HAYA UNA COMBINACION VALIDA.
			  //WHILE ...
			  float y = 2;
			  while((y <= cadena.size()-(cadena.size()/2))&&(esCV(cadena.substr(((cadena.size()/2)+y),2)))){
				  solucionD = solucionD + cadena.substr(((cadena.size()/2)+y),2);
				  y+=2;
			  }
			  //ITERACION POR LA IZQUIERDA DE LA CADENA HASTA QUE SE ACABE O HASTA QUE NO HAYA UNA COMBINACION VALIDA.
			  //wHILE ...
			  float z = 2;
			  while((((cadena.size()/2)-z-2) >= 0)&&(esCV(cadena.substr((cadena.size()/2)-z-2,2)))){
				  solucionI = cadena.substr((cadena.size()/2)-z-2,2) + solucionI;
				  z+=2;
			  }
			  return max(solucionI+cadenaCentral+solucionD,der,izq);
		  }
	  }
	  return max(der,izq);
  }
}

/////////////////////////////////////////////////////////////
////////////        FUNCION RECURSIVA        ////////////////
/////////////////////////////////////////////////////////////
/*
*SE CORRESPONDE CON LA FUNCION RECURSIVA DEL ESQUEMA DE DIVIDE Y VENCERAS
*La funcion comprueba si la cadena es menor o igual que el caso base, si lo es
*simplemente se limita a llamar a la funcion iterativa para solucionar el caso base,
*si no entonces llama a la funcion combinar con la cadena que se le pasa como parametro
*, el maximo del lado derecho que se calcula con la llamada recursiva con la mitad derecha
*de la cadena y lo mismo para la parte izquierda, el resultado final es lo que devuelve la función combinar.
*/
string maxConsVocal(string cadena,int n){
	if(n <= 5){
		return iterativo(cadena);
	}
	string cad1 = cadena.substr(0,n/2);
	string cad2 = cadena.substr(n/2,n-(n/2));
	return combinar(cadena,maxConsVocal(cad1,(n/2)),maxConsVocal(cad2,(n-(n/2))));
}
/*
*Con esta funcion podemos generar automaticamente cadenas muy grandes e incluso
*podemos variar la probabilidad de que salgan vocales para que se den mas o menos casos.
*/
string generarCadena(int n){
	string solucion;
	int num,prob;
	char c;
	string vocales = "aeiou";
	for(int i = 0; i < n; i++){
		prob=1+rand()%(10-1);
		if(prob > 10){
			num = rand()%5;
			solucion += vocales[num];
		}
		else {
			//generar numero aleatorio entre 97 - 122 (rango de minusculas)
			num=97+rand()%(122-97);
			//combertir el numero a char
			c = (char)num;
			//añadir el caracter a la cadena
			solucion += c;
		}
	}
	return solucion;
}

//////////////////////////////////////////////////////////////
////////////        PROGRAMA PRINCIPAL        ////////////////
//////////////////////////////////////////////////////////////

int main (void)
{
	srand(time(NULL));
	//Variables.
	int m,base;
	long long int val;
	base = 0;
	long long int tiempoIni,tiempoFin;
	long long contador = 0;
	////////////////////////

  //Se pintan los indices.
  printf("n\t");
  for(int i = 1;i <= n; i+=incremento) printf("%d\t",i);
    printf("\nTiempo\t");
  /////////////////////////
   fprintf(stderr,"Se van a genererar %d datos\n", _NUMEROCASOS);

  for(int i = 1; i <= n; i+=incremento){
			contador = 0;
			///////////////////////////////////////////////////

			string cadena = generarCadena(i);
			//cerr << "La cadena es " << i << endl;
			//cerr << "Cadena final (iterativa): " << iterativo(cadena) << endl;
			//cerr << "Cadena final (recursivo): " << maxConsVocal(cadena,cadena.length()) << endl;
			for(int j = 0; j < 10; j++){
				tiempoIni = mseconds();
				maxConsVocal(cadena,cadena.length());
				tiempoFin = mseconds();
				contador+=(tiempoFin-tiempoIni);
			}

	///////////////////////////////////////////////////
	/*

          barraProgreso(i);
          val=(tiempoFin-tiempoIni);
          /*
          if(val<0){
            fprintf(stderr, "error\n");
          }
*/

    //fprintf(stderr,"EL TIEMPO PARA %d CASOS ES: %lld %lld %lld\n",i, tiempoIni, tiempoFin, contador/10);
		printf("%lld\t",contador/10);
		barraProgreso(i);
	}
/*

	 */



}
