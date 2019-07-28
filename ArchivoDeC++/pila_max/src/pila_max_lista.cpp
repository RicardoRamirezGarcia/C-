void Pila_max::poner(int valor)
{
  elemento nuevo;
  nuevo.ele = valor; 

  if (vacia())
  {
    nuevo.maximo = valor;
  }
  else
  {
    elemento anterior = tope();
    nuevo.maximo = (valor > anterior.maximo) ? valor : anterior.maximo;
  }

  datos.insertar(datos.primero(), nuevo);
}