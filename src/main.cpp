#include "packet/polv_packet.h"
#include "tools/polv_tools.h"

#include "data_link/polv_data_link.h"
#include "network/polv_network.h"
#include "network/polv_ip_v4.h"
#include "network/polv_ip_v6.h"
#include "network/polv_arp.h"

#include "filter/polv_filter.h"

#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <pcap.h>

#include <iostream>

using namespace std;

void callback (u_char*, const struct pcap_pkthdr*, const u_char*);
void print_packet(const u_char*, int);
void print_octs(const u_char*, int);
void print_data_link(struct polv_data_link*);
void print_network(struct polv_network*);
void print_transport(struct polv_transport*);
void print_ipv4(struct polv_ip_v4*);
void print_ipv6(struct polv_ip_v6*);
void print_arp(struct polv_arp*);
void print_udp(struct polv_udp*);
void print_icmp(struct polv_icmp*);
void print_tcp(struct polv_tcp*);

#define MAC_ADDRESS_LEN 6

int num = 0;
int extern_argc;
char** extern_argv;

int main(int argc, char *argv[])
{
	extern_argc = argc;
	extern_argv = argv;
	char *dev,*dump_10,errbuf[PCAP_ERRBUF_SIZE];
	
	pcap_t* capture;
	pcap_dumper_t* pd;
	
	const u_char *packet;
	struct pcap_pkthdr hdr;
	polv_validate_filter(extern_argc,extern_argv);
	
	int count = 20;
	
	dev = argv[1];
	
	printf("Device: %s\n\n",dev);

	capture = pcap_open_live(dev,BUFSIZ, 0, 1000, errbuf);
    
	if (capture == NULL) {
		printf("pcap_open_live(): %s\n",errbuf);
		return EXIT_FAILURE;
	}
	
	pcap_loop(capture,count,callback,(u_char*)packet);
	
	pcap_close(capture);
	
	printf("\n");
	
	return EXIT_SUCCESS;
}

