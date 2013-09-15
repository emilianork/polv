#include "transport/polv_tcp.h"

#include "tools/polv_tools.h"
#include "tools/polv_next_layer.h"

#include <cstdlib>

struct polv_tcp* polv_tcp_init()
{

	struct polv_tcp* tcp;
	tcp = (struct polv_tcp*) malloc(sizeof(struct polv_tcp));

	tcp->src_port = tcp->dst_port = tcp->seq = tcp->ack = tcp->offset = 
		tcp->reserved = tcp->flags = tcp->window = tcp->checksum = tcp->urgent =
		tcp->options = NULL;

	return tcp;

}

void polv_tcp_destroy(struct polv_tcp* tcp)
{
	free((u_char*)tcp->src_port);
	free((u_char*)tcp->dst_port);
	free((u_char*)tcp->seq);
	free((u_char*)tcp->ack);
	free((u_char*)tcp->offset);
	free((u_char*)tcp->reserved);
	free((u_char*)tcp->flags);
	free((u_char*)tcp->window);
	free((u_char*)tcp->checksum);
	free((u_char*)tcp->urgent);
	free((u_char*)tcp->options);
	
	free(tcp);

	return;
}

const u_char* polv_tcp_src_port(const u_char* packet) 
{
	return NULL;
}

const u_char* polv_tcp_dst_port(const u_char* packet)
{
	return NULL;
}

const u_char* polv_tcp_seq(const u_char* packet)
{
	return NULL;
}

const u_char* polv_tcp_ack(const u_char* packet)
{
	return NULL;
}

const u_char* polv_tcp_offset(const u_char* packet)
{
	return NULL;
}

const u_char* polv_tcp_reserved(const u_char* packet)
{
	return NULL;
}

const u_char* polv_tcp_flags(const u_char* packet)
{
	return NULL;
}

const u_char* polv_tcp_window(const u_char* packet)
{
	return NULL;
}

const u_char* polv_tcp_checksum(const u_char* packet)
{
	return NULL;
}

const u_char* polv_tcp_urgent(const u_char* packet)
{
	return NULL;
}

const u_char* polv_tcp_options(const u_char* packet)
{
	return NULL;
}

struct next_layer* polv_tcp_data(const u_char* packet, int len)
{
	return NULL;
}

