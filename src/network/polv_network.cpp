#include "network/polv_network.h"
#include "network/polv_ip_v4.h"
#include "network/polv_ip_v6.h"
#include "network/polv_arp.h"

#include <cstdlib>
#include <iostream>

u_char arp[2] = {8,6};
u_char ipv4[2] = {8,0};
u_char ipv6[2] = {134, 221};

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
	if (arp == ethertype) 
		return ARP;
	if (ipv4 == ethertype)
		return IPV4;
	if (ipv6 == ethertype)
		return IPV6;
	else
		exit(EXIT_FAILURE);
}
