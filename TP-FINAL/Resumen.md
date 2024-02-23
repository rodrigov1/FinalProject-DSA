# CONSIGNA DESGLOZADA

# Pagina 

## Creacion
- [x] Se deben generar un numero aleatorio de páginas que llegan a cada terminal 
  - Esto se soluciona con la funcion random() en **Admin::administrar_pagina()**
- [x] El origen, destino y el tamaño de la página tienen que ser aleatorios
  - Lo mismo que el caso anterior
- [x] Cuando se envia una pagina de una terminal, se envia de a segmentos llamados paquetes


# Router 

## Creacion
- [x] Se pueden crear un maximo de 256 routers 
- [x] Cada router esta conectado a uno o más routers, llamados **routers vecinos**
- [x] Cada router tiene un numero "k" de terminales, donde k <= 256 ya que la IP es de 1 byte

## Recepcion de paquetes 
- [x] Debe ir almacenando los paquetes recibidos hasta que se complete la pagina y 
  recien ahi enviar a la terminal 
- [x] Cuando un router recibe paquetes de otro router (mediante el canal correspondiente)
  debe reenviarlo al router siguiente en la ruta

## Envio de paquetes 
- [x] Si la direccion del paquete corresponde a la de un router vecino, hay una
  conexion directa, por lo que no hay mas tramite.
- [x] Para routers que no son vecinos pueden haber varias rutas alternativas, debiendo el router 
  elegir aquella que tiene la menor carga de trafico. Una vez determinada la mejor ruta, 
  todos los paquetes se envian al router vecino que conforma el camino elegido


# Terminal 

## Creacion 

# Administrador
- [ ]  Existe un administrador del sistema que recomputa las rutas optimas de todos los routers periodicamente (cada 2).
  Para ello cada router le envia el tamano de la cola de espera de envios de paquetes hacia cada router vecino, y 
  con ello el administrador determina la ruta optima pasando por los routers que tengan menor trafico pendiente en 
  relacion al ancho de banda de la conexi´on que tenga con ese router.
  - Esto se resuelve en generate_network() y posteriormente en Router::send_packet()


# Fixing bugs
- [x] Fix the calculation of peso in each canal
- [x] Print the pages arrived in each terminal in all routers
- [x] Fix the counting packets in recepcion de paquetes
- [x] Debugg the best_route election in Router::send_packet() q parte de Administrador::generate_network()
- [ ] Revisar el makefile, explicarlo un poco más si hace falta
- [ ] Revisar todo lo relacionado a dijkstra  



solace = consuelo
hassle = problema, molestia
bestow =
