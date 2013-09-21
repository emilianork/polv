/*
  José Emiliano Cabrera Blancas
  Diego Andrés Gómez Montesinos 
  
  Implementacion de las funciones del encabezado con el mismo nombre.
*/


#include "transport/polv_icmp.h"

#include "tools/polv_tools.h"
#include "tools/polv_next_layer.h"

#include <cstdlib>

struct polv_icmp* polv_icmp_init()
{
	struct polv_icmp* icmp;
	icmp = (struct polv_icmp*) malloc(sizeof(struct polv_icmp));
	
	icmp->type = icmp->code = icmp->checksum = NULL;

	return icmp;
}

void polv_icmp_destroy(struct polv_icmp* icmp)
{
	free((u_char*)icmp->type);
	free((u_char*)icmp->code);
	free((u_char*)icmp->checksum);
	
	free(icmp);
	
	return;
}

const u_char* polv_icmp_type(const u_char* packet)
{
	const u_char* type;
	type = polv_oct(TYPE_ICMP,TYPE_ICMP_LEN,packet);
	
	return type;
}

const u_char* polv_icmp_code(const u_char* packet)
{
	const u_char* code;
	code = polv_oct(CODE_ICMP,CODE_ICMP_LEN,packet);

	return code;
}

const u_char* polv_icmp_checksum(const u_char* packet)
{
	const u_char* checksum;
	checksum = polv_oct(CHECKSUM_ICMP,CHECKSUM_ICMP_LEN,packet);
	
	return checksum;
}

void polv_icmp_data(struct polv_next_layer* next_layer)
{
	const u_char* packet = next_layer->packet;
	int len = next_layer->len;
	
	if (len == DATA_ICMP) {
		free((u_char*)next_layer->packet);
		next_layer->packet = NULL;
		next_layer->len = 0;
		return;
	}
	
	const u_char* data;
	data = polv_oct(DATA_ICMP,len - DATA_ICMP, packet);
	
	free((u_char*)packet);
	
	next_layer->packet = data;
	next_layer->len = len - DATA_ICMP;

	return;
}
