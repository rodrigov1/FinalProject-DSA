#ifndef PAGINA_H
#define PAGINA_H

using namespace std;

class Pagina
{
private:
    int id = 0;
    int size;
    int origen[2];
    int dest[2];

public:
    Pagina(){};
    Pagina(int size, int origen[2], int dest[2])
    {
        this->id++;
        this->size = size;
        this->origen[0] = origen[0];
        this->origen[1] = origen[1];
        this->dest[0] = dest[0];
        this->dest[1] = dest[1];
    }
    //~Pagina();
    int getId() { return id; };
    int *getDest() { return dest; };
    int *getOrigen() { return origen; };
    int getSize() { return size; };
};

#endif
