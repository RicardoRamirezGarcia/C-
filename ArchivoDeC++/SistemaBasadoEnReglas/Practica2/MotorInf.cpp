#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <cstdlib>
using namespace std;


struct Atributo{
string nombre;
string tipo;
list<string> valores;
};

struct Fconf{
int Natributos;
struct Atributo* Atr;
string objetivo;
int Nprio;
int *prio;
};
void leerConf(struct Fconf *FC,char* nombreF){
   ifstream f(nombreF);
   string cadena;
   getline(f,cadena);

   if(cadena=="ATRIBUTOS"){
        f>>FC->Natributos;
        FC->Atr = new struct Atributo [FC->Natributos];
        for(int i=0;i<FC->Natributos;i++){
            f>>FC->Atr[i].nombre;
            f>>cadena;
            if(cadena == "Nom"){
                FC->Atr[i].tipo = "Nom";
                string aux;
                f>>cadena;
                int pos=1;
                while(pos < (int)cadena.size() ){
                    if((cadena[pos] !=',')&& (cadena[pos] != '}')){
                        aux+=cadena[pos];
                    }else{
                        FC->Atr[i].valores.push_back(aux);
                        aux="";
                    }
                    pos++;
            }
            }else
             FC->Atr[i].tipo = "NU";
        }
    f>>cadena;
    if(cadena=="OBJETIVO"){
        f>>FC->objetivo;
        f>>cadena;
        if(cadena=="PRIORIDADES-REGLAS"){
            f>>FC->Nprio;
            FC->prio = new int[FC->Nprio];
            for(int j=0;j<FC->Nprio;j++){
                f>>FC->prio[j];
            }
        }else cout << "formato incorrecto" << endl;
    }else cout << "formato incorrecto" << endl;

   f.close();
   }
}
struct Antecedente{
string atributo;
string operador;
string valorS;//depende del tipo del atributo
int valorI;//depende del tipo del atributo
};

struct Consecuente{
string atributo;
string operador;
string valorS;//depende del tipo del atributo
int valorI;//depende del tipo del atributo
};

struct Reglas{
list<Antecedente> Ant;
struct Consecuente Con;
};

struct BaseConocimiento{
string dominio;
int Nreglas;
struct Reglas* R;
};

string getTipoAtributo(string atr,struct Fconf *FC){

    int i = 0;
    while(atr != FC->Atr[i].nombre){
            i++;
    }
    return FC->Atr[i].tipo;
}

void leerBC(struct BaseConocimiento *BC,char* nombreF,struct Fconf *FC){

   string atrAux,opAux,valorAux,tipoAux;
   int auxI;

   struct Antecedente antAux;
   struct Consecuente conAux;


   ifstream f(nombreF);
   string cadena;
   getline(f,cadena);


        BC->dominio=cadena;
        f>>BC->Nreglas;
        BC->R = new struct Reglas [BC->Nreglas];
        for(int i=0;i<BC->Nreglas;i++){

            f>>cadena;
            f>>cadena;
            if(cadena == "Si"){


                //Antecedentes
                while(cadena != "Entonces"){

                    f>>atrAux;
                    f>>opAux;
                    tipoAux=getTipoAtributo(atrAux,FC);

                    if(tipoAux=="Nom"){//atributos nominales

                        f>>valorAux;
                        antAux.atributo = atrAux;
                        antAux.operador =opAux;
                        antAux.valorS = valorAux;

                        BC->R[i].Ant.push_back(antAux);

                    }else{//atributos numerales

                        f>>auxI;
                        antAux.atributo = atrAux;
                        antAux.operador =opAux;
                        antAux.valorI = auxI;

                         BC->R[i].Ant.push_back(antAux);
                    }
                    f>>cadena;
                }
                //Consecuente

                    f>>atrAux;
                    f>>opAux;
                    tipoAux=getTipoAtributo(atrAux,FC);

                if(tipoAux=="Nom"){//atributos nominales

                        f>>valorAux;
                        BC->R[i].Con.atributo = atrAux;
                        BC->R[i].Con.operador =opAux;
                        BC->R[i].Con.valorS = valorAux;




                    }else{//atributos numerales

                        f>>auxI;
                        BC->R[i].Con.atributo = atrAux;
                        BC->R[i].Con.operador =opAux;
                        BC->R[i].Con.valorI = auxI;


                    }
            }
        }
   f.close();

}

struct BaseHecho{
int NhechosI;
int Numhechos;
list<Antecedente> AntHechos;
};

