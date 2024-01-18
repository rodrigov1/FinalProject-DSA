#ifndef PAGINA_H
#define PAGINA_H

using namespace std;

class Pagina {
private:
    int id = 0;
    int size;
    int origin[2];
    int destiny[2];

public:
    Pagina() {;};
    Pagina(int size, int origen[2], int dest[2]) {
        id++;
        this->size = size;
        this->origin[0] = origin[0];
        this->origin[1] = origin[1];
        this->destiny[0] = destiny[0];
        this->destiny[1] = destiny[1];
    };
    //~Pagina();
    int getId() { return id; };
    int* getDest() { return destiny; };
    int* getOrigin() { return origin; };
    int getSize() { return size; };
};

#endif
