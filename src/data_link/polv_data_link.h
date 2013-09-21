/*
  José Emiliano Cabrera Blancas
  Diego Andrés Gómez Montesinos 
  
  Encabezado para modelar la capa de enlace
*/

#ifndef POLV_DATA_LINK_H_
#define POLV_DATA_LINK_H_

#include "tools/polv_types.h"
#include "tools/polv_next_layer.h"

/* Macros para las funciones*/
#define MAC_ADDRESS 6
#define TYPE_LEN 2
#define DSAP_LEN 1
#define SSAP_LEN 1
#define CONTROL_LEN 2
#define ORG_CODE_LEN 2

#define DST 0
#define SRC 6
#define TYPE 12
#define DSAP 14
#define SSAP 15
#define CONTROL 16
#define ORG_CODE 18
#define ETHERTYPE 20
#define DATA 22

enum polv_ethertype {
	VII,
	V802,
	UNKNOWN_LINK
};

/* Estructura para representar ambos protocolos 802 y vII */
struct polv_data_link {
	const u_char *dst;
	const u_char *src;
	enum polv_ethertype type;
	const u_char *ethertype;
	const u_char *dsap;
	const u_char *ssap;
	const u_char *control;
	const u_char *org_code;
};

/* Funciones para inicializar y destruir struct 
   polv_data_link */
struct polv_data_link* polv_data_link_init();
void polv_data_link_destroy(struct polv_data_link*);

/* Funciones para obtener los datos del encabezado MAC*/
/* @param  El paquete capturado con libpcap */
/* @return La cadena solicitada*/

const u_char* polv_ether_dst(const u_char*);
const u_char* polv_ether_src(const u_char*);
enum polv_ethertype polv_ether_ver(const u_char*);
const u_char* polv_ethertype(const u_char*, enum polv_ethertype);
const u_char* polv_dsap(const u_char*);
const u_char* polv_ssap(const u_char*);
const u_char* polv_control(const u_char*);
const u_char* polv_org_code(const u_char*);

/* Función para obtener el encabezado de la siguiente capa */
void polv_network_packet(const u_char*, struct polv_next_layer*,
						 enum polv_ethertype, int);

#endif POLV_DATA_LINK_H_
