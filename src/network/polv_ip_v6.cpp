#include "network/polv_ip_v6.h"

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

