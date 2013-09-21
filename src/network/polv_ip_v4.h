/*
  José Emiliano Cabrera Blancas
  Diego Andrés Gómez Montesinos 
  
  Encabezado para describir el protocolo de red IP V4
*/

#ifndef POLV_IP_V4_H_
#define POLV_IP_V4_H_

#include "tools/polv_types.h"

#include "tools/polv_next_layer.h"

/* Macros de posicion de datos */
#define VERSION 0
#define IHL 0
#define TYPE_SERVICE 1
#define LEN 2
#define IDENTIFICATION 4
#define FLAGS 6
#define FRAGMENT_OFFSET 6
#define TIME_TO_LIVE 8
#define PROTOCOL 9 
#define HEADER_CHECK 10
#define SRC_ADDR 12
#define DST_ADDR 16
#define OPTIONS 20

/* Macros de longitud de los datos */
#define VERSION_LEN 1
#define IHL_LEN 1
#define TYPE_SERVICE_LEN 1
#define LEN_LEN 2
#define IDENTIFICATION_LEN 2
#define FLAGS_LEN 1
#define FRAGMENT_OFFSET_LEN 2
#define TIME_TO_LIVE_LEN 1
#define PROTOCOL_LEN 1
#define HEADER_CHECK_LEN 2
#define SRC_ADDR_LEN 4
#define DST_ADDR_LEN 4

/* Estructura para describir el protocolo ip v4*/
struct polv_ip_v4 {
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

/*Funciones para inicializar y destruir esta estructura */
struct polv_ip_v4* polv_ip_v4_init();
void polv_ip_v4_destroy(struct polv_ip_v4*);

/*Funciones para obtener los valores requeridos, a partir del encabezado
  solo de red, sin el encabezado de ethernet*/
const u_char* polv_ip_v4_version(const u_char*);
const u_char* polv_ip_v4_ihl(const u_char*);
const u_char* polv_ip_v4_type_service(const u_char*);
const u_char* polv_ip_v4_len(const u_char*);
const u_char* polv_ip_v4_identification(const u_char*);
const u_char* polv_ip_v4_flags(const u_char*);
const u_char* polv_ip_v4_fragment_offset(const u_char*);
const u_char* polv_ip_v4_time_to_live(const u_char*);
const u_char* polv_ip_v4_protocol(const u_char*);
const u_char* polv_ip_v4_header_check(const u_char*);
const u_char* polv_ip_v4_src_addr(const u_char*);
const u_char* polv_ip_v4_dst_addr(const u_char*);
const u_char* polv_ip_v4_options(const u_char*, u_char ihl);

/*Funciona para obtener el encabezado de la capa de transporte */
void polv_ip_v4_next_layer(struct polv_next_layer*);

#endif POLV_IP_V4_H_
