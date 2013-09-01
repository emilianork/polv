#include "data_link.h"
#include "network.h"
#include "transport.h"

struct osi_model {
	struct data_link* data_link;
	struct network* network;
	struct transport* transport;
};
