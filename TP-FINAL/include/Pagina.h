#ifndef PAGINA_H
#define PAGINA_H

using namespace std;

class Pagina {
private:
    int id = 0;
    int size;
    byte origen[2];
    byte dest[2];

public:
    Pagina() {;};
    Pagina(int size, int origen[2], int dest[2]) {
        id++;
        this->size = size;
        this->origen[0] = byte(origen[0]);
        this->origen[1] = byte(origen[1]);
        this->dest[0] = byte(dest[0]);
        this->dest[1] = byte(dest[1]);
    };
    //~Pagina();
    int getId() { return id; };
    byte* getDest() { return dest; };
    byte* getOrigen() { return origen; };
    int getSize() { return size; };
};

#endif
