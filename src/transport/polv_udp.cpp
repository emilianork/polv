/*
  José Emiliano Cabrera Blancas
  Diego Andrés Gómez Montesinos 
  
  Implementacion de las funciones del encabezado con el mismo nombre.
*/

#include "transport/polv_udp.h"

#include "tools/polv_tools.h"
#include "tools/polv_next_layer.h"

#include <cstdlib>

struct polv_udp* polv_udp_init()
{
	struct polv_udp* udp;
	udp = (struct polv_udp*) malloc(sizeof(struct polv_udp));

	udp->src_port = udp->dst_port = udp->len = udp->checksum = NULL;

	return udp;
}

void polv_udp_destroy(struct polv_udp* udp)
{
	free((u_char*) udp->src_port);
	free((u_char*) udp->dst_port);
	free((u_char*) udp->len);
	free((u_char*) udp->checksum);
	
	free(udp);
	return;
}

const u_char* polv_udp_src_port(const u_char* packet)
{
	const u_char* src_port;
	src_port = polv_oct(SRC_PORT_UDP,SRC_PORT_UDP_LEN,packet);

	return src_port;
}

const u_char* polv_udp_dst_port(const u_char* packet)
{
	const u_char* dst_port;
	dst_port = polv_oct(DST_PORT_UDP,DST_PORT_UDP_LEN,packet);

	return dst_port;	
}

const u_char* polv_udp_len(const u_char* packet)
{
	const u_char* len;
	len = polv_oct(LEN_UDP,LEN_UDP_LEN,packet);

	return len;	
}

const u_char* polv_udp_checksum(const u_char* packet)
{
	const u_char* checksum;
	checksum = polv_oct(CHECKSUM_UDP,CHECKSUM_UDP_LEN,packet);

	return checksum;	
}

void polv_udp_data(struct polv_next_layer* next_layer)
{
	const u_char* packet = next_layer->packet;
	int len = next_layer->len;
	
	if (len == DATA_UDP) {
		free((u_char*)next_layer->packet);
		next_layer->packet = NULL;
		next_layer->len = 0;
		return;
	}

	const u_char* data;
	data = polv_oct(DATA_UDP,len - DATA_UDP,packet);
	
	free((u_char*)next_layer->packet);	

	next_layer->packet = data;
	next_layer->len = len - DATA_UDP;

	return;
}
