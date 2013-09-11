#ifndef POLV_TRANSPORT_H
#define POLV_TRANSPORT_H_

#include "tools/polv_types.h"

enum polv_trans_protocol {
	TCP,
	UDP,
	ICMP
};

struct udp {
	const u_char* src_port;
	const u_char* dst_port;
	const u_char* len;
	const u_char* checksum;
};


struct tcp {
	const u_char* src_port;
	const u_char* dst_port;
	const u_char* seq;
	const u_char* ack;
	const u_char* offset;
	const u_char* reserved;
	const u_char* flags;
	const u_char* window;
	const u_char* checksum;
	const u_char* urgent;
	const u_char* options;

};

struct icmp {
	const u_char* type;
	const u_char* code;
	const u_char* checksum;
	const u_char* identifier;
	const u_char* seq;
	const u_char* data;
};

struct polv_transport {
	enum polv_trans_protocol protocol;
	void* header;
};

struct polv_transport* polv_transport_init();
void polv_transport_destroy(struct polv_transport*);


/* @param  El paquete ip o arp, sin la cabecera de ethernet.
   @return La cabecera de la capa de transporte */
//const u_char* polv_transport_head(const u_char*);

/* @param    Cabezera de la capa de transporte.
   @ return  El protocolo de la capa de transporte.
 regresa el protocolo de la capa de transporte */
//enum polv_trans_protocol polv_transport_protocol(const u_char*);

#endif POLV_TRANSPORT_H_
