
/* ------------------------- PROBLEMA DE LAS N REINAS ----------------------- */
#include <ga/GASimpleGA.h> //  Algoritmo Genetico simple
#include <ga/GA1DArrayGenome.h> // Genoma --> array de enteros (dim. 1) alelos
#include <iostream>
#include <fstream>
using namespace std;

float fitness(GAGenome &); // Funcion objetivo --> al final
GABoolean Termina(GAGeneticAlgorithm &); // Funcion de terminacion --> al final
int CruceSudoku(const GAGenome& p1,const GAGenome & p2,GAGenome* c1,GAGenome* c2);
int MutacionSudoku(GAGenome& g,float pmut);
void leerSudoku(struct plantilla *S,char *nombreF);
void InicioSudoku(GAGenome& g);




struct plantilla{
       int tam;
       int *fijo;
};

int main(int argc, char **argv)
{

// Declaramos variables para los parametros del GA y las inicializamos

// Declarmaos la plantilla
    struct plantilla *S= new struct plantilla;
    char* fichero= argv[1]; // Guarda el fichero de texto que contiene el Sudoku
    leerSudoku(S,fichero);  // Almacena en la estructura plantilla el Sudoku que se le proporciona en formato de texto
    int popsize = atoi(argv[2]); //Guarda el tamaño de población
    int ngen = 12000; // Establece un número de generaciones máximas que va a realizar como  una de las condición de parada el algoritmo genetico
    float pcross = atof(argv[4]); // Almacena la probabilidad de cruzar entre los individuos
    float pmut = atof(argv[5]); // Almacena la probabilidad de mutar de cada elemento de un individuo , es decir el gen.

    cout << "Caso de prueba:  " << fichero << endl;
    cout << "Parametros:    - Tamaño poblacion: " << popsize << endl;
    cout << "               - Numero de generaciones: " << ngen << endl;
    cout << "               - Probabilidad cruce: " << pcross << endl;
    cout << "               - Probabilidad mutacion: " << pmut << endl;

// Conjunto enumerado de alelos --> valores posibles de cada gen del genoma

    GAAlleleSet<int> alelos;
    for(int i=0;i<9;i++) alelos.add(i);


// Creamos el genoma y definimos operadores de inicio, cruce y mutación

    GA1DArrayAlleleGenome<int> genome(S->tam*S->tam,alelos,fitness,S);
    genome.initializer(InicioSudoku);
    genome.crossover(CruceSudoku);
    genome.mutator(MutacionSudoku);

// Creamos el algoritmo genetico

    GASimpleGA ga(genome);

// Inicializamos - minimizar funcion objetivo, tamaño poblacion, nº generaciones,
// pr. cruce y pr. mutacion, selección y le indicamos que evolucione.

    ga.minimaxi(-1);
    ga.populationSize(popsize);
    ga.nGenerations(ngen);
    ga.pCrossover(pcross);
    ga.pMutation(pmut);

    if(strcmp("GATournamentSelector",argv[3])){
        GATournamentSelector selector; //Almacenas la forma de seleccionar la poblaciónTorneo :
        //Se establecen k torneos aleatorios entre parejas de individuos y se eligen los que 	ganan en cada torneo (mejor función fitness).
        ga.selector(selector);
        cout << "               - Torneo" << endl << endl; //para sacar la salida con parametros
    }
    if(strcmp("GARouletteWheelSelector",argv[3])){
        GARouletteWheelSelector selector; //Almacenas la forma de seleccionar la población
        //Ruleta : Se eligen con probabilidad proporcional a su función fitness.
        ga.selector(selector);
        cout << "               - Ruleta" << endl << endl; //para sacar la salida con parametros
    }

    ga.terminator(Termina);
    ga.evolve(1);
    cout << "El GA encuentra la solucion ( " << ga.statistics().bestIndividual() << ")" << endl;
    cout  <<"Con un valor fitness"<< ga.statistics().minEver() << " "<< endl;

}
// Cruce Sudoku

