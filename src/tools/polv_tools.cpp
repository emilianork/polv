#include "tools/polv_tools.h"

#include <iostream>

const hexadecimal* polv_oct(int from, int len, const u_char* packet) 
{
	hexadecimal* hex;
	u_char* octs;
	
	octs = (u_char*) malloc(sizeof(u_char));

	int i;

	for (i = 0; i < len; i++) {
		octs[i] = packet[from + i];
	}

	hex = (hexadecimal*) malloc(sizeof(hexadecimal));

	hex->octs = (const u_char*) octs;
	hex->len = len;
	return ((const hexadecimal) hex);
}
