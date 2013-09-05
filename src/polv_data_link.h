#ifndef POLV_DATA_LINK_H_
#define POLV_DATA_LINK_H_

#include "polv_types.h"

enum polv_ethertype {
	VII,
	V802
};

struct polv_data_link {
	const u_char *dst;
	const u_char *src;
	enum polv_ethertype type;
	const u_char *crc;
};

struct polv_data_link* polv_data_link_init();

void polv_data_link_destroy(struct polv_data_link*);

/* @param  El paquete capturado con libpcap,
   @return La version de ethernet del paquete. */
//enum polv_ethertype polv_ether_ver(const u_char*);

#endif POLV_DATA_LINK_H_
