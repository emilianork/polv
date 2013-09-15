#ifndef POLV_NETWORK_H_
#define POLV_NETWORK_H_

#include "tools/polv_types.h"

enum polv_net_protocol {
	IPV4,
	IPV6,
	ARP,
	UNKNOWN_NET
};

struct polv_network {
	enum polv_net_protocol protocol;
	void* header;
};

struct polv_network* polv_network_init();
void polv_network_destroy(struct polv_network*);

/*
  @param   Cabecera de la capa de red.
  @return  El protocolo de la capa de red utilizado.
  
 */
enum polv_net_protocol polv_network_protocol(const u_char*);

/* @param   El paquete que me entrega libpcap
   @return  La cabecera de la capa de red */
//const u_char* polv_network_head(const u_char*, );


#endif POLV_DATA_LINK_H_