void callback(u_char *user, const struct pcap_pkthdr* header,
			  const u_char* packet)
{
	struct polv_packet* p;
	if (polv_filter(packet,header->len,extern_argc,extern_argv)) {
		printf("PAQUETE CORRECTO\n");
	} else {
		printf("PAQUETE ERRONEO\n");
	}
	//p = polv_packet_create(packet,header->len);
	/*
	printf("\tPACK ORIGINAL: \n");
	print_packet(packet,header->len);
	
	print_data_link(p->data_link);
	print_network(p->network);
	print_transport(p->transport);
	
	if (p->raw_data != NULL) {
		printf("\t\tDatos:\n ");
		print_packet(p->raw_data,p->raw_data_len);
	} else {
		printf("No tiene data");
	}
	*/
	//polv_packet_destroy(p);
	
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
		printf("\nEther Version: %s", "V802   ");
		break;
	case VII:
			printf("\nEther Version: %s", "VII   ");
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

void print_network(struct polv_network* network)
{
	if (network == NULL) {
		printf("PROTOCOLO DE RED NO RECONOCIDO\n");
		return;
	}
	switch(network->protocol) {
	case IPV4:
		print_ipv4((struct polv_ip_v4*)network->header);
		break;
	case IPV6:
		print_ipv6((struct polv_ip_v6*)network->header);
		break;
	case ARP:
		print_arp((struct polv_arp*)network->header);
		break;
	}
	return;
}

void print_ipv4(struct polv_ip_v4* ip)
{
	printf("\n\n\tIP4:\n");
	
	printf("Version: ");
	print_octs(ip->version,VERSION_LEN);
	
	printf("Ihl: ");
	print_octs(ip->ihl,IHL_LEN);

	printf("Type of service: ");
	print_octs(ip->type_service, TYPE_SERVICE);
	
	printf("Len: ");
	print_octs(ip->len,LEN_LEN);

	printf("Identification: ");
	print_octs(ip->identification,IDENTIFICATION_LEN);

	printf("Flags: ");
	print_octs(ip->flags, FLAGS_LEN);

	printf("Fragment Offset: ");
	print_octs(ip->fragment_offset,FRAGMENT_OFFSET_LEN);

	printf("Time to live: ");
	print_octs(ip->time_to_live,TIME_TO_LIVE_LEN);
	
	printf("Protocol: ");
	print_octs(ip->protocol,PROTOCOL_LEN);

	printf("Header Check: ");
	print_octs(ip->header_check,HEADER_CHECK_LEN);

	printf("SRC ADDR: ");
	print_octs(ip->src_addr, SRC_ADDR_LEN);
	
	printf("DST ADDR: ");
	print_octs(ip->dst_addr, DST_ADDR_LEN);

	if (ip->ihl[0] > 5) {
		printf("OPTIONS: ");
		print_octs(ip->options,(ip->ihl[0] - 5) * 4);
	}
	printf("\n");
}

void print_ipv6(struct polv_ip_v6* ip) 
{
	printf("\n\n\tIP6:\n");

	printf("Version: ");
	print_octs(ip->version,VERSION_V6_LEN);

	printf("Traffic Class: ");
	print_octs(ip->traffic_class,TRAFFIC_CLASS_LEN);

	printf("Flow Label: ");
	print_octs(ip->flow_label,FLOW_LABEL_LEN);
	
	printf("Payload_len: ");
	print_octs(ip->payload_len,PAYLOAD_LEN_LEN);
	
	printf("Next header: ");
	print_octs(ip->next_header,NEXT_HEADER_LEN);

	printf("Hop Limit: ");
	print_octs(ip->hop_limit,HOP_LIMIT_LEN);

	printf("Src Addr: ");
	print_octs(ip->src_addr, SRC_ADDR_V6_LEN);

	printf("Dst Addr: ");
	print_octs(ip->dst_addr, DST_ADDR_V6_LEN);

	printf("\n");
}

void print_arp(struct polv_arp* arp)
{
	printf("\n\n\tARP:\n");
	
	printf("HTYPE: ");
	print_octs(arp->htype, HTYPE_LEN);

	printf("PTYPE: ");
	print_octs(arp->ptype, PTYPE_LEN);

	printf("HLEN: ");
	print_octs(arp->hlen,HLEN_LEN);
	
	printf("PLEN: ");
	print_octs(arp->plen,PLEN_LEN);

	printf("OPER: ");
	print_octs(arp->oper,OPER_LEN);
	
	printf("SHA: ");
	print_octs(arp->sha,SHA_LEN);
	
	printf("SPA: ");
	print_octs(arp->spa,SPA_LEN);

	printf("THA: ");
	print_octs(arp->tha,THA_LEN);

	printf("TPA: ");
	print_octs(arp->tpa,TPA_LEN);

	printf("\n");
}

void print_transport(struct polv_transport* transport)
{
	if (transport == NULL) {
		printf("PROTOCOLO DE RED NO RECONOCIDO\n");
		return;
	}
	
	switch(transport->protocol) {
	case UDP:
		print_udp((struct polv_udp*)transport->header);
		return;
	case ICMP:
		print_icmp((struct polv_icmp*)transport->header);
		return;
	case TCP:
		print_tcp((struct polv_tcp*)transport->header);
		return;
	}
}

void print_udp(struct polv_udp* udp)
{
	printf("\n\n\tUDP:\n");
	
	printf("Source Port: ");
	print_octs(udp->src_port,SRC_PORT_UDP_LEN);

	printf("Dest Port: ");
	print_octs(udp->dst_port,DST_PORT_UDP_LEN);

	printf("Length: ");
	print_octs(udp->len,LEN_UDP_LEN);

	printf("Checksum: ");
	print_octs(udp->checksum,CHECKSUM_UDP_LEN);

	printf("\n");
}

void print_icmp(struct polv_icmp* icmp)
{
	printf("\n\n\tICMP:\n");
	
	printf("Type: ");
	print_octs(icmp->type,TYPE_ICMP_LEN);

	printf("Code: ");
	print_octs(icmp->code,CODE_ICMP_LEN);

	printf("Checksum: ");
	print_octs(icmp->checksum,CHECKSUM_ICMP_LEN);

	printf("\n");
	

}
void print_tcp(struct polv_tcp* tcp)
{
	printf("\n\n\tTCP:\n");
	
	printf("Source Port: ");
	print_octs(tcp->src_port,SRC_PORT_TCP_LEN);

	printf("Dest Port: ");
	print_octs(tcp->dst_port,DST_PORT_TCP_LEN);

	printf("Seq: ");
	print_octs(tcp->seq,SEQ_TCP_LEN);

	printf("Ack: ");
	print_octs(tcp->ack,ACK_TCP_LEN);

	printf("Offset: ");
	print_octs(tcp->offset,OFFSET_TCP_LEN);

	printf("Reserved: ");
	print_octs(tcp->reserved,RESERVED_TCP_LEN);

	printf("Flags: ");
	print_octs(tcp->flags,FLAGS_TCP_LEN);

	printf("Window: ");
	print_octs(tcp->window,WINDOW_TCP_LEN);

	printf("Checksum: ");
	print_octs(tcp->checksum,CHECKSUM_TCP_LEN);

	printf("Urgent: ");
	print_octs(tcp->urgent,URGENT_TCP_LEN);

	printf("\n");

}
