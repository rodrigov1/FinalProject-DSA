#include <string>
#include "Cola.h"

using namespace std;

class Router {
    private:
    byte id;
    byte terminal;

    public:
    Router(int id, int terminal){this->id = byte(id); this->terminal = byte(terminal);};
    //~Router();
    void setId();
    byte getId();
    
};
