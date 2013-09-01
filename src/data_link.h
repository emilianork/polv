
enum ether_type {
	VII,
	V802
};


struct data_link {
	const u_char *dst;
	const u_char *src;
	enum ether_type type;
	const u_char* crc;
};
