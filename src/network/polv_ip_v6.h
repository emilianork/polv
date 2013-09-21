/*
  José Emiliano Cabrera Blancas
  Diego Andrés Gómez Montesinos 
  
  Encabezado para describir el protocolo de red IP V6
*/


#include "tools/polv_types.h"

#include "tools/polv_next_layer.h"

/* Macros de posicion de datos */
#define VERSION_V6 0
#define TRAFFIC_CLASS 0 
#define FLOW_LABEL 1
#define PAYLOAD_LEN 4
#define NEXT_HEADER 6
#define HOP_LIMIT 7
#define SRC_ADDR_V6 8
#define DST_ADDR_V6 24

#define VERSION_V6_LEN 1
#define TRAFFIC_CLASS_LEN 1
#define FLOW_LABEL_LEN 3
#define PAYLOAD_LEN_LEN 2
#define NEXT_HEADER_LEN 1
#define HOP_LIMIT_LEN 1
#define SRC_ADDR_V6_LEN 16
#define DST_ADDR_V6_LEN 16

/* Macros de longitud de los datos */
#define IPV6_HEADER_LEN 40

/* Estructura para describir el protocolo ip v6*/
struct polv_ip_v6 {
	const u_char* version;
	const u_char* traffic_class;
	const u_char* flow_label;
	const u_char* payload_len;
	const u_char* next_header;
	const u_char* hop_limit;
	const u_char* src_addr;
	const u_char* dst_addr;
};

/*Funciones para inicializar y destruir esta estructura */
struct polv_ip_v6* polv_ip_v6_init();
void polv_ip_v6_destroy(struct polv_ip_v6*);

/*Funciones para obtener los valores requeridos, a partir del encabezado
  solo de red, sin el encabezado de ethernet*/
const u_char* polv_ip_v6_version(const u_char*);
const u_char* polv_ip_v6_traffic_class(const u_char*);
const u_char* polv_ip_v6_flow_label(const u_char*);
const u_char* polv_ip_v6_payload_len(const u_char*);
const u_char* polv_ip_v6_next_header(const u_char*);
const u_char* polv_ip_v6_hop_limit(const u_char*);
const u_char* polv_ip_v6_src_addr(const u_char*);
const u_char* polv_ip_v6_dst_addr(const u_char*);

/*Funciona para obtener el encabezado de la capa de transporte */
void polv_ip_v6_next_layer(struct polv_next_layer*);
