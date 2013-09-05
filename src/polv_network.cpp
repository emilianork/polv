#include "polv_network.h"

#include <cstdlib>

struct polv_network* polv_network_init()
{
	struct polv_network* network;
	
	network = (struct polv_network*) malloc(sizeof(struct polv_network));

	network->header = NULL;
	return  network;
}

void polv_network_destroy(struct polv_network* network)
{
	free(network);
}
