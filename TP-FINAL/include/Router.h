#include <string>
#include "Cola.h"
#include "Paquetes.h"

using namespace std;

class Router {
private:
    byte id;
    byte terminal;
    Cola<Paquetes*> incomingPackages;
    Cola<Paquetes*> outgoingPackages;

public:
    Router(int id, int terminal) {
        this->id = byte(id); 
        this->terminal = byte(terminal);
        };
    //~Router();
    void setId();
    byte getId();
    
};
