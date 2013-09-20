#include "packet/polv_packet.h"

#include "tools/polv_tools.h"
#include "tools/polv_next_layer.h"
#include "tools/polv_types.h"

#include "network/polv_arp.h"
#include "network/polv_ip_v4.h"
#include "network/polv_ip_v6.h"

#include <cstdlib>
#include <iostream>

using namespace std;

struct polv_packet* polv_packet_init();

struct polv_data_link* polv_data_link_layer_init(const u_char*);

struct polv_network* polv_network_layer_init(const u_char*, const u_char*);

struct polv_transport* polv_transport_layer_init(const u_char*,
												 const u_char*);

struct polv_packet* polv_packet_init()
{
	struct polv_packet *packet;

	packet = (struct polv_packet*) malloc(sizeof(struct polv_packet));

	if (packet == NULL) {
		cout << "\nNo se encontro memoria disponible." << endl;
		exit(EXIT_FAILURE);
	}

	packet->data_link = NULL;
	packet->network = NULL;
	packet->transport = NULL;
	packet->raw_packet = NULL;
	packet->raw_data = NULL;
	
	return packet;
}

void polv_packet_destroy(struct polv_packet* packet)
{
	if (packet->data_link != NULL)
		polv_data_link_destroy(packet->data_link);
	if (packet->network != NULL)
		polv_network_destroy(packet->network);
	if (packet->transport != NULL)
		polv_transport_destroy(packet->transport);
	
	free((u_char*)packet->raw_data);

	free((u_char*)packet->raw_packet);
	free(packet);
}

struct polv_packet* polv_packet_create(const u_char* raw_packet, int len)
{
	struct polv_packet* packet;
	struct polv_data_link* data_link;
	struct polv_network* network;
	struct polv_transport* transport;

	packet = polv_packet_init();

	packet->raw_packet = polv_oct(0,len,raw_packet);
	packet->raw_packet_len = len;

	data_link = polv_data_link_layer_init(raw_packet);
	
	/* El protocolo de enlace, no fue reconocido. */
	if (data_link == NULL)
		return packet;
	
	packet->data_link = data_link;
	
	struct polv_next_layer* next_layer;
	next_layer = polv_next_layer_init();
	
	polv_network_packet(raw_packet,next_layer,data_link->type,len);
	
	network = polv_network_layer_init(next_layer->packet,
									  data_link->ethertype);

	packet->network = network;

	/* Si no reconoce la capa de red, entonces regresa NULL*/
	if (network == NULL)
		return packet;

	/* Dado que ARP y RARP es un protocolo que tiene funcionalidad hasta la capa
	 de red, la capa de transporte ya ni importa. */
	if ((network->protocol == ARP) || (network->protocol == RARP)) 
		return packet;
	
	polv_transport_packet(next_layer,network->protocol);

	switch(network->protocol) {
	case IPV4:
		struct polv_ip_v4* ip_v4;
		ip_v4 = (struct polv_ip_v4*)network->header;
		transport = polv_transport_layer_init(next_layer->packet,ip_v4->protocol);
		break;
	case IPV6:
		struct polv_ip_v6* ip_v6;
		ip_v6 = (struct polv_ip_v6*)network->header;
		transport = polv_transport_layer_init(next_layer->packet,
											  ip_v6->next_header);
		break;
	}

	packet->transport = transport;
	
	if (transport == NULL) 
		return packet;

	polv_transport_data(transport,next_layer);
	
	packet->raw_data = next_layer->packet;
	packet->raw_data_len = next_layer->len;

	return packet;
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
	case RARP:
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

struct polv_transport* polv_transport_layer_init(const u_char* packet,
												 const u_char* prot)
{
	enum polv_trans_protocol protocol;
	protocol = polv_transport_protocol(prot);

	if (protocol == UNKNOWN_TRANS)
		return NULL;
	
	struct polv_transport* transport;
	transport = polv_transport_init();
	
	transport->protocol = protocol;

	switch(protocol) {
	case TCP:
		transport->header = (void *)polv_tcp_analyze(packet);
		return transport;
	case UDP:
		transport->header = (void *)polv_udp_analyze(packet);
		return transport;
	case ICMP:
		transport->header = (void *)polv_icmp_analyze(packet);
		return transport;
	}
}
