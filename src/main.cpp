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
void print_data_link(struct polv_data_link*);
void print_packet(const u_char*, int);
void print_octs(const u_char*, int);

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
	struct polv_data_link* data_link;
	data_link = polv_data_link_layer_init(packet);

	printf("Paquete en bruto:\n");
	print_packet(packet,header->len);
	
	print_data_link(data_link);


		
	printf("\n\tPaquete capa de enlace: ");

	struct polv_next_layer* next_layer;
	next_layer = polv_network_packet(packet,data_link->type,header->len);

	print_packet(next_layer->packet,next_layer->len);
		
	return;
}


void print_packet(const u_char* packet, int len)
{
	int i;
	for(i = 0; i < len; i++) {
		if (i + 1 != len)
			printf("%02x:",packet[i]);
		else
			printf("%02x\n",packet[i]);
	}

	return;
}

void print_octs(const u_char* octs, int len)
{
	int i;
	for(i = 0; i < len; i++) {
		if (i + 1 != len)
			printf("%02x:",octs[i]);
		else
			printf("%02x      ",octs[i]);
	}

	return;
}

void print_data_link(struct polv_data_link* data_link)
{
	if (data_link == NULL) {
		printf("PROTOCOLO DE ETHERNET NO RECONOCIDO\n");
		return;
	}
	
	switch (data_link->type) {
	case V802:
		printf("Ether Version: %s", "V802   ");
		break;
	case VII:
			printf("Ether Version: %s", "VII   ");
	}

	printf("Mac Destino: ");
	print_octs(data_link->dst,MAC_ADDRESS);

	printf("Mac Fuente: ");
	print_octs(data_link->src,MAC_ADDRESS);

	printf("Longitud/Tipo: ");
	print_octs(data_link->ethertype,TYPE_LEN);
	
	if (data_link->type == VII)
		return;
	
	printf("DSAP: ");
	print_octs(data_link->dsap, DSAP_LEN);
	
	printf("SSAP: ");
	print_octs(data_link->ssap, SSAP_LEN);

	printf("CONTROL: ");
	print_octs(data_link->control, CONTROL_LEN);

	printf("ORG_CODE: ");
	print_octs(data_link->org_code, ORG_CODE);
	
	return;
		
}
