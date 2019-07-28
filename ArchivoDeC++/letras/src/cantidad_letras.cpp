#include <fstream>
#include <iostream>
#include "Diccionario.h"
#include "ConjuntoLetras.h"

using namespace std;

int main(int argc, char * argv[])
{
    if (argc!=4)
    {
        cout<<"Nombre del diccionario "		<< endl;
        cout<<"Nombre de fichero de letras "<< endl;
        cout<<"Nombre de fichero de salida "<< endl;
        return 1;
    }

    ifstream fichero_dicccionario (argv[1]);

    if (!fichero_dicccionario)
    {
        cout << "No puedo abrir el fichero " << argv[1] << endl;
        return 1;
    }

    ifstream fichero_letras (argv[2]);

    if (!fichero_letras)
    {
        cout << "No puedo abrir el fichero " << argv[2] << endl;
        return 1;
    }

    ofstream fichero_salida (argv[3]);

    if (!fichero_salida)
    {
        cout << "No puedo crear el fichero " << argv[3] << endl;
        return 1;
    } 

    //Cabecera del archivo
    fichero_salida << "#Letra\tCantidad\tPuntos" << endl;

    //Cargar el diccionario
    Diccionario diccionario;
    fichero_dicccionario >> diccionario;

    //Cargar las letras en memoria
    ConjuntoLetras conjunto_letras;
    fichero_letras >> conjunto_letras;

    //Para cada letra en el conjunto
    for (int i=0; i<conjunto_letras.size(); i++)
    {
        Letra l = conjunto_letras[i];
        //Obtenemos las veces que aparece
        int apariciones = diccionario.getApariciones(*l);
		//Y obtenemos el numero de puntos
        int puntos = l.getPuntos();

        //Pintamos la salida
        fichero_salida << *l << '\t' << apariciones << '\t' << puntos << endl;
    }

    //Cerramos el archivo
    fichero_salida.close();

    return 0;
}





