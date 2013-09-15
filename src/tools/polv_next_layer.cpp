#include "tools/polv_next_layer.h"

#include <cstdlib>

struct polv_next_layer* polv_next_layer_init()
{
	struct polv_next_layer* next_layer;

	next_layer = (struct polv_next_layer*) malloc(sizeof(struct polv_next_layer));
	
	next_layer->packet = NULL;
  
	return next_layer;
}

void polv_next_layer_destroy(struct polv_next_layer* next_layer)
{
	free((u_char*)next_layer->packet);
	free(next_layer);

	return;
}
