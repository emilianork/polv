
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


/* @param  El paquete capturado con libpcap,
   @return La version de ethernet del paquete. */
enum ether_type ether_ver(const u_char*);