void leerBH(struct BaseHecho *BH,char* nombreF,struct Fconf *FC){

   string atrAux,opAux,valorAux,tipoAux;
   int auxI;

   struct Antecedente antAux;

   ifstream f(nombreF);

   f>>BH->NhechosI;
   BH->Numhechos=BH->NhechosI;

   int i = 0;
   while(i != BH->NhechosI ){

    f>>atrAux;
    f>>opAux;
    tipoAux=getTipoAtributo(atrAux,FC);

        if(tipoAux=="Nom"){//atributos nominales

                f>>valorAux;
                antAux.atributo = atrAux;
                antAux.operador = opAux;
                antAux.valorS = valorAux;

                BH->AntHechos.push_back(antAux);


            }else{//atributos numerales

                f>>auxI;

                antAux.atributo = atrAux;
                antAux.operador = opAux;
                antAux.valorI = auxI;

                BH->AntHechos.push_back(antAux);
            }
    i++;
   }
   f.close();
}



void ShowList(list<Antecedente> &sList,struct Fconf *FC){

 list<Antecedente>::iterator pos;
 pos = sList.begin();
 string tipoAux;
 while( pos != sList.end())
 {
     tipoAux=getTipoAtributo(pos->atributo,FC);
     if(tipoAux== "Nom"){
     cout<< "hecho: " <<pos->atributo << " " << pos->operador << " " << pos->valorS<< endl;
     }else{
     cout<< "hecho: " <<pos->atributo << " " << pos->operador << " " << pos->valorI<< endl;
     }

 pos++;
 }
}
void ShowReglas( list<int> &sList,struct Fconf *FC){
 list<int>::iterator pos;
 pos = sList.begin();
 while( pos != sList.end()){
     cout << "   R"<< *pos << " con un valor de prioridad: " << FC->prio[*pos-1] << endl;
 pos++;
 }
}
void mostrarObtRprio(int regla,struct BaseHecho *BH,struct BaseConocimiento *BC,struct Fconf *FC){
    // mostrar la salida para ver como se ven afectadas las structuras cuando avanza el algoritmo
 cout << "ANTECEDENTES:" << endl;
 list<Antecedente>::iterator pos;
 pos = BC->R[regla-1].Ant.begin();
 list<Antecedente>::iterator pos1;
 pos1 = BH->AntHechos.begin();
 string tipoAux;
 int n=1;

 while( pos != BC->R[regla-1].Ant.end()){

     tipoAux=getTipoAtributo(pos->atributo,FC);
     if(tipoAux== "Nom"){
     cout<< "antecedente: " <<pos->atributo << " " << pos->operador << " " << pos->valorS<< endl;
     }else{
     cout<< "antecedente: " <<pos->atributo << " " << pos->operador << " " << pos->valorI<< endl;
     }
     cout << "      Hecho de la BH que confirma el antecedente:" << endl;
         while( pos1 != BH->AntHechos.end()){
            if(pos1->atributo == pos->atributo){
                   if(tipoAux== "Nom"){
                    cout<< "      hecho: " <<pos1->atributo << " " << pos1->operador << " " << pos1->valorS<< endl;
                    }else{
                    cout<< "      hecho: " <<pos1->atributo << " " << pos1->operador << " " << pos1->valorI<< endl;
                    }
                    if(n <= BH->NhechosI){
                        cout << "      El hecho es un dato de entrada" << endl;
                    }else{
                        cout << "      El hecho ha sido inferido por una regla" << endl;
                    }
               }
               n++;
               pos1++;
        }
 pos++;
 }

 if(tipoAux== "Nom"){
        cout << "COCSECUENTE: " << BC->R[regla-1].Con.atributo << " " << BC->R[regla-1].Con.operador << " " << BC->R[regla-1].Con.valorS << endl;
 }else{
        cout << "COCSECUENTE: " << BC->R[regla-1].Con.atributo << " " << BC->R[regla-1].Con.operador << " " << BC->R[regla-1].Con.valorI << endl;
 }
}
list<int> actualizarConjuntoConflicto(list<int> &sList,list<int> &sList2){
    //insertar todos elemento de la lista 2 en la lista 1
    list<int>::iterator pos;
    pos = sList2.begin();
    while( pos != sList2.end()){
        sList.push_back(*pos);
        pos++;
 }
    return sList;
}
bool esContenida( list<Antecedente> &sList , string meta ){
// comprueba si en la base de hechos se encuentra el objetivo indicado en el fichero de configuración
 list<Antecedente>::iterator pos;

struct Antecedente antAux;
  pos = sList.begin();
 while( pos != sList.end())
 {
      if(pos->atributo == meta){
        return true;
      }
 pos++;
 }
 return false;
}

