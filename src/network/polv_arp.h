/*
  José Emiliano Cabrera Blancas
  Diego Andrés Gómez Montesinos 
  
  Estructura que representa el protocolo ARP
*/

#ifndef POLV_ARP_H_
#define POLV_ARP_H_

#include "tools/polv_types.h"

#include "network/polv_network.h"

/* Macros de posicion de los datos */

#define HTYPE 0
#define PTYPE 2
#define HLEN 4
#define PLEN 5
#define OPER 6
#define SHA 8
#define SPA 14
#define THA 18
#define TPA 24

/* Macros de longitud de los datos */
#define HTYPE_LEN 2
#define PTYPE_LEN 2
#define HLEN_LEN 1
#define PLEN_LEN 1
#define OPER_LEN 2
#define SHA_LEN 6
#define SPA_LEN 4
#define THA_LEN 6
#define TPA_LEN 4

#define ARP_HEADER_LEN 28

/* Estructura para describir el protocolo arp*/
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

/*Funciones para inicializar y destruir esta estructura */
struct polv_arp* polv_arp_init();
void polv_arp_destroy(struct polv_arp*);

/*Funciones para obtener los valores requeridos, a partir del encabezado
  solo de red, sin el encabezado de ethernet*/

const u_char* polv_arp_htype(const u_char*);
const u_char* polv_arp_ptype(const u_char*);
const u_char* polv_arp_hlen(const u_char*);
const u_char* polv_arp_plen(const u_char*);
const u_char* polv_arp_oper(const u_char*);
const u_char* polv_arp_sha(const u_char*);
const u_char* polv_arp_spa(const u_char*);
const u_char* polv_arp_tha(const u_char*);
const u_char* polv_arp_tpa(const u_char*);

#endif POLV_ARP_H_
