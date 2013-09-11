#include "polv_network.h"
#include "polv_ip_v4.h"
#include "polv_ip_v6.h"
#include "polv_arp.h"

#include <cstdlib>
#include <iostream>

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
