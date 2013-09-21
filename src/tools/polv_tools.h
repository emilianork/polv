/*
  José Emiliano Cabrera Blancas
  Diego Andrés Gómez Montesinos 
  
  Funiones para el manejo de u_char*
*/

#ifndef POLV_TOOLS_H_
#define POLV_TOOLS_H_

#include "tools/polv_types.h"

/* @param from
   @param len
   @param packet
   @return El paquete completo*/
const u_char* polv_oct(int,int,const u_char*);

/*
  @param first
  @param two
  @param len
  @return -1 si first < two, 0 si first == two y 1 si first > two
**/
int polv_compare(const u_char*,const u_char*,int);

#endif POLV_TOOLS_H_