int CruceSudoku(const GAGenome& p1,const GAGenome & p2,GAGenome* c1,GAGenome* c2){

    //Obtiene el casting correspondiente para obtener el genoma
     GA1DArrayAlleleGenome<int> & m = (GA1DArrayAlleleGenome<int> &)p1;
     GA1DArrayAlleleGenome<int> & p = (GA1DArrayAlleleGenome<int> &)p2;

    struct plantilla * plantilla1 = (struct plantilla *) m.userData();
    int n=0;
    int punto1=GARandomInt(0,m.length()); // genera un numero entre 0 y 81
    while ((punto1%plantilla1->tam)!=0) punto1++; // busca el primer numero que sea modulo 9
    int punto2=m.length()-punto1; // coge el complementario al anterior

    /*Realiza un cruce por dos puntos obteniendo x filas de la madre precisamente desde 0 hasta el punto 1
        y el resto de otro sudoku padre*/

    if (c1){

            //Obtiene el casting correspondiente del hijo pero creas el genoma de arraygenome para obtener el metodo copy con cuatro parametros
            GA1DArrayGenome<int> & h1 = (GA1DArrayAlleleGenome<int> &)*c1;
             h1.copy(m,0,0,punto1);
             h1.copy(p,punto1,punto1,punto2);
             n++;
    }

    if (c2){

            //Obtiene el casting correspondiente del hijo pero creas el genoma de arraygenome para obtener el metodo copy con cuatro parametros
            GA1DArrayGenome<int> & h2 = (GA1DArrayAlleleGenome<int> &)*c2;

             h2.copy(p,0,0,punto1);
             h2.copy(m,punto1,punto1,punto2);
             n++;
    }

    return n;

}




