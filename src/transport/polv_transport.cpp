#include "transport/polv_transport.h"

#include <cstdlib>
#include <iostream>

using namespace std;

struct polv_transport* polv_transport_init()
{
	struct polv_transport* transport;

	transport = (struct polv_transport*) malloc(sizeof(struct polv_transport));

	if (transport == NULL) {
		cout << "\nNo se encontro memoria disponible." << endl;
		exit(EXIT_FAILURE);
	}

	transport->header = transport->message = NULL;

	return transport;
}

void polv_transport_destroy(struct polv_transport* transport)
{
	free(transport);
}
