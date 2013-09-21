/*
  José Emiliano Cabrera Blancas
  Diego Andrés Gómez Montesinos 
  
  Encabezado con funciones exclusivas para filtrar los paquetes
*/


#ifndef POLV_FILTER_H_
#define POLV_FILTER_H_

#include "tools/polv_types.h"

/* Antes de capturar paquetes, verificamos que los parametros esten 
 que se le pasaron a la linea de comandos, son correctos. */
void polv_validate_filter(int,char**);

/* Regrra TRUE en caso de que el paquete cumpla con el filtro o FALSE en 
 otro caso. */
int polv_filter(const u_char*,int,int,char**);

/* Regresa la posicion donde se encuentra el termino, -1 en caso de 
   no encontrarlo*/
int search_terms(const char*,int, char**);

#endif POLV_FILTER_H_
