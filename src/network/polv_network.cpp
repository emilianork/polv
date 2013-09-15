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

	switch(network->protocol) {
	case IPV4:
		polv_ip_v4_destroy((struct polv_ip_v4*) network->header);
		break;
	case IPV6:
		polv_ip_v6_destroy((struct polv_ip_v6*) network->header);
	case ARP:
		polv_arp_destroy((struct polv_arp*) network->header);
	}
	free(network);
}

enum polv_net_protocol polv_network_protocol(const u_char* ethertype)
{
	
	if (polv_compare(arp, ethertype,TYPE_LEN) == 0) 
		return ARP;
	if (polv_compare(ipv4, ethertype,TYPE_LEN) == 0)
		return IPV4;
	if (polv_compare(ipv6, ethertype,TYPE_LEN) == 0)
		return IPV6;
	//std::count << "Protocolo de red, no soportado" << std::endl;
	
	return UNKNOWN_NET;
}
