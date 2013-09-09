#include "polv_ip_v4.h"

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
