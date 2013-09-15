#ifndef POLV_NEXT_LAYER_H
#define POLV_NEXT_LAYER_H

#include "tools/polv_types.h"

struct polv_next_layer {
	const u_char* packet;
	int len;
};

struct polv_next_layer* polv_next_layer_init();
void polv_next_layer_destroy(struct polv_next_layer*);

#endif POLV_NEXT_LAYER_H
