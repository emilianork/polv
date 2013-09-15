#ifndef POLV_UPD_H
#define POLV_UPD_H

#include "tools/polv_types.h"
#include "tools/polv_next_layer.h"

#define SRC_PORT_UDP 0
#define DST_PORT_UDP 2
#define LEN_UDP 4
#define CHECKSUM_UDP 6

#define DATA_UDP 8

#define SRC_PORT_UDP_LEN 2
#define DST_PORT_UDP_LEN 2
#define LEN_UDP_LEN 2
#define CHECKSUM_UDP_LEN 2

struct polv_udp {
	const u_char* src_port;
	const u_char* dst_port;
	const u_char* len;
	const u_char* checksum;
};

struct polv_udp* polv_udp_init();
void polv_udp_destroy(struct polv_udp*);

const u_char* polv_upd_src_port(const u_char*);
const u_char* polv_udp_dst_port(const u_char*);
const u_char* polv_upd_len(const u_char*);
const u_char* polv_udp_checksum(const u_char*);

struct polv_next_layer* polv_udp_data(const u_char*, int);
#endif POLV_UPD_H
