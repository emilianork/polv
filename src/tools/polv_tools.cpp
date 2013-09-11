#include "polv_tools.h"

#include <iostream>

const u_char* polv_oct(int from, int len, const u_char* packet) 
{
	u_char* octs;
	octs = (u_char*) malloc(sizeof(u_char));

	int i;

	for (i = 0; i < len; i++) {
		octs[i] = packet[from + i];
	}

	return ((const u_char*)octs);
}
