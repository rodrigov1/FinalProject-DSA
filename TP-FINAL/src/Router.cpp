#include <iostream>
#include <string>
#include "../include/Router.h"
#include "../include/Lista.h"
#include "../include/Cola.h"
#include "../include/Pagina.h"
#include "../include/Terminal.h"

using namespace std;

void Router::add_terminal(Terminal *t)
{
    terminals_conectados->add(t);
}