int resolver(list<int> &sList,struct Fconf *FC){
    // devuelve la regla del conjunto conflicto con el valor de prioridad mas alto
 list<int>::iterator pos;
 list<int>::iterator posmayor;
 pos = sList.begin();
 int mayor= -1;

 while( pos != sList.end()){
    if(mayor < FC->prio[*pos-1]){
        mayor =FC->prio[*pos-1]; //valor de prioridad mas alto
        posmayor = pos; //  posicion de la regla con el valor de prioridad mas alto
    }
    pos++;
 }
cout << "REGLA PRIORITARIA" << endl;
cout << "   R"<< *posmayor << " con un valor de prioridad: " << mayor << endl;
return *posmayor;
}

void aplicar(int regla,struct BaseHecho *BH,struct BaseConocimiento *BC,struct Fconf *FC){
  //conseguir el consecuente de la regla en la base de conocimiento
  // almacenarla en la base de hechos
  string tipoAux;
  struct Antecedente antAux;

  tipoAux=getTipoAtributo(BC->R[regla-1].Con.atributo,FC);

  if(tipoAux=="Nom"){
    antAux.atributo=BC->R[regla-1].Con.atributo;
    antAux.operador=BC->R[regla-1].Con.operador;
    antAux.valorS=BC->R[regla-1].Con.valorS;

    cout << "hecho: " << BC->R[regla-1].Con.atributo << " " << BC->R[regla-1].Con.operador << " " << BC->R[regla-1].Con.valorS << endl;

    BH->AntHechos.push_back(antAux);
    BH->Numhechos++;
  }else{

    antAux.atributo=BC->R[regla-1].Con.atributo;
    antAux.operador=BC->R[regla-1].Con.operador;
    antAux.valorI=BC->R[regla-1].Con.valorI;

    cout << "hecho: " << BC->R[regla-1].Con.atributo << " " << BC->R[regla-1].Con.operador << " " << BC->R[regla-1].Con.valorI << endl;

    BH->AntHechos.push_back(antAux);
    BH->Numhechos++;
  }

}


list<int> equiparar(struct BaseConocimiento *BC,struct BaseHecho *BH, bool* reglasMarcadas,struct Fconf *FC){

    list<Antecedente>::iterator posRBC;
    list<Antecedente>::iterator posRBH;
    list<int> conjuntoConflicto;
    string tipoAux;
    int nAnt=0;
    int antRBCcoincidenBH=0;

     for(int i=0;i<BC->Nreglas;i++){// para cada regla
        if(reglasMarcadas[i] == false){
            posRBC = BC->R[i].Ant.begin();
            nAnt = 0;
            antRBCcoincidenBH=0;
            while( posRBC != BC->R[i].Ant.end()){//para la lista de antecedentes de cada regla
                posRBH = BH->AntHechos.begin();
                while( posRBH != BH->AntHechos.end()){//para cada hecho
                  if(posRBC->atributo == posRBH->atributo){
                     tipoAux=getTipoAtributo(posRBH->atributo,FC);
                        if(tipoAux=="Nom"){

                            if(posRBC->valorS == posRBH->valorS){//coincide el valor del atributo de la bh con la bc
                                antRBCcoincidenBH++;
                            }

                        }else{

                            if(posRBC->operador == "="){
                                if(posRBC->valorI == posRBH->valorI){//coincide el valor del atributo de la bh con la bc
                                antRBCcoincidenBH++;
                                }
                            }else if(posRBC->operador == "<"){
                                if(posRBH->valorI < posRBC->valorI){//coincide el valor del atributo de la bh con la bc
                                antRBCcoincidenBH++;
                                }
                            }else if(posRBC->operador == ">"){
                                if(posRBH->valorI > posRBC->valorI){//coincide el valor del atributo de la bh con la bc
                                antRBCcoincidenBH++;
                                }
                            }else if(posRBC->operador == ">="){
                                if(posRBH->valorI >= posRBC->valorI){//coincide el valor del atributo de la bh con la bc
                                antRBCcoincidenBH++;
                                }
                            }else if(posRBC->operador == "<="){
                                if(posRBH->valorI <= posRBC->valorI){//coincide el valor del atributo de la bh con la bc
                                antRBCcoincidenBH++;
                                }
                            }

                        }
                        posRBH = BH->AntHechos.end() ;
                  }else{//fin coincide el atributo
                      posRBH++;
                  } //fin no coincide el atributo

                }// fin para cada hecho
             posRBC++;
             nAnt++;
            }
            if(nAnt == antRBCcoincidenBH){
                    conjuntoConflicto.push_back(i+1);// la regla se añade al conjunto conflicto
            }

        }
    }
    return conjuntoConflicto;
}




