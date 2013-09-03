#include "data_link.h"
#include "network.h"
#include "transport.h"

struct packet_povl {
	struct data_link* data_link;
	struct network* network;
	struct transport* transport;
};
