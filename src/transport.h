enum protocol {
	TCP,
	UDP,
	ICMP
};

struct udp {
	const u_char* src_port;
	const u_char* dst_port;
	const u_char* len;
	const u_char* checksum;
};


struct tcp {
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

struct icmp {
	const u_char* type;
	const u_char* code;
	const u_char* checksum;
	const u_char* identifier;
	const u_char* seq;
	const u_char* data;
};

struct transport {
	enum protocol protocol;
	void* transport;
};
