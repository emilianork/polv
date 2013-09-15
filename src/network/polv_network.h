#ifndef POLV_NETWORK_H_
#define POLV_NETWORK_H_

#include "tools/polv_types.h"
#include "tools/polv_next_layer.h"

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

struct polv_arp* polv_arp_analyze(const u_char*);
struct polv_ip_v4* polv_ip_v4_analyze(const u_char*);
struct polv_ip_v6* polv_ip_v6_analyze(const u_char*);

/* @param   El paquete que me entregan de la capa de enlace
   @return  El paquete de la capa de transporte */
struct polv_next_layer* polv_transport_packet(const u_char*,
											  enum polv_net_protocol,int len);


#endif POLV_DATA_LINK_H_
