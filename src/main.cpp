#include "polv_packet.h"
#include "polv_tools.h"

#include "polv_data_link.h"

#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <pcap.h>

#include <iostream>

using namespace std;

void callback (u_char*, const struct pcap_pkthdr*, const u_char*);

#define MAC_ADDRESS_LEN 6


int main(int argc, char *argv[])
{
	char *dev,*dump_10,errbuf[PCAP_ERRBUF_SIZE];
	
	pcap_t* capture;
	pcap_dumper_t* pd;
	
	const u_char *packet;
	struct pcap_pkthdr hdr;

	int count = 1;
	
	dev = argv[1];
	
	printf("Device: %s\n\n",dev);
	
	capture = pcap_open_live(dev,BUFSIZ, 0, 1000, errbuf);
    
	if (capture == NULL) {
		printf("pcap_open_live(): %s\n",errbuf);
		return EXIT_FAILURE;
	}
	
	pcap_loop(capture,count,callback,(u_char*)packet);
	
	pcap_close(capture);
	
	return EXIT_SUCCESS;
}

void callback(u_char *user, const struct pcap_pkthdr* header,
			  const u_char* packet)
{
	int i;
	const u_char *src, *dst;
	enum polv_ethertype type;


	dst = polv_ether_dst(packet);
	src = polv_ether_src(packet);
	type = polv_ether_ver(packet);
	
	printf("Paquete:   ");
	for(i = 0; i < header->len; i++) {
		if (i + 1 != header->len)
			printf("%02x:",packet[i]);
		else
			printf("%02x",packet[i]);
	}

	printf("\n     Destino: ");
	for(i = 0; i < 6 ; i++) {
	    printf("%02x:",dst[i]);
	}

	printf("     Fuente: ");
	for(i =0; i < 6; i++) {
	    printf("%02x:",src[i]);
	}
	
	switch (type) {
		
	case VII:
		printf("     VII");
		break;
	case V802:
		printf("     802");
		break;
	}

	printf("\n");
	int len = header->len - 14;

	const u_char* header_network;
	
	header_network = polv_network_header(packet,type,len);

	printf("Paquete: ");
	for(i = 0; i < len ; i++) {
		if ( i + 1 != len)
			printf("%02x:",header_network[i]);
		else
			printf("%02x\n",header_network[i]);
	}

	return;
}
