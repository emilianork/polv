/*
  José Emiliano Cabrera Blancas
  Diego Andrés Gómez Montesinos 
  
  Estructura que representa la generalizacion de la capa red
*/

#ifndef POLV_NETWORK_H_
#define POLV_NETWORK_H_

#include "tools/polv_types.h"
#include "tools/polv_next_layer.h"

enum polv_net_protocol {
	IPV4,
	IPV6,
	ARP,
	RARP,
	UNKNOWN_NET
};

struct polv_network {
	enum polv_net_protocol protocol;
	void* header;
};

/* Funciones para la inicializacion y destruccion de la estructura */
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
void polv_transport_packet(struct polv_next_layer*,enum polv_net_protocol);


#endif POLV_NETWORK_H_
