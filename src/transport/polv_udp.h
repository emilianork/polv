/*
  José Emiliano Cabrera Blancas
  Diego Andrés Gómez Montesinos 
  
  Estructura que representa el protocolo UDP
*/

#ifndef POLV_UPD_H
#define POLV_UPD_H

#include "tools/polv_types.h"
#include "tools/polv_next_layer.h"

/* Macros de posicion de datos */
#define SRC_PORT_UDP 0
#define DST_PORT_UDP 2
#define LEN_UDP 4
#define CHECKSUM_UDP 6

#define DATA_UDP 8

/* Macros de longitud de los datos */
#define SRC_PORT_UDP_LEN 2
#define DST_PORT_UDP_LEN 2
#define LEN_UDP_LEN 2
#define CHECKSUM_UDP_LEN 2

/* Estructura para describir el protocolo UDP*/
struct polv_udp {
	const u_char* src_port;
	const u_char* dst_port;
	const u_char* len;
	const u_char* checksum;
};

/*Funciones para inicializar y destruir esta estructura */
struct polv_udp* polv_udp_init();
void polv_udp_destroy(struct polv_udp*);

/*Funciones para obtener los valores requeridos, a partir del encabezado
  solo de transporte, sin el encabezado de red*/
const u_char* polv_udp_src_port(const u_char*);
const u_char* polv_udp_dst_port(const u_char*);
const u_char* polv_udp_len(const u_char*);
const u_char* polv_udp_checksum(const u_char*);

/* Funcion para obtener los datos del protocolo de transporte */
void polv_udp_data(struct polv_next_layer*);
#endif POLV_UPD_H
