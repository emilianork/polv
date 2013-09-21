/*
  José Emiliano Cabrera Blancas
  Diego Andrés Gómez Montesinos 
  
  Implementacion de las funciones del encabezado con el mismo nombre.
*/

#include "tools/polv_tools.h"

#include <iostream>
#include <cstdlib>

const u_char* polv_oct(int from, int len, const u_char* packet) 
{
	u_char* octs;
	
	octs = (u_char*) malloc(sizeof(u_char)*len);

	int i;

	for (i = 0; i < len; i++) {
		octs[i] = packet[from + i];
	}

	return ((const u_char*) octs);
}

int polv_compare(const u_char* first,const  u_char* two, int len)
{
	int i;
	for(i = 0; i < len; i++) {
		if (first[i] < two[i])
			return -1;
		if (first[i] > two[i])
			return 1;
	}
	return 0;
}

