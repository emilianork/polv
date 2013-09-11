#include "packet/polv_packet.h"

#include <cstdlib>
#include <iostream>

using namespace std;

struct polv_packet* polv_packet_init()
{
	struct polv_packet *packet;

	struct polv_data_link* data_link;
	struct polv_network* network;
	struct polv_transport* transport;

	packet = (struct polv_packet*) malloc(sizeof(struct polv_packet));

	if (packet == NULL) {
		cout << "\nNo se encontro memoria disponible." << endl;
		exit(EXIT_FAILURE);
	}
		

	data_link = polv_data_link_init();
	network = polv_network_init();
	transport = polv_transport_init();

	packet->data_link = data_link;
	packet->network = network;
	packet->transport = transport;
	
	return packet;
}

void polv_packet_destroy(struct polv_packet* packet)
{
	polv_data_link_destroy(packet->data_link);
	polv_network_destroy(packet->network);
	free(packet);
}
