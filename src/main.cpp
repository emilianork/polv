#include "packet/polv_packet.h"
#include "tools/polv_tools.h"

#include "data_link/polv_data_link.h"

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

	int count = 1000;
	
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
	const u_char *src, *dst, *ethertype;
	enum polv_ethertype type;
	int len = header->len - 14;
	const u_char* header_network;

	dst = polv_ether_dst(packet);
	src = polv_ether_src(packet);
	type = polv_ether_ver(packet);
	ethertype = polv_ethertype(packet,type); 
	
	header_network = polv_network_header(packet,type,len);

	enum polv_net_protocol arp = polv_network_protocol(ethertype);

	if (arp == IPV4) {
		printf("IPV4\n");
	}
	
	if (arp == IPV6) {
		printf("IPV6\n");
		
		printf("Paquete:   ");
		for(i = 0; i < header->len; i++) {
			if (i + 1 != header->len)
				printf("%02x:",packet[i]);
			else
				printf("%02x\n",packet[i]);
		}
		exit(0);
	}
	
	if (arp == ARP) {
		printf("ARP\n");
		
		printf("Paquete:   ");
		for(i = 0; i < header->len; i++) {
			if (i + 1 != header->len)
				printf("%02x:",packet[i]);
			else
				printf("%02x\n",packet[i]);
		}
	}

	printf("\n");
	
	

	return;
}
