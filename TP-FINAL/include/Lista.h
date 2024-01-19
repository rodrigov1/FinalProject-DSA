#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <class T>
class Nodo
{
private:
  T dato;
  Nodo *next;

public:
  Nodo() { next = nullptr; };
  Nodo(T a)
  {
    dato = a;
    next = nullptr;
  };
  void set_dato(T a) { dato = a; };
  void set_next(Nodo *n) { next = n; };
  T get_dato() { return dato; };
  Nodo *get_next() { return next; };
  bool es_vacio() { return next == nullptr; }
};

template <class T>
class Lista
{
private:
  Nodo<T> *czo;
  void addO(T d, Nodo<T> *ant);
  void borrarD(T d, Nodo<T> *ant);

public:
  Lista()
  {
    czo = new Nodo<T>();
  };
  Lista(Nodo<T> *n) { czo = n; };
  //~Lista(void);
  void add(T d); // sumar nodos a la lista
  bool esvacia(void);
  T cabeza(void);     // retorna el dato del primer nodo
  Lista *resto(void); // retorna el puntero al "resto" de la lista
                      // resto= lo que queda de la lista sin la cabeza
  string toPrint(string p);
  void impre(void);
  T suma(T i);
  int size();
  bool esta(T d);                               // detecta si d esta en la lista
  void borrarDato(T d) { borrarD(d, nullptr); } // borra el nodo que contiene d
  void borrar(void);                            // borra la cabeza
  void borrar_last();                           // borra el ultimo
  void concat(Lista<T> *l1);                    // le transfiere los datos de l1 a this
  Lista<T> *copy(void);                         // hace una copia de la lista
  void tomar(int n);                            // deja "vivos" los n primeros nodos y borra el resto
  void addOrdenado(T d)
  {
    addO(d, nullptr);
  };        // sumar nodos a la lista Ordenados de menor a MAYOR
  T last(); // retorna el dato del ultimo nodo
  Nodo<T> *get_czo() { return czo; };
  void addFinal(T d); // Agrega un nodo al final de la lista
};

template <class T>
T Lista<T>::last()
{
  if (!this->esvacia())
  {
    if (this->resto()->esvacia())
      return this->cabeza();
    return this->resto()->last();
  }
  return 0;
}

template <class T>
void Lista<T>::add(T d) // 100
{
  Nodo<T> *nuevo = new Nodo<T>(d);
  nuevo->set_next(czo);
  czo = nuevo;
}

template <class T>
bool Lista<T>::esvacia(void) { return czo->es_vacio(); }
template <class T>
T Lista<T>::cabeza(void)
{
  if (this->esvacia())
  {
    cout << " Error, Cabeza de lista vacia";
    return 0;
  }
  return czo->get_dato();
}

template <class T>
Lista<T> *Lista<T>::resto(void)
{
  Lista *l = new Lista(czo->get_next());
  return (l);
}

template <class T>
string Lista<T>::toPrint(string p)
{
  if (this->esvacia())
  {
    return p;
  }
  else
  {
    // std::ostringstream stm;
    ostringstream stm;
    stm << this->cabeza() << "-" << this->resto()->toPrint(p) << endl;
    // cout<<endl<<" stm.str()= "<<stm.str()<<endl;
    return stm.str();
  }
}

template <class T>
T Lista<T>::suma(T i)
{ // cout<<" i al entrar= "<<i<<endl;
  if (this->esvacia())
  {
    return i;
  }
  else
  {

    // cout<<"this->cabeza()= "<<this->cabeza()<<endl;
    return this->resto()->suma(i + this->cabeza());
  }
}

template <class T>
int Lista<T>::size()
{
  if (this->esvacia())
    return 0;
  return 1 + this->resto()->size();
}

template <class T>
void Lista<T>::borrar(void)
{ // borra el nodo cabeza
  if (!this->esvacia())
  {
    Nodo<T> *tmp = czo;
    czo = czo->get_next();
    delete tmp;
  }
}

