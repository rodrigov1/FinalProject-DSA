#include <string>
#include "../include/Router.h"

using namespace std;

// class methods 

Cola<Paquetes*> Router :: dividePage(Pagina page) {
    Cola<Paquetes*> aux;
    int size = page.getSize();   // n paquetes del mismo tamaño (m.c.m pero hay que implementarlo)

    for(int i = 0; i < size; i++) {
        Paquetes *pkg = new Paquetes(i,page);
        aux.encolar(pkg);
        delete pkg;
    }

    return aux;
};