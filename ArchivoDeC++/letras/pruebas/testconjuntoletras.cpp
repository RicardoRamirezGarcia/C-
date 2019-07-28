#include <fstream>
#include <iostream>
#include "ConjuntoLetras.h"

using namespace std;

int main(int argc, char * argv[])
{
    if (argc!=2)
    {
        cout<<"Nombre de fichero de letras "<<endl;
        return 0;
    }

    ifstream f (argv[1]);
    if (!f)
    {
        cout<<"No puedo abrir el fichero "<<argv[1]<<endl;
        return 0;
    }

    ConjuntoLetras conjunto;

    cout << "Leyendo letras" << endl;
    f >> conjunto; //Cargamos en memoria.


    cout << "Escribiendo letras" << endl;
    cout << conjunto;

    return 0;

}