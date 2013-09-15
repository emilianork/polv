#ifndef POLV_TRANSPORT_H
#define POLV_TRANSPORT_H_

#include "tools/polv_types.h"

enum polv_trans_protocol {
	TCP,
	UDP,
	ICMP,
	UNKNOWN_TRANS
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
	u_char* message;
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
