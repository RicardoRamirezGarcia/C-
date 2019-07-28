#include <fstream>
#include <iostream>
#include <cstdlib>  
#include <ctime>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#include "Diccionario.h"
#include "ConjuntoLetras.h"
#include "BolsaLetras.h"
#include "Resultado.h"

using namespace std;

int main(int argc, char * argv[])
{
	if (argc!=5)
	{
		cout<<"Nombre del diccionario "<<endl;
		cout<<"Nombre de fichero de letras "<<endl;
		cout<<"Numero de letras a generar "<<endl;
		cout<<"Modo de juego (L: palabras mas larga, P: mayor puntuacion)"<<endl;
		return 1;
	}

	ifstream fichero_dicccionario (argv[1]);
	if (!fichero_dicccionario)
	{
		cout<<"No puedo abrir el fichero "<< argv[1] << endl;
		return 1;
	}

	ifstream fichero_letras (argv[2]);
	if (!fichero_letras)
	{
		cout<<"No puedo abrir el fichero "<< argv[2] << endl;
		return 1;
	}

	//Cargamos las palabras en el diccionario
	Diccionario diccionario;
	fichero_dicccionario >> diccionario;

	//Cargamos las letras en memoria
	ConjuntoLetras conjunto_letras;
	fichero_letras >> conjunto_letras;

	//Llenamos la bolsa de letras con las repeticiones
	BolsaLetras bolsa_letras;
	conjunto_letras >> bolsa_letras;

	//Numero de letras con las que jugaremos:
	int numero_letras = atoi(argv[3]);

	char type;
	do
	{
		cout << "Las letras son:\t" << endl;
		srand(time(0));            				  
		vector<Letra> letras;

		for (int i=0; i<numero_letras; i++)
		{
			int rnd = rand() % bolsa_letras.size(); 

			Letra l = bolsa_letras[rnd];

			cout << *l << '\t';

			letras.push_back(l);
		}

		string palabra;
		for (int i=0; i<letras.size(); i++)
		{
			Letra l = letras[i];
			palabra.push_back(tolower(*l));
		}

		bool fallo = false; 
		string solucion_usuario;
		do
		{
			fallo = false;

			cout << "Dime tu solucion:";
			cin >> solucion_usuario;
			if (solucion_usuario.size() > numero_letras)
			{
				cout <<"La palabra introducida es mayor a la cantidad de letras proporcionadas" << endl;
				fallo = true;
			}
			else
			{
				for (int i=0; !fallo && i<solucion_usuario.size(); i++)
				{
					char letra = solucion_usuario[i];
					// Comprobamos si la letra no está
					if (palabra.find(letra) == string::npos)
					{
						cout <<"Has usado letras fuera de la secuencia"<< endl;
						fallo = true;
					}
				}
			}

		} while (fallo);

		//Comprobamos si la palabra introducida existe
		if (!diccionario.Esta(solucion_usuario))
			cout <<"La palabra introducida no existe" << endl;
		else
			cout << solucion_usuario << "\tPuntuacion: " << conjunto_letras.puntuacion(solucion_usuario) << endl;

		//BUSCAMOS LAS LETRAS
		vector<Resultado> encontradas;

		cout << "Mis soluciones son:" << endl;

		for (int i=numero_letras; i>0; i--)
		{
			//Obtenemos la lista de palabras de la longitud actual
			vector<string> v = diccionario.PalabrasLongitud(i);

			for (vector<string>::iterator it = v.begin(); it!=v.end(); ++it)
			{
				string palabra_vector = *it;

				// Creamos un vector de letras usadas inicializado a false
				vector<bool> letras_usadas(letras.size(), false);

				int cont_usadas = 0;
				for (int l_actual =0; l_actual<palabra_vector.size(); l_actual++)
				{
					bool salir = false;
					char letra_actual = palabra_vector[l_actual];

					for (int l_orig=0; !salir && l_orig<palabra.size(); l_orig++)
					{
						if (!letras_usadas[l_orig] && palabra[l_orig] == letra_actual)
						{
							// La letra no está usada ,la marcamos como usada y incrementamos el contador de utilizadas 
							letras_usadas[l_orig] = true; 
							cont_usadas++; 
							salir = true;
						}
					}
				}
				//Si el tamaño de la palabra del vector con el del contador de usadas es igual hemos encontrado una palabra
				if (cont_usadas == palabra_vector.size())		
					encontradas.push_back(Resultado(palabra_vector,conjunto_letras.puntuacion(palabra_vector) ));
			}
		}

		if (encontradas.empty())
			cout <<"No se encontró ninguna palabra con esas letras" << endl;
		else
		{
			if (strcmp(argv[4], "L") == 0)
			{
				//Modo longitud
				sort(encontradas.begin(), encontradas.end(), Resultado::cmp_pal());
			}
			else if (strcmp(argv[4], "P") == 0)
			{ 
				//Modo puntos
				sort(encontradas.begin(), encontradas.end(), Resultado::cmp_pts());
			}
			else
			{
				//Modo incorrecto
				cout<<"Error: El modo es incorrecto, debe ser L o P"<<endl;
				return 1;
			}
			// Pintamos las palabras encontradas
			for (vector<Resultado>::iterator it = encontradas.begin(); it!=encontradas.end(); ++it)
				cout << *it << endl;


		}

		cout << "¿Quieres seguir jugando [s/n]?";
		cin >> type;
		cout << endl;

	} while (tolower(type)!='n');

	return 0;
}


















