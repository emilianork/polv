/*
  José Emiliano Cabrera Blancas
  Diego Andrés Gómez Montesinos 
  
  Estructura que representa el protocolo ICMP
*/


#ifndef POLV_ICMP_H_
#define POLV_ICMP_H_

#include "tools/polv_types.h"
#include "tools/polv_next_layer.h"

/* Macros de posicion de datos */
#define TYPE_ICMP 0
#define CODE_ICMP 1
#define CHECKSUM_ICMP 2
#define DATA_ICMP 4

/* Macros de longitud de los datos */
#define TYPE_ICMP_LEN 1
#define CODE_ICMP_LEN 1
#define CHECKSUM_ICMP_LEN 2

/* Estructura para describir el protocolo ICMP*/
struct polv_icmp {
	const u_char* type;
	const u_char* code;
	const u_char* checksum;
};

/*Funciones para inicializar y destruir esta estructura */
struct polv_icmp* polv_icmp_init();
void polv_icmp_destroy(struct polv_icmp*);

/*Funciones para obtener los valores requeridos, a partir del encabezado
  solo de transporte, sin el encabezado de red*/
const u_char* polv_icmp_type(const u_char*);
const u_char* polv_icmp_code(const u_char*);
const u_char* polv_icmp_checksum(const u_char*);

/* Funcion para obtener los datos del protocolo de transporte */
void polv_icmp_data(struct polv_next_layer*);

#endif POLV_ICMP_H_
