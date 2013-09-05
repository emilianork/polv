#ifndef POLV_NETWORK_H_
#define POLV_NETWORK_H_

#include "polv_types.h"

enum polv_net_protocol {
	IP,
	ARP
};


struct polv_ip {

	const u_char* version;
	const u_char* ihl;
	const u_char* type_service;
	const u_char* len;
	const u_char* identification;
	const u_char* flags;
	const u_char* fragment_offset;
	const u_char* time_to_live;
	const u_char* protocol;
	const u_char* header_check;
	const u_char* src_addr;
	const u_char* dst_addr;
	const u_char* options;
};

struct polv_arp {
	const u_char* htype;
	const u_char* ptype;
	const u_char* hlen;
	const u_char* plen;
	const u_char* oper;
	const u_char* sha;
	const u_char* spa;
	const u_char* tha;
	const u_char* tpa;

};

struct polv_network {
	enum polv_net_protocol protocol;
	void* header;
};

struct polv_network* polv_network_init();
void polv_network_destroy();

/* @param   El paquete capturado con libpcap, 
   @return  La cabecera de la capa de red */
//const u_char* polv_network_head(const u_char*);

/*
  @param   Cabecera de la paca de red.
  @return  El protocolo de la capa de red utilizado.
  
 */
//enum polv_net_protocol polv_network_protocol(const u_char*);

#endif POLV_DATA_LINK_H_