void leerSudoku(struct plantilla *S,char *nombreF){
   /*Carga el fichero y lo trata como char para poder acceder al el por fila usando la sintaxis >> e id almacenado
   en la plantilla los valores necesario para leer el fichero completo */
   ifstream f(nombreF);

   f>>S->tam;

   S->fijo = new int[S->tam*S->tam];

   for(int i=0;i<S->tam*S->tam;i++)
           f>>S->fijo[i];

   f.close();
}
// Mutacion
bool checkColumna(int col[], int * check, int tam){
    /* modifica el array que le pasan como parametro check con el numero de repeticiones de cada numero y devuelve true en el caso
        en el que un numero para una columna es mayor que 1
    */
     bool repe=false;

     for(int i=0;i<tam;i++) check[i]=0;

     for(int i=0;i<tam;i++)
             check[col[i]-1]++;
     for(int i=0;i<tam;i++) if (check[i]>1) repe=true;

     return repe;
}
int MutacionSudoku(GAGenome& g,float pmut){
    //Obtiene el casting correspondiente para obtener el genoma
    GA1DArrayAlleleGenome<int> & genome = (GA1DArrayAlleleGenome<int> &)g;

    struct plantilla * plantilla1;
    plantilla1 = (struct plantilla *) genome.userData();
    int nmut=0;
    int aux;
    int fil;
    bool fila;

    int caux[plantilla1->tam];
    int *checkC=new int[plantilla1->tam];

    if (pmut<=0.0) return 0;

    for(int f=0; f<plantilla1->tam; f++)
       for(int c=0; c<plantilla1->tam; c++)
          if (plantilla1->fijo[(f*plantilla1->tam)+c]==0){
           if (GAFlipCoin(pmut) ){
               /*
               se realiza la mutacion de un elemento en fila o en columna actual en el caso de hacer cierta la condición
               con una probabilidad igual a pmut
               */
                if (GAFlipCoin(0.5)) fila = true;
                else fila = false;
                /*
                la probabilidad de que se mute un elemento por fila o columna es del 50 porciento
                */
                if (!fila){
                        /*
                        la mutación se hará por columnas y se apoyará de una función auxiliar que le devolverá true en caso de encontrar un elemento
                        repetido en esa columna y modificará un array que se le pasa como parámetro con el numero de repeticiones para cada numero
                        con esta información busca cual es el elemento repetido de ese array y busca la posición de ese numero repetido y en el caso
                        que en esa posicion antes en la plantilla original había un 0 puedes mutar el elemento con aquel elemento
                        que en check es igual a 0 eso significa que ese numero que vas a cambiar no estaba en esa columna,
                         cuando lo cambias puede pasar dos situaciones con esa fila para evitar las repeticiones por fila:

                        - que en la plantilla original hubiera un 0 y el valor despues de inicializar sea el mismo que el valor que modificas:
                            lo que debe de hacer es cambiar el valor que habia repetido en la columna por el valor actual en la fila
                        -que en la plantilla original estuviera el mismo valor que acabas de modificar  :
                            por lo tanto al comprobar en la fila que ese valor ya estaba deshaces la modificación
                        */

                      for(int j=0;j<plantilla1->tam;j++) caux[j]=genome.gene((j*plantilla1->tam)+c);
                      if (checkColumna(caux,checkC,plantilla1->tam)){
                         int v1 = GARandomInt(0,plantilla1->tam-1);
                         while (checkC[v1]<=1) v1=(v1+1)%plantilla1->tam;
                         v1++;
                         int v2 = GARandomInt(0,plantilla1->tam-1);
                         while (checkC[v2]!=0) v2=(v2+1)%plantilla1->tam;
                         v2++;

                         bool encontrado = false;
                         for(int j=0;j<plantilla1->tam && !encontrado;j++)
                                 if ((plantilla1->fijo[j*(plantilla1->tam)+c]==0)&&(genome.gene(j*(plantilla1->tam)+c)==v1)){
                                    encontrado = true;
                                    genome.gene((j*plantilla1->tam)+c,v2);
                                    fil = j;
                                 }

                         int col=(c+1)%plantilla1->tam;
                         while(genome.gene((fil*plantilla1->tam)+col)!=v2) col=(col+1)%plantilla1->tam;
                         if (plantilla1->fijo[(fil*plantilla1->tam)+col]==0) {
                                nmut++;
                                genome.gene((fil*plantilla1->tam)+col,v1);
                         }
                         else {
                              genome.gene((fil*plantilla1->tam)+c,v1);
                         }

                      }

                }
                else{
                        /*
                        Como en las filas los valores son diferentes hace un intercambio de los elementos
                        */
                   int v1 = (c + 1) %plantilla1->tam;
                   while ((plantilla1->fijo[(f*plantilla1->tam)+v1]!=0)) v1=(v1+1)%plantilla1->tam;
                   aux = genome.gene((f*plantilla1->tam)+c);
                   genome.gene((f*plantilla1->tam)+c,genome.gene((f*plantilla1->tam)+v1));
                   genome.gene((f*plantilla1->tam)+v1,aux);
                   nmut++;
                }
           }
          }

    return nmut; // se devuelve el numero de mutaciones realizadas
}


//InicioSudoku

void InicioSudoku(GAGenome& g){

     GA1DArrayAlleleGenome<int> & genome = (GA1DArrayAlleleGenome<int> &)g;//obtiene el casting correspondiente para obtener el genoma
     struct plantilla * plantilla1;//crea la estructura plantilla que representa al sudoku

     plantilla1 = (struct plantilla *) genome.userData(); //obtiene el sudoku inicial

     int aux[plantilla1->tam];

     for(int f=0;f<plantilla1->tam;f++){ //Recorre el sudoku

          for(int j=0;j<plantilla1->tam;j++) aux[j]=0;

        /* Para cada posición de cada fila genera un numero aleatorio entre 0 y 9 accede a esa posicion en el array y sustituye el valor
         de la posicion del array en la posición generado por el número aleatorio  y en el caso de que en esa posicion generada por el numero
        aleaotrio existiera otro numero distinto de cero avanza uno mas en el array e intenta colocar el numero en esa posicion asi hasta
        que todos los valores del 1 al 9 esten colocados en esa fila y pasa a la siguiente fila , gacias al array auxiliar va comparando con
        los valores del sudoku para hacer que en cada fila no se repita ningún número y que no haya 0.
        */

          for(int j=1;j<=plantilla1->tam;j++){
            int v=GARandomInt(0,plantilla1->tam-1);
            while (aux[v]!=0) v=(v+1)%plantilla1->tam;
            aux[v]=j;
          }
          int i=0;

          while(i<plantilla1->tam){

              while((plantilla1->fijo[(f*plantilla1->tam)+i]==0) && (i<plantilla1->tam)) i++;

              if (i<plantilla1->tam){

                     bool encontrado=false;
                     for(int j=0;(j<plantilla1->tam) && (!encontrado);j++)
                             if (aux[j]==plantilla1->fijo[(f*plantilla1->tam)+i]) {
                                encontrado=true;
                                aux[j]=aux[i];
                             }

                     aux[i]=plantilla1->fijo[(f*plantilla1->tam)+i];
              }
              i++;

          }

          for(int c=0;c<plantilla1->tam;c++)
                  genome.gene((f*plantilla1->tam)+c,aux[c]);
     }
}

