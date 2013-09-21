/*
  José Emiliano Cabrera Blancas
  Diego Andrés Gómez Montesinos 
  
  Implementacion de las funciones del encabezado con el mismo nombre.
*/

#include "transport/polv_transport.h"

#include <cstdlib>
#include <iostream>

using namespace std;

u_char icmp = 1;
u_char tcp = 6;
u_char udp = 17;
u_char icmpv6 = 58;

struct polv_transport* polv_transport_init()
{
	struct polv_transport* transport;

	transport = (struct polv_transport*) malloc(sizeof(struct polv_transport));

	if (transport == NULL) {
		cout << "\nNo se encontro memoria disponible." << endl;
		exit(EXIT_FAILURE);
	}

	transport->header = NULL;

	return transport;
}

void polv_transport_destroy(struct polv_transport* transport)
{
	switch(transport->protocol) {
	case TCP:
		struct polv_tcp* tcp;
		tcp = (struct polv_tcp*)transport->header;
		polv_tcp_destroy(tcp);
		break;
	case UDP:
		struct polv_udp* udp;
		udp = (struct polv_udp*)transport->header;
		polv_udp_destroy(udp);
		break;
	case ICMP:
		struct polv_icmp* icmp;
		icmp = (struct polv_icmp*)transport->header;
		polv_icmp_destroy(icmp);
		break;
	}
}

enum polv_trans_protocol polv_transport_protocol(const u_char* protocol)
{
	if ((icmp == protocol[0]) || (icmpv6 == protocol[0]))
		return ICMP;
	
	if (tcp == protocol[0])
		return TCP;

	if (udp == protocol[0])
		return UDP;

	return UNKNOWN_TRANS;
}

struct polv_tcp* polv_tcp_analyze(const u_char* packet)
{
	struct polv_tcp* tcp;
	tcp = polv_tcp_init();

	tcp->src_port = polv_tcp_src_port(packet);
	tcp->dst_port = polv_tcp_dst_port(packet);
	tcp->seq = polv_tcp_seq(packet);
	tcp->ack = polv_tcp_ack(packet);
	tcp->offset = polv_tcp_offset(packet);
	tcp->reserved = polv_tcp_reserved(packet);
	tcp->flags = polv_tcp_flags(packet);
	tcp->window = polv_tcp_window(packet);
	tcp->checksum = polv_tcp_checksum(packet);
	tcp->urgent = polv_tcp_urgent(packet);
	tcp->options = polv_tcp_options(packet);

	return tcp;
}

struct polv_udp* polv_udp_analyze(const u_char* packet)
{
	struct polv_udp* udp;
	udp = polv_udp_init();
	
	udp->src_port = polv_udp_src_port(packet);
	udp->dst_port = polv_udp_dst_port(packet);
	udp->len = polv_udp_len(packet);
	udp->checksum = polv_udp_checksum(packet);

	return udp;
}

struct polv_icmp* polv_icmp_analyze(const u_char* packet)
{
	struct polv_icmp* icmp;
	icmp = polv_icmp_init();
	
	icmp->type = polv_icmp_type(packet);
	icmp->code = polv_icmp_code(packet);
	icmp->checksum = polv_icmp_checksum(packet);

	return icmp;
}

void polv_transport_data(struct polv_transport* transport,
						 struct polv_next_layer* next_layer)
{
	switch(transport->protocol) {
	case TCP:
		struct polv_tcp* tcp;
		tcp = (struct polv_tcp*)transport->header;
		polv_tcp_data(tcp->offset[0],next_layer);
		break;
	case UDP:
		polv_udp_data(next_layer);
		break;
	case ICMP:
		polv_icmp_data(next_layer);
		break;
	}
}
