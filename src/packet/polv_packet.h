/*
  José Emiliano Cabrera Blancas
  Diego Andrés Gómez Montesinos 
  
  Encabezado para describir los paquetes de polv.
*/

#ifndef POLV_PACKET_H_
#define POLV_PACKET_H_

#include "tools/polv_types.h"

#include "data_link/polv_data_link.h"
#include "network/polv_network.h"
#include "transport/polv_transport.h"
#include <ctime>

/*Estructura que representa un paquete capturado */
struct polv_packet {
	struct polv_data_link* data_link;
	struct polv_network* network;
	struct polv_transport* transport;
	const u_char* raw_data;
	int raw_data_len;
	const u_char* raw_packet;
	int raw_packet_len;
};

/* Funciones para destruir y crear la estructura */
void polv_packet_destroy(struct polv_packet*);
struct polv_packet* polv_packet_create(const u_char*, int);

#endif POLV_PACKET_H_
