#include "polv_types.h"

struct polv_ip_v4 {

	const u_char* version;
	const u_char* ihl;
	const u_char* type_service;
	const u_char* len;
	const u_char* identification;
	const u_char* flags;
	const u_char* fragment_offset;
	const u_char* time_to_live;
	const u_char* protocol;
	const u_char* header_check;
	const u_char* src_addr;
	const u_char* dst_addr;
	const u_char* options;
};

struct polv_ip_v4* polv_ip_v4_init();
void polv_ip_v4_destroy(struct polv_ip_v4*);
