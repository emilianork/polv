#ifndef POLV_FILTER_H_
#define POLV_FILTER_H_

#include "tools/polv_types.h"

void polv_validate_filter(int,char**);

int polv_filter(const u_char*,int,int,char**);

/* Regresa la posicion donde se encuentra el termino, -1 en caso de 
   no encontrarlo*/
int search_terms(const char*,int, char**);

#endif POLV_FILTER_H_
