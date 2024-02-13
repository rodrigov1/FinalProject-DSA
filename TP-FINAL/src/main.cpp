#include "../include/Administrador.h"

#define BLUE "\033[36;1m"
#define PURPLE "\033[35;1m"
#define RESET_COLOR "\x1b[0m"

int main() {
	Administrador *admin = new Administrador();
	admin->leer_config();
	int opcion = 1;
	int crear = 1;

	while (opcion == 1) {
		admin->generate_network();
		if (crear == 1) {
			admin->administrar_paginas();
			admin->administrar_paginas();
			admin->administrar_paginas();
			admin->administrar_paginas();
			crear = 0;
		}
		cout << BLUE << "----------- ENVIO DE PAQUETES ------------" << RESET_COLOR << endl;
		admin->send_packets();
		cout << BLUE << "--------- RECEPCION DE PAQUETES ----------" << RESET_COLOR << endl;
		admin->receive_packets();
		cout << PURPLE << "------- ¿DESEA REPETIR EL PROCESO? -------" << RESET_COLOR << endl;
		cout << "1. SI" << endl;
		cout << "0. NO" << endl << endl;
		cin >> opcion;
	}
	return 0;
}
