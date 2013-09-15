#include "packet/polv_packet.h"

#include "tools/polv_next_layer.h"
#include "tools/polv_types.h"

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

struct polv_data_link* polv_data_link_layer_init(const u_char* packet)
{
	enum polv_ethertype type;
	
	type = polv_ether_ver(packet);

	if (type == UNKNOWN_LINK)
		return NULL;

	struct polv_data_link* data_link;
	data_link = polv_data_link_init();

	data_link->dst = polv_ether_dst(packet);
	data_link->src = polv_ether_src(packet);
	data_link->type = type;
	data_link->ethertype = polv_ethertype(packet,type);
	
	switch (type) {
	case VII:
		return data_link;
	case V802:
		data_link->dsap = polv_dsap(packet);
		data_link->ssap = polv_ssap(packet);
		data_link->control = polv_control(packet);
		data_link->org_code = polv_org_code(packet);
		
		return data_link;
	}
}

struct polv_network* polv_network_layer_init(const u_char* packet,
											 const u_char* ethertype)
{
	enum polv_net_protocol protocol;
	protocol = polv_network_protocol(ethertype);

	if (protocol == UNKNOWN_NET)
		return NULL;

	struct polv_network* network;
	network = polv_network_init();
	
	network->protocol = protocol;
	
	switch(protocol) {
	case ARP:
		network->header = (void *)polv_arp_analyze(packet);
		return network;
	case IPV4:
		network->header = (void *)polv_ip_v4_analyze(packet);
		return network;
	case IPV6:
		network->header = (void *)polv_ip_v6_analyze(packet);
		return network;
	}
}