template <class T>
void Lista<T>::borrar_last()
{ // borra el ultimo nodo
  if (!this->esvacia())
  {
    if ((czo->get_next())->get_next() == nullptr)
    {
      delete czo->get_next();
      czo->set_next(nullptr);
    }
    else
      this->resto()->borrar_last();
  }
}

template <class T>
void Lista<T>::concat(Lista<T> *l1)
{ // le transfiere los datos de l1 a this
  if (!(l1->esvacia()))
  {
    this->concat(l1->resto());
    this->add(l1->cabeza());
  }
}

template <class T>
Lista<T> *Lista<T>::copy(void)
{
  Lista<T> *aux = new Lista();
  aux->concat(this);
  return aux;
}

template <class T>
void Lista<T>::tomar(
    int n)
{ // deja "vivos" los n primeros nodos y borra el resto
  if (this->size() > n)
  {
    this->borrar_last();
    this->tomar(n);
  }
}

template <class T>
void Lista<T>::impre(void)
{
  Nodo<T> *aux;
  aux = czo;
  while (aux->get_next() != nullptr)
  {
    cout << aux->get_dato() << endl;
    aux = aux->get_next();
  }
}

template <class T>
void Lista<T>::addO(T d, Nodo<T> *ant)
{
  if (this->esvacia())
  { // el primero
    this->add(d);
  }
  else
  {
    if (d < czo->get_dato())
    {
      if (ant == nullptr)
      { // al principio
        this->add(d);
      }
      else
      { // entre medio
        Nodo<T> *nuevo = new Nodo<T>(d);
        nuevo->set_next(ant->get_next());
        ant->set_next(nuevo);
      }
    }
    else
    {
      if ((czo->get_next())->get_next() == nullptr)
      { // al final
        Nodo<T> *nuevo = new Nodo<T>(d);
        nuevo->set_next(czo->get_next());
        czo->set_next(nuevo);
      }
      else
        this->resto()->addO(d, czo);
    }
  }
}

template <class T>
void Lista<T>::addFinal(T d)
{
  if (this->esvacia())
  { // el primero
    this->add(d);
  }
  else
  {
    if ((czo->get_next())->get_next() == nullptr)
    { // al final
      Nodo<T> *nuevo = new Nodo<T>(d);
      nuevo->set_next(czo->get_next());
      czo->set_next(nuevo);
    }
    else
      this->resto()->addFinal(d);
  }
}
template <class T>
bool Lista<T>::esta(T d)
{ // busca d en la lista
  if (this->esvacia())
    return false;
  if (this->cabeza() == d)
    return true;

  return this->resto()->esta(d);
}

template <class T>
void Lista<T>::borrarD(T d, Nodo<T> *ant)
{
  if (!this->esvacia())
  {
    if (d == this->cabeza())
    {
      if (ant == nullptr)
      { // al principio
        this->borrar();
      }
      else
      { // entre medio
        ant->set_next(czo->get_next());
        delete czo;
      }
    }
    else
      this->resto()->borrarD(d, czo);
  }
}

template <class T>
class Pila : public Lista<T>
{
public:
  Pila() { Lista<T>(); };
  void apilar(T d) { this->add(d); };
  T tope(void) { return this->cabeza(); };
  void desapilar(void) { this->borrar(); };
  bool pilavacia() { return this->esvacia(); };
};

template <class T>
class Cola : public Lista<T>
{
public:
  Cola(void) { Lista<T>(); };
  //~Cola(void);
  T tope() { return this->last(); };
  bool colavacia(void) { return this->esvacia(); };
  void encolar(T a) { this->add(a); };
  void desencolar(void) { this->borrar_last(); };
  T ultimo(void) { return this->cabeza(); };
  string imprimir(string s) { return this->toPrint(s); };
  int sizeCola()
  {
    if (this->esvacia())
      return 0;
    return 1 + this->resto()->size();
  }
};

#endif