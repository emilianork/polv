#include "polv_transport.h"

#include <cstdlib>

struct polv_transport* polv_transport_init()
{
	struct polv_transport* transport;

	transport = (struct polv_transport*) malloc(sizeof(struct polv_transport));

	transport->header = NULL;

	return transport;
}

void polv_transport_destroy(struct polv_transport* transport)
{
	free(transport);
}
