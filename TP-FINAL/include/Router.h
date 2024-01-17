#include <string>
#include "Cola.h"
#include "Packages.h"

using namespace std;

class Router {
    private:
    byte id;
    byte terminal;
    Cola<Packages*> incomingPackages;
    Cola<Packages*> outgoingPackages;

    public:
    Router(int id, int terminal) {
        this->id = byte(id); 
        this->terminal = byte(terminal);
        };
    //~Router();
    void setId();
    byte getId();
    
};
