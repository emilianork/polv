/*
  José Emiliano Cabrera Blancas
  Diego Andrés Gómez Montesinos 
  
  Estructura que representa el encabezo y datos de la siguiente capa en
  general.
*/

#ifndef POLV_NEXT_LAYER_H
#define POLV_NEXT_LAYER_H

#include "tools/polv_types.h"

/* El paquete en hex mas su longitud */
struct polv_next_layer {
	const u_char* packet;
	int len;
};

/*Funciones para el manejo de la estructura. */
struct polv_next_layer* polv_next_layer_init();
void polv_next_layer_destroy(struct polv_next_layer*);

#endif POLV_NEXT_LAYER_H
