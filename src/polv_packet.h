#ifndef POLV_PACKET_H_
#define POLV_PACKET_H_

#include "polv_data_link.h"
#include "polv_network.h"
#include "polv_transport.h"


struct polv_packet {
	struct polv_data_link* data_link;
	struct polv_network* network;
	struct polv_transport* transport;
};


/* Funciones para el manejo de la estructura */
struct polv_packet* polv_packet_init();
void polv_packet_destroy(struct polv_packet*);

#endif POLV_PACKET_H_
