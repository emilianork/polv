#ifndef POLV_ICMP_H_
#define POLV_ICMP_H

#include "tools/polv_types.h"
#include "tools/polv_next_layer.h"

#define TYPE_ICMP 0
#define CODE_ICMP 1
#define CHECKSUM_ICMP 2
#define DATA_ICMP 4

#define TYPE_ICMP_LEN 1
#define CODE_ICMP_LEN 1
#define CHECKSUM_ICMP_LEN 2


struct polv_icmp {
	const u_char* type;
	const u_char* code;
	const u_char* checksum;
};

struct polv_icmp* polv_icmp_init();
void polv_icmp_destroy(struct polv_icmp*);

const u_char* polv_icmp_type(const u_char*);
const u_char* polv_icmp_code(const u_char*);
const u_char* polv_icmp_checksum(const u_char*);

void polv_icmp_data(struct polv_next_layer*);

#endif POLV_ICMP_H_

