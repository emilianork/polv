#include "data_link/polv_data_link.h"

#include "network/polv_network.h"
#include "network/polv_ip_v4.h"
#include "network/polv_ip_v6.h"
#include "network/polv_arp.h"

#include "tools/polv_tools.h"

#include <cstdlib>
#include <iostream>

const u_char arp[2] = {8,6};
const u_char ipv4[2] = {8,0};
const u_char ipv6[2] = {134, 221};
const u_char rarp[2] = {128,53};

using namespace std;

struct polv_network* polv_network_init()
{
	struct polv_network* network;
	
	network = (struct polv_network*) malloc(sizeof(struct polv_network));

	if (network == NULL) {
		cout << "\nNo se encontro memoria disponible." << endl;
		exit(EXIT_FAILURE);
	}

	network->header = NULL;
	return  network;
}

void polv_network_destroy(struct polv_network* network)
{

	if (network != NULL)
		return;

	switch(network->protocol) {
	case IPV4:
		polv_ip_v4_destroy((struct polv_ip_v4*) network->header);
		break;
	case IPV6:
		polv_ip_v6_destroy((struct polv_ip_v6*) network->header);
		break;
	case ARP:
		polv_arp_destroy((struct polv_arp*) network->header);
		break;
	case RARP:
		polv_arp_destroy((struct polv_arp*) network->header);
		break;
	}
	free(network);
}

enum polv_net_protocol polv_network_protocol(const u_char* ethertype)
{
	
	if (polv_compare(arp, ethertype,TYPE_LEN) == 0) 
		return ARP;
	if (polv_compare(rarp, ethertype,TYPE_LEN) == 0)
		return RARP;
	if (polv_compare(ipv4, ethertype,TYPE_LEN) == 0)
		return IPV4;
	if (polv_compare(ipv6, ethertype,TYPE_LEN) == 0)
		return IPV6;
	
	return UNKNOWN_NET;
}

struct polv_arp* polv_arp_analyze(const u_char* packet)
{
	struct polv_arp* arp;
	arp = polv_arp_init();

	arp->htype = polv_arp_htype(packet);
	arp->ptype = polv_arp_ptype(packet);
	arp->hlen = polv_arp_hlen(packet);
	arp->plen = polv_arp_plen(packet);
	arp->oper = polv_arp_oper(packet);
	arp->sha = polv_arp_sha(packet);
	arp->spa = polv_arp_spa(packet);
	arp->tha = polv_arp_tha(packet);
	arp->tpa = polv_arp_tpa(packet);
	
	return arp;
}

struct polv_ip_v4* polv_ip_v4_analyze(const u_char* packet)
{
	struct polv_ip_v4* ip;
	ip = polv_ip_v4_init();

	ip->version = polv_ip_v4_version(packet);
	ip->ihl = polv_ip_v4_ihl(packet);
	ip->type_service = polv_ip_v4_type_service(packet);
	ip->len = polv_ip_v4_len(packet);
	ip->identification = polv_ip_v4_identification(packet);
	ip->flags = polv_ip_v4_flags(packet);
	ip->fragment_offset = polv_ip_v4_fragment_offset(packet);
	ip->time_to_live = polv_ip_v4_time_to_live(packet);
	ip->protocol = polv_ip_v4_protocol(packet);
	ip->header_check = polv_ip_v4_header_check(packet);
	ip->src_addr = polv_ip_v4_src_addr(packet);
	ip->dst_addr = polv_ip_v4_dst_addr(packet);
	ip->options = polv_ip_v4_options(packet,(u_char)ip->ihl[0]);

	return ip;
}

struct polv_ip_v6* polv_ip_v6_analyze(const u_char* packet)
{
	struct polv_ip_v6* ip;
	ip = polv_ip_v6_init();

	ip->version = polv_ip_v6_version(packet);
	ip->traffic_class = polv_ip_v6_traffic_class(packet);
	ip->flow_label = polv_ip_v6_flow_label(packet);
	ip->payload_len = polv_ip_v6_payload_len(packet);
	ip->next_header = polv_ip_v6_next_header(packet);
	ip->hop_limit = polv_ip_v6_hop_limit(packet);
	ip->src_addr = polv_ip_v6_src_addr(packet);
	ip->dst_addr = polv_ip_v6_dst_addr(packet);

	return ip;
}

void polv_transport_packet(struct polv_next_layer* next_layer,
						   enum polv_net_protocol protocol)
{
	switch(protocol) {
	case IPV4:
		polv_ip_v4_next_layer(next_layer);
		break;
	case IPV6:
		polv_ip_v6_next_layer(next_layer);
		break;
	}
}
