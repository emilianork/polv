#include "tools/polv_types.h"

struct polv_ip_v6 {
	const u_char* version;
	const u_char* traffic_class;
	const u_char* flow_label;
	const u_char* payload_len;
	const u_char* next_header;
	const u_char* hop_limit;
	const u_char* src_addr;
	const u_char* dst_addr;
};

struct polv_ip_v6* polv_ip_v6_init();
void polv_ip_v6_destroy(struct polv_ip_v6*);
