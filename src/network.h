enum net_protocol {
	IP,
	ARP
};


struct ip {

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

struct arp {
	const u_char* htype;
	const u_char* ptype;
	const u_char* hlen;
	const u_char* plen;
	const u_char* oper;
	const u_char* sha;
	const u_char* spa;
	const u_char* tha;
	const u_char* tpa;

};

struct network {
	enum net_protocol protocol;
	void* protocol_header;
};
