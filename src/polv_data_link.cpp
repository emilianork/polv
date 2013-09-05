#include "polv_data_link.h"

#include <cstdlib>

struct polv_data_link* polv_data_link_init()
{
	struct polv_data_link* data_link;

	data_link = (struct polv_data_link*) malloc(sizeof(struct polv_data_link));

	data_link->dst = data_link->src = data_link->crc = NULL;
	
	return data_link;
}


void polv_data_link_destroy(struct polv_data_link* data_link)
{
	free(data_link);
}
