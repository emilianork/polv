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
	const u_char* src_port;
	src_port = polv_oct(SRC_PORT_TCP,SRC_PORT_TCP_LEN,packet);

	return src_port;
}

const u_char* polv_tcp_dst_port(const u_char* packet)
{
	const u_char* dst_port;
	dst_port = polv_oct(DST_PORT_TCP,DST_PORT_TCP_LEN,packet);

	return dst_port;
}

const u_char* polv_tcp_seq(const u_char* packet)
{
	const u_char* seq;
	seq = polv_oct(SEQ_TCP,SEQ_TCP_LEN,packet);
	
	return seq;
}

const u_char* polv_tcp_ack(const u_char* packet)
{
	const u_char* ack;
	ack = polv_oct(ACK_TCP,ACK_TCP_LEN,packet);

	return ack;
}

const u_char* polv_tcp_offset(const u_char* packet)
{
	u_char* offset;
	u_char mask = 15;
	
	offset = (u_char*)polv_oct(OFFSET_TCP,OFFSET_TCP_LEN,packet);

	offset[0] = offset[0] >> 4;
	offset[0] = offset[0] & mask;

	return ((const u_char*)offset);
}

const u_char* polv_tcp_reserved(const u_char* packet)
{
	u_char* reserved;
	u_char mask = 7;

	reserved = (u_char*)polv_oct(RESERVED_TCP,RESERVED_TCP_LEN,packet);

	reserved[0] = reserved[0] >> 1;
	reserved[0] = reserved[0] & mask;

	return ((const u_char*)reserved);
}

const u_char* polv_tcp_flags(const u_char* packet)
{
	u_char* flags;
	u_char mask = 1;

	flags = (u_char*) polv_oct(FLAGS_TCP,FLAGS_TCP_LEN,packet);
	flags[0] = flags[0] & mask;

	return ((const u_char*) flags);
}

const u_char* polv_tcp_window(const u_char* packet)
{
	const u_char* window;
	window = polv_oct(WINDOW_TCP,WINDOW_TCP_LEN,packet);

	return window;
}

const u_char* polv_tcp_checksum(const u_char* packet)
{
	const u_char* checksum;
	checksum = polv_oct(CHECKSUM_TCP,CHECKSUM_TCP_LEN,packet);
	
	return checksum;
}

const u_char* polv_tcp_urgent(const u_char* packet)
{
	const u_char* urgent;
	urgent = polv_oct(URGENT_TCP,URGENT_TCP_LEN,packet);
	
	return urgent;
}

const u_char* polv_tcp_options(const u_char* packet)
{
	u_char* offset = (u_char*) polv_tcp_offset(packet);
	int len = offset[0];

	if (len == 5) 
		return NULL;

	const u_char* options;
	options = polv_oct(OPTIONS_TCP,(len - 5) * 4, packet);
	
	return options;
	
}

struct polv_next_layer* polv_tcp_data(const u_char* packet,u_char offset, int len)
{
	int header_len = offset * 4;
	
	if (header_len == len)
		return NULL;
	
	struct polv_next_layer* next_layer;
	next_layer = polv_next_layer_init();
	
	next_layer->packet = polv_oct(header_len, len - header_len, packet);
	next_layer->len = len - header_len;

	return next_layer;
}

