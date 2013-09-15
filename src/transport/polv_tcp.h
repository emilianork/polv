#ifndef POLV_TCP_H_
#define POLV_TCP_H_

#include "tools/polv_types.h"
#include "tools/polv_next_layer.h"

#define SRC_PORT_TCP 0
#define DST_PORT_TCP 2
#define SEQ_TCP 4
#define ACK_TCP 8
#define OFFSET_TCP 12
#define RESERVED_TCP 12
#define FLAGS_TCP 13
#define WINDOW_TCP 14
#define CHECKSUM_TCP 16
#define URGENT_TCP 18
#define OPTIONS_TCP 20

#define SRC_PORT_TCP_LEN 2
#define DST_PORT_TCP_LEN 2
#define SEQ_TCP_LEN 4
#define ACK_TCP_LEN 4
#define OFFSET_TCP_LEN 1
#define RESERVED_TCP_LEN 1
#define FLAGS_TCP_LEN 1
#define WINDOW_TCP_LEN 2
#define CHECKSUM_TCP_LEN 2
#define URGENT_TCP_LEN 2

struct polv_tcp {
	const u_char* src_port;
	const u_char* dst_port;
	const u_char* seq;
	const u_char* ack;
	const u_char* offset;
	const u_char* reserved;
	const u_char* flags;
	const u_char* window;
	const u_char* checksum;
	const u_char* urgent;
	const u_char* options;

};

struct polv_tcp* polv_tcp_init();
void polv_tcp_destroy(struct polv_tcp*);

const u_char* polv_tcp_src_port(const u_char*);
const u_char* polv_tcp_dst_port(const u_char*);
const u_char* polv_tcp_seq(const u_char*);
const u_char* polv_tcp_ack(const u_char*);
const u_char* polv_tcp_offset(const u_char*);
const u_char* polv_tcp_reserved(const u_char*);
const u_char* polv_tcp_flags(const u_char*);
const u_char* polv_tcp_window(const u_char*);
const u_char* polv_tcp_checksum(const u_char*);
const u_char* polv_tcp_urgent(const u_char*);
const u_char* polv_tcp_options(const u_char*);

struct next_layer* polv_tcp_data(const u_char*, int);

#endif POLV_TCP_H_
