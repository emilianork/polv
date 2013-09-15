#include "network/polv_ip_v4.h"

#include "tools/polv_tools.h"

#include <cstdlib>

struct polv_ip_v4* polv_ip_v4_init()
{
	struct polv_ip_v4* ip;

	ip = (struct polv_ip_v4*) malloc(sizeof(struct polv_ip_v4));

	ip->version = ip->ihl = ip->type_service = ip->len = ip->identification = 
		ip->flags = ip->fragment_offset = ip->time_to_live = ip->protocol = 
		ip->header_check = ip->src_addr = ip->dst_addr = ip->options = NULL;

	return ip;
}


void polv_ip_v4_destroy(struct polv_ip_v4* ip)
{
	free((u_char*)ip->version);
	free((u_char*)ip->ihl);
	free((u_char*)ip->type_service);
	free((u_char*)ip->len);
	free((u_char*)ip->identification);
	free((u_char*)ip->flags);
	free((u_char*)ip->fragment_offset);
	free((u_char*)ip->time_to_live);
    free((u_char*)ip->protocol);
	free((u_char*)ip->header_check);
	free((u_char*)ip->src_addr);
	free((u_char*)ip->dst_addr);
	free((u_char*)ip->options);
	
	free(ip);

	return;
}

const u_char* polv_ip_v4_version(const u_char* packet)
{
	u_char* version;
	u_char mask = 15;
	version = (u_char*)polv_oct(VERSION,VERSION_LEN,packet);
	
	version[0] = version[0] >> 4;
	version[0] = version[0] & mask;
	
	return ((const u_char*)version);
}

const u_char* polv_ip_v4_ihl(const u_char* packet)
{
	u_char* ihl;
	u_char mask = 15;
	ihl = (u_char*)polv_oct(IHL,IHL_LEN,packet);
	
	ihl[0] = ihl[0] << 4;
	ihl[0] = ihl[0] >> 4;
	ihl[0] = ihl[0] & mask;
	
	return ((const u_char*)ihl);
}

const u_char* polv_ip_v4_type_service(const u_char* packet)
{
	const u_char* type_service;
	type_service = polv_oct(TYPE_SERVICE,TYPE_SERVICE_LEN,packet);

	return type_service;
}

const u_char* polv_ip_v4_len(const u_char* packet)
{
	const u_char* len;
	len = polv_oct(LEN,LEN_LEN,packet);

	return len;
}

const u_char* polv_ip_v4_identification(const u_char* packet)
{
	const u_char* identification;
	identification = polv_oct(IDENTIFICATION,IDENTIFICATION_LEN,packet);

	return identification;
}

const u_char* polv_ip_v4_flags(const u_char* packet)
{
	u_char* flags;
	u_char mask = 7;
	flags =  (u_char*)polv_oct(FLAGS,FLAGS_LEN,packet);
	
	flags[0] = flags[0] >> 5;
	flags[0] = flags[0] & mask;
	
	return flags;
}

const u_char* polv_ip_v4_fragment_offset(const u_char* packet)
{
	u_char* fragment_offset;
	u_char mask = 31;
	fragment_offset =  (u_char*)polv_oct(FRAGMENT_OFFSET,
										FRAGMENT_OFFSET_LEN,packet);

	fragment_offset[0] = fragment_offset[0] & mask;

	return ((const u_char*)fragment_offset);
}

const u_char* polv_ip_v4_time_to_live(const u_char* packet)
{
	const u_char* time_to_live;
    time_to_live = polv_oct(TIME_TO_LIVE,TIME_TO_LIVE_LEN,packet);
	
	return time_to_live;
}

const u_char* polv_ip_v4_protocol(const u_char* packet)
{
	const u_char* protocol;
    protocol = polv_oct(PROTOCOL,PROTOCOL_LEN,packet);
	
	return protocol;
}

const u_char* polv_ip_v4_header_check(const u_char* packet)
{
	const u_char* header_check;
    header_check = polv_oct(HEADER_CHECK,HEADER_CHECK_LEN,packet);
	
	return header_check;
}

const u_char* polv_ip_v4_src_addr(const u_char* packet)
{
	const u_char* src_addr;
    src_addr = polv_oct(SRC_ADDR,SRC_ADDR_LEN,packet);
	
	return src_addr;
}

const u_char* polv_ip_v4_dst_addr(const u_char* packet)
{
	const u_char* dst_addr;
    dst_addr = polv_oct(DST_ADDR,DST_ADDR_LEN,packet);
	
	return dst_addr;
}

const u_char* polv_ip_v4_options(const u_char* packet, u_char ihl)
{
	int len = ihl;
	if (len == 5) {
		return NULL;
	} else {
		const u_char* options;
		options = polv_oct(OPTIONS,(len - 5) * 4,packet);
		
		return options;
	}
}

struct polv_next_layer* polv_ip_v4_next_layer(const u_char* packet, int len)
{
	const u_char* ihl;
	ihl = polv_ip_v4_ihl(packet);
	
	int ihl_value = ihl[0];

	int header_len = ihl_value * 4;
	
	const u_char* transport;
	transport = polv_oct(header_len,len - header_len,packet);
	
	struct polv_next_layer* next_layer;
	next_layer = polv_next_layer_init();

	next_layer->packet = transport;
	next_layer->len = len - header_len;

	return next_layer;
}