// Funcion de terminacion

GABoolean Termina(GAGeneticAlgorithm & ga){
    /*Devuelve verdadero o falso en función a si cumple una condición de parada , ya sea por numero máximo de generaciones
    o que encuentra el valor fitness 0 , es decir no ha colisiones en el sudoku y esta resuelto */
    if ( (ga.statistics().minEver()==0) ||
        (ga.statistics().generation()==ga.nGenerations()) ) return gaTrue;
    else return gaFalse;
}
// Funcion fitness
float numrep(int c[]){
/* Dado el array que recibes como parametro devuelves la suma de repeticiones totales de cada numero en ese array
*/
int n =0;
int a[9] ={0,0,0,0,0,0,0,0,0};
for(int i=0;i<9;i++){
a[c[i]-1]=a[c[i]-1]+1;
}
for(int j=0;j<9;j++){
    if(a[j]!=0){
        n = n + (a[j]-1);
    }
}
return n;
}
void imprimirSudoku(GA1DArrayAlleleGenome<int> & genome){

    for(int i=1;i<10;i++){
            if((i==4)||(i==7)){
                cout << endl;
            }
            cout << endl;
        for(int j=0;j<9;j++){
            if((j==3)||(j==6)){
            cout << "   " ;
            }
            cout << genome.gene(i*j);
        }
    }

}
float fitness(GAGenome &ga){
    /* En una iteracion voy almacenando los elementos en distintos arrays en función a la posisción del sudoku
     y cuando llega al final de cada fila columna o se termina un conjunto llamo a una función que calcula en numero de repeticiones
     sobre cada numero de ese array y voy acumulandolo sobre una variable local al procedimiento
          */
    int fitness = 0;
    GA1DArrayAlleleGenome<int> & genome = (GA1DArrayAlleleGenome<int> &)ga;
    int columna0[9];int columna1[9];int columna2[9];int columna3[9];
    int columna4[9];int columna5[9];int columna6[9];int columna7[9];int columna8[9];
    int conjunto0[9];int conjunto1[9];int conjunto2[9];
    struct plantilla * p;
     p = (struct plantilla *) genome.userData();
    for(int i=0;i<p->tam*p->tam;i++){
        if(i%9 == 0){
          columna0[i/9] = genome.gene(i);

            if((i/9 == 0)||(i/9 == 3)||(i/9 == 6)){
                conjunto0[0] = genome.gene(i);
            }
            if((i/9 == 1)||(i/9 == 4)||(i/9 == 7)){
                conjunto0[3] = genome.gene(i);
            }
            if((i/9 == 2)||(i/9 == 5)||(i/9 == 8)){
                conjunto0[6] = genome.gene(i);
            }
            if(i/9 == 8) {
                fitness = fitness + numrep(columna0);
        }
        }if(i%9 == 1){
          columna1[i/9] = genome.gene(i);
            if((i/9 == 0)||(i/9 == 3)||(i/9 == 6)){
                conjunto0[1] = genome.gene(i);
            }
            if((i/9 == 1)||(i/9 == 4)||(i/9 == 7)){
                conjunto0[4] = genome.gene(i);
            }
            if((i/9 == 2)||(i/9 == 5)||(i/9 == 8)){
                conjunto0[7] = genome.gene(i);
            }
            if(i/9 == 8) {
                fitness = fitness + numrep(columna1);
        }
        }if(i%9 == 2){
          columna2[i/9] = genome.gene(i);
            if((i/9 == 0)||(i/9 == 3)||(i/9 == 6)){
                conjunto0[2] = genome.gene(i);
            }
            if((i/9 == 1)||(i/9 == 4)||(i/9 == 7)){
                conjunto0[5] = genome.gene(i);
            }
            if((i/9 == 2)||(i/9 == 5)||(i/9 == 8)){
                conjunto0[8] = genome.gene(i);
                fitness = fitness + numrep(conjunto0);
            }
            if(i/9 == 8) {
                fitness = fitness + numrep(columna2);
            }
        }if(i%9 == 3){
          columna3[i/9] = genome.gene(i);
            if((i/9 == 0)||(i/9 == 3)||(i/9 == 6)){
                conjunto1[0] = genome.gene(i);
            }
            if((i/9 == 1)||(i/9 == 4)||(i/9 == 7)){
                conjunto1[3] = genome.gene(i);
            }
            if((i/9 == 2)||(i/9 == 5)||(i/9 == 8)){
                conjunto1[6] = genome.gene(i);
            }
            if(i/9 == 8){
                fitness += numrep(columna3);
        }
        }if(i%9 == 4){
          columna4[i/9] = genome.gene(i);
            if((i/9 == 0)||(i/9 == 3)||(i/9 == 6)){
                conjunto1[1] = genome.gene(i);
            }
            if((i/9 == 1)||(i/9 == 4)||(i/9 == 7)){
                conjunto1[4] = genome.gene(i);
            }
            if((i/9 == 2)||(i/9 == 5)||(i/9 == 8)){
                conjunto1[7] = genome.gene(i);
            }
            if(i/9 == 8) {
                fitness = fitness + numrep(columna4);
        }
        }if(i%9 == 5){
          columna5[i/9] = genome.gene(i);
            if((i/9 == 0)||(i/9 == 3)||(i/9 == 6)){
                conjunto1[2] = genome.gene(i);
            }
            if((i/9 == 1)||(i/9 == 4)||(i/9 == 7)){
                conjunto1[5] = genome.gene(i);
            }
            if((i/9 == 2)||(i/9 == 5)||(i/9 == 8)){
                conjunto1[8] = genome.gene(i);
                fitness = fitness + numrep(conjunto1);
            }
            if(i/9 == 8) {
                fitness = fitness + numrep(columna5);
        }
        }if(i%9 == 6){
          columna6[i/9] = genome.gene(i);
            if((i/9 == 0)||(i/9 == 3)||(i/9 == 6)){
                conjunto2[0] = genome.gene(i);
            }
            if((i/9 == 1)||(i/9 == 4)||(i/9 == 7)){
                conjunto2[3] = genome.gene(i);
            }
            if((i/9 == 2)||(i/9 == 5)||(i/9 == 8)){
                conjunto2[6] = genome.gene(i);
            }
            if(i/9 == 8) {
                fitness = fitness + numrep(columna6);
        }
        }if(i%9 == 7){
          columna7[i/9] = genome.gene(i);
            if((i/9 == 0)||(i/9 == 3)||(i/9 == 6)){
                conjunto2[1] = genome.gene(i);
            }
            if((i/9 == 1)||(i/9 == 4)||(i/9 == 7)){
                conjunto2[4] = genome.gene(i);
            }
            if((i/9 == 2)||(i/9 == 5)||(i/9 == 8)){
                conjunto2[7] = genome.gene(i);
            }
            if(i/9 == 8) {
                fitness = fitness + numrep(columna7);
        }
        }if(i%9 == 8){
          columna8[i/9] = genome.gene(i);
            if((i/9 == 0)||(i/9 == 3)||(i/9 == 6)){
                conjunto2[2] = genome.gene(i);
            }
            if((i/9 == 1)||(i/9 == 4)||(i/9 == 7)){
                conjunto2[5] = genome.gene(i);
            }
            if((i/9 == 2)||(i/9 == 5)||(i/9 == 8)){
                conjunto2[8] = genome.gene(i);
                fitness += numrep(conjunto2);
            }
            if(i/9 == 8) {
                fitness += numrep(columna8);
        }
        }

    }
 return fitness;
}
