#include "polv_network.h"

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
	free(network);
}
