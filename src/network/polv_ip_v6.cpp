#include "network/polv_ip_v6.h"

#include "tools/polv_tools.h"

#include <cstdlib>

struct polv_ip_v6* polv_ip_v6_init()
{
	struct polv_ip_v6* ip;

	ip = (struct polv_ip_v6*) malloc(sizeof(struct polv_ip_v6));

	ip->version = ip->traffic_class = ip->flow_label = ip->payload_len = 
		ip->next_header = ip->hop_limit = ip->src_addr = ip->dst_addr = NULL;

	return ip;
}

void polv_ip_v6_destroy(struct polv_ip_v6* ip)
{

	free((u_char*)ip->version);
	free((u_char*)ip->traffic_class);
	free((u_char*)ip->flow_label);
	free((u_char*)ip->payload_len);
	free((u_char*)ip->next_header);
	free((u_char*)ip->hop_limit);
	free((u_char*)ip->src_addr);
	free((u_char*)ip->dst_addr);

	free(ip);

	return;
}

const u_char* polv_ip_v6_version(const u_char* packet)
{
	u_char* version;
	u_char mask = 15;
	version = (u_char*)polv_oct(VERSION_V6,VERSION_V6_LEN,packet);
	
	version[0] = version[0] >> 4;
	version[0] = version[0] & mask;
	
	return ((const u_char*)version);
}

const u_char* polv_ip_v6_traffic_class(const u_char* packet)
{
	u_char* traffic_class;
	u_char 	mask = 240;
	u_char traffic;

	traffic_class = (u_char*) polv_oct(TRAFFIC_CLASS,TRAFFIC_CLASS_LEN,packet);
	traffic_class[0] = traffic_class[0] << 4;
	traffic_class[0] = traffic_class[0] & mask;

	mask = 15;
	traffic_class[1] = traffic_class[1] >> 4;
	traffic_class[1] = traffic_class[1] & mask;

	traffic = traffic_class[0] | traffic_class[1];
	
	free(traffic_class);
	
	traffic_class = (u_char*) malloc(sizeof(u_char));

	traffic_class[0] = traffic;

	return ((const u_char*)traffic_class);
}

const u_char* polv_ip_v6_flow_label(const u_char* packet)
{
    u_char* flow_label;
	u_char mask = 15;
	
	flow_label = (u_char*) polv_oct(FLOW_LABEL,FLOW_LABEL_LEN,packet);

	flow_label[0] = flow_label[0] & mask;
	
	return ((const u_char*)flow_label);
}

const u_char* polv_ip_v6_payload_len(const u_char* packet)
{
	const u_char* payload_len;
	payload_len = polv_oct(PAYLOAD_LEN,PAYLOAD_LEN_LEN,packet);

	return payload_len;
}

const u_char* polv_ip_v6_next_header(const u_char* packet)
{
	const u_char* next_header;
    next_header = polv_oct(NEXT_HEADER,NEXT_HEADER_LEN,packet);

	return next_header;
}

const u_char* polv_ip_v6_hop_limit(const u_char* packet)
{
	const u_char* hop_limit;
	hop_limit = polv_oct(HOP_LIMIT,HOP_LIMIT_LEN,packet);
	
	return hop_limit;
}

const u_char* polv_ip_v6_src_addr(const u_char* packet)
{
	const u_char* src_addr;
	src_addr = polv_oct(SRC_ADDR_V6,SRC_ADDR_V6_LEN,packet);
	
	return src_addr;
}

const u_char* polv_ip_v6_dst_addr(const u_char* packet)
{
	const u_char* dst_addr;
	dst_addr = polv_oct(DST_ADDR_V6,DST_ADDR_V6_LEN,packet);
	
	return dst_addr;
}
