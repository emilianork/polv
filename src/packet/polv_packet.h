#ifndef POLV_PACKET_H_
#define POLV_PACKET_H_

#include "data_link/polv_data_link.h"
#include "network/polv_network.h"
#include "transport/polv_transport.h"


struct polv_packet {
	struct polv_data_link* data_link;
	struct polv_network* network;
	struct polv_transport* transport;
};


/* Funciones para el manejo de la estructura */
struct polv_packet* polv_packet_init();
void polv_packet_destroy(struct polv_packet*);

struct polv_data_link* polv_data_link_layer_init(const u_char*, int);

#endif POLV_PACKET_H_
