#ifndef PAGINA_H
#define PAGINA_H

using namespace std;

class Pagina
{
private:
    int id;
    int size;
    bool state = 0;
    int orig[2];
    int dest[2];

public:
    Pagina() { ; };
    Pagina(int id, int size, int origen[2], int dest[2])
    {
        this->id = id;
        this->size = size;
        this->orig[0] = origen[0];
        this->orig[1] = origen[1];
        this->dest[0] = dest[0];
        this->dest[1] = dest[1];
    };
    //~Pagina();
    int getId() { return id; };
    int *getDest() { return dest; };
    int *getOrigin() { return orig; };
    int getSize() { return size; };
};

#endif
