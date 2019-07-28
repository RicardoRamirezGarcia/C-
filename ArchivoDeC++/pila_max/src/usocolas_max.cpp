#include <iostream>
#include "cola_max.h"

using namespace std;

int main(){

  Cola_max c,d;
  int i;

  // De 10 a 0
  for ( i=10; i>=0 ; i--)
    c.poner(i);


  while (!c.vacia() ){
    elemento x = c.tope();
    cout << x << endl;
    c.quitar();
  }


  return 0;
}
