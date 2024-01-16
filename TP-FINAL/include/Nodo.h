#ifndef NODO_H
#define NODO_H
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;

template <class T>
class Nodo
{
private:
    T dato;
    Nodo *next;

public:
    Nodo() { next = NULL; };
    Nodo(T a)
    {
        dato = a;
        next = NULL;
    };
    void set_dato(T a) { dato = a; };
    void set_next(Nodo *n) { next = n; };
    T get_dato() { return dato; };
    Nodo *get_next() { return next; };
    bool es_vacio() { return next == NULL; }
};

#endif