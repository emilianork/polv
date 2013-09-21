/*
  José Emiliano Cabrera Blancas
  Diego Andrés Gómez Montesinos 
  
  Estructura que representa la generalizacion de la capa de transporte
*/


#ifndef POLV_TRANSPORT_H
#define POLV_TRANSPORT_H_

#include "tools/polv_types.h"

#include "transport/polv_tcp.h"
#include "transport/polv_udp.h"
#include "transport/polv_icmp.h"

enum polv_trans_protocol {
	TCP,
	UDP,
	ICMP,
	UNKNOWN_TRANS
};

struct polv_transport {
	enum polv_trans_protocol protocol;
	void* header;
};

/* Funciones para la inicializacion y destruccion de la estructura */
struct polv_transport* polv_transport_init();
void polv_transport_destroy(struct polv_transport*);

/* @param    Protocolo que indica en la cabecera de red
   @ return  El protocolo de la capa de transporte.
 regresa el protocolo de la capa de transporte */
enum polv_trans_protocol polv_transport_protocol(const u_char*);

/*Funciones para analizar y crear el header, de la capa de red.*/
struct polv_tcp* polv_tcp_analyze(const u_char*);
struct polv_udp* polv_udp_analyze(const u_char*);
struct polv_icmp* polv_icmp_analyze(const u_char*);

void polv_transport_data(struct polv_transport*,struct polv_next_layer*);

#endif POLV_TRANSPORT_H_