int main(int argc, char **argv){
    struct Fconf *FC= new struct Fconf;
    char* Fconfig = argv[1];
    struct BaseConocimiento *BC = new struct BaseConocimiento;
    char* Bconocimientos = argv[2];
    struct BaseHecho *BH = new struct BaseHecho;
    char* Bhechos = argv[3];

    list <int> conjuntoConflicto;
    list <int> conjuntoConflictoAux;
    bool control = false;//para controlar la equiparacion
    int reglaActual;// regla actual a aplciar
    int n=1;// nuero de iteraciones que ejecuta el algoritmo
    //ofstream fs1("Salida1.txt");


    list <int>::iterator pos;// para acceder a la posición de la lista conjuntoConflicto para eliminar una regla
    pos = conjuntoConflicto.begin();


    leerConf(FC,Fconfig); // lee el fichero de configuracion y lo almacena en la structura FC
    bool* reglasMarcadas = new bool[FC->Natributos];
    for(int j=0;j<FC->Natributos;j++){//inicializar el array de reglas marcadas
        reglasMarcadas[j]= false;
    }

    leerBC(BC,Bconocimientos,FC); //lee el fichero que contiene la base de conocimientos y lo almacena en la structura BC
    cout << BC->dominio << endl;
    cout << "Atributo objetivo: " << FC->objetivo <<endl;
    leerBH(BH,Bhechos,FC); // lee el contenido del fichero de la base de hechos y la almacena en la estructura BH

    ShowList(BH->AntHechos,FC);

    cout << "Proceso de razonamiento seguido por el SBR" << endl;

    conjuntoConflicto = equiparar(BC,BH,reglasMarcadas,FC); // conjunto conflcito inicial
    control = true;
    while(!esContenida(BH->AntHechos,FC->objetivo) && (!(conjuntoConflicto.empty()))){
    cout << "<<<<<<<<<<ITERACION: " << n << ">>>>>>>>>>"<< endl;
        if(!control){
                conjuntoConflictoAux= equiparar(BC,BH,reglasMarcadas,FC); // obtener el conjunto conflicto auxiliar
                if(!conjuntoConflictoAux.empty()){
                conjuntoConflicto=actualizarConjuntoConflicto(conjuntoConflicto,conjuntoConflictoAux); //añadir las el cojunto conflicto auxiliar al conjunto conflicto con el que trabaja el algoritmoa a la hora de aplicar las reglas
                }
                control = false;
        }
        cout << "CONTENIDO CONJUNTO CONFLICTO" << endl;
        cout << "ID REGLAS EN CONJUNTO CONFLICTO" << endl;

        control = false;
        if(!(conjuntoConflicto.empty())){
            reglaActual= resolver(conjuntoConflicto,FC); // obtener regla del conjunto conflicto con el valor de prioridad mas alto
            mostrarObtRprio(reglaActual,BH,BC,FC);//muestra como se han verificado los antecedentes de la regla escogida y muestra el consecuente que se btiene al aplicar ésta
            cout << "HECHO INFERIDO: " << endl;
            aplicar(reglaActual,BH,BC,FC); // APLICAR REGLA Y ACTUALIZAR BASE DE HECHOS con el hecho inferido por la regla
            cout<< "CONTENIDO BH ACTUALIZADA"<< endl;
            ShowList(BH->AntHechos,FC);
            reglasMarcadas[reglaActual - 1] = true; //marcar regla actual para no tener que aplicarla de nuevo porque ya ha sido aplicada y eliminarla del conjunto conflicto ;
            advance(pos,reglaActual -1); // colocarse en la regla a eliminar
            pos = conjuntoConflicto.erase(pos); //elimina la regla y devuelve el puntero al siguiente de la regla eliminada
            pos = conjuntoConflicto.begin(); // colocarse en el inicio para poder usar de nuevo la función advance
        }
     n++;
    }

    if(esContenida(BH->AntHechos,FC->objetivo)){
    cout << "Se ha alcanzado el objetivo "<< FC->objetivo << endl;
    }else{
    cout << "No se ha logrado alcanzar el objetivo" << endl;
    }

return 0;
}
