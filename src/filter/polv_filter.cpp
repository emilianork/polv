#include "filter/polv_filter.h"
#include "tools/polv_boolean.h"
#include "data_link/polv_data_link.h"
#include "network/polv_network.h"
#include "network/polv_ip_v4.h"
#include "network/polv_ip_v6.h"
#include "network/polv_arp.h"
#include "transport/polv_transport.h"
//#include "transport/polv_udp.h"
//#include "transport/polv_tcp.h"

#include <cstring>

#include <cstdio>
#include <cstdlib>

#include <iostream>

const char* polv_ether = "ether\0";
const char* polv_v802 = "802\0";
const char* polv_vII = "II\0";

const char* polv_net = "net\0";
const char* polv_ip4 = "ip\0";
const char* polv_ip6 = "ip6\0";
const char* polv_arp = "arp\0";
const char* polv_rarp = "rarp\0";
const char* polv_icmp = "icmp\0";

const char* polv_proto = "proto\0";
const char* polv_udp = "udp\0";
const char* polv_tcp = "tcp\0";

const char* polv_src_ip = "-S\0";
const char* polv_dst_ip = "-D\0";

const char* polv_src_port = "-s\0";
const char* polv_dst_port = "-d\0";


/* Valida ip*/
void validate_ip(const char*);

/*Valida puerto*/
void validate_port(const char*);

int compare_ips(const u_char*,char*);

int compare_port(const u_char*,char*);

void polv_validate_filter(int argc, char *argv[])
{
	int ether_pos,net_pos, proto_pos,
		src_ip_pos, dst_ip_pos, src_port_pos,
		dst_port_pos;
	
	enum polv_net_protocol net_protocol;
	enum polv_trans_protocol transport_protocol;

	ether_pos = search_terms(polv_ether,argc,argv);

	net_pos = search_terms(polv_net,argc,argv);
	proto_pos = search_terms(polv_proto,argc,argv);

	src_ip_pos = search_terms(polv_src_ip,argc,argv);
	dst_ip_pos = search_terms(polv_dst_ip,argc,argv);

	src_port_pos = search_terms(polv_src_port,argc,argv);
	dst_port_pos = search_terms(polv_dst_port,argc,argv);

	/* Validacion de ethernet */
	if (ether_pos != -1) {
		if (ether_pos + 1 == argc) {
			std::cout << "Protocolo de ethernet inválido" << std::endl;
			exit(EXIT_FAILURE);
		} else if (strcmp(polv_v802,argv[ether_pos + 1]) == 0) {
		} else if (strcmp(polv_vII,argv[ether_pos + 1]) == 0) {
		} else { 
			std::cout << "Protocolo de ethernet inválido" << std::endl;
			exit(EXIT_FAILURE);
		}
	} 
	
	/* Validación de protocolo de red */
	if (net_pos != -1) {
		if (net_pos + 1 == argc) {
			std::cout << "Protocolo de red inválido" << std::endl;
			exit(EXIT_FAILURE);
		} else if (strcmp(polv_ip4,argv[net_pos + 1]) == 0) {
			net_protocol = IPV4;
		} else if (strcmp(polv_ip6,argv[net_pos + 1]) == 0) {
			net_protocol = IPV6;
		} else if (strcmp(polv_arp,argv[net_pos + 1]) == 0) {
			net_protocol = ARP;
		} else if (strcmp(polv_rarp,argv[net_pos + 1]) == 0) {
		    std::cout << "Protocolo de red inválido" << std::endl;
			exit(EXIT_FAILURE);
		} else if (strcmp(polv_icmp,argv[net_pos + 1]) == 0) {
			net_protocol = UNKNOWN_NET;
			transport_protocol = ICMP;
		} else {
			std::cout << "Protocolo de red inválido" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	
	/* Validacion de protocolo de transporte*/
	if (proto_pos != -1) {
		if (proto_pos + 1 == argc) {
			std::cout << "Protocolo de transporte inválido" << std::endl;
			exit(EXIT_FAILURE);
		} else if (strcmp(polv_udp,argv[proto_pos + 1]) == 0) {
			transport_protocol = TCP;
		} else if (strcmp(polv_tcp,argv[proto_pos + 1]) == 0) {
			transport_protocol = UDP;
		} else {
			std::cout << "Protocolo de transporte inválido" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	

	
	/* Validacion de la ip fuente */
	if (src_ip_pos != -1) {
		if (src_ip_pos + 1 == argc) {
			std::cout << "Ip fuente inválida" << std::endl;
			exit(EXIT_FAILURE);
		} else {
			validate_ip((const char*)argv[src_ip_pos + 1]);
		}
	}
	
	/* Validacion de la ip destino */
	if (dst_ip_pos != -1) {
		if (dst_ip_pos + 1 == argc) {
			std::cout << "Ip destino inválida" << std::endl;
			exit(EXIT_FAILURE);
		} else {
		    validate_ip((const char*)argv[dst_ip_pos + 1]);
		}
	}
	
	/* Validacion de la puerto fuente */
	if (src_port_pos != -1) { 
		if (src_port_pos + 1 == argc) {
			std::cout << "Puerto fuente inválido" << std::endl;
			exit(EXIT_FAILURE);
		} else {
		    validate_port((const char*)argv[src_port_pos + 1]);
		}
	}

	/* Validacion de la puerto destino */
	if (dst_port_pos != -1) {
		if (dst_port_pos + 1 == argc) {
			std::cout << "Puerto destino inválido" << std::endl;
			exit(EXIT_FAILURE);
		} else {
			validate_port((const char*)argv[dst_port_pos + 1]);
		}
	}

	/* Valido que net y proto no tengan los siguientes choques: 
	   - ICMP no puede ir proto udp/tcp.
	   - ARP y RARP no pueden ir con proto udp/tcp */
	if ((proto_pos != -1) && (net_pos != -1)) {
		if (net_protocol == UNKNOWN_NET) {
			std::cout << "Sintaxis erronea" << std::endl;
			exit(EXIT_FAILURE);
		} else if ((net_protocol == ARP) || (net_protocol == RARP)) {
			std::cout << "Sintaxis erronea" << std::endl;
			exit(EXIT_FAILURE);
		} else {
		}
	}

	/*Valido que net y -s no tengan choques como: 
	  - ICMP, ARP y RARP no pueden ir con -s*/
	if ((src_port_pos != -1) && (net_pos != -1)) {
		if (net_protocol == UNKNOWN_NET) {
			std::cout << "Sintaxis erronea" << std::endl;
			exit(EXIT_FAILURE);
		} else if (net_protocol == ARP) {
			std::cout << "Sintaxis erronea" << std::endl;
			exit(EXIT_FAILURE);
		} else if (net_protocol == RARP) {
			std::cout << "Sintaxis erronea" << std::endl;
			exit(EXIT_FAILURE);
		} else {
		}
	}


	/*Valido que net y -d no tengan choques como: 
	  - ICMP, ARP y RARP no pueden ir con -d*/
	if ((dst_port_pos != -1) && (net_pos != -1)) {
		if (net_protocol == UNKNOWN_NET) {
			std::cout << "Sintaxis erronea" << std::endl;
			exit(EXIT_FAILURE);
		} else if (net_protocol == ARP) {
			std::cout << "Sintaxis erronea" << std::endl;
			exit(EXIT_FAILURE);
		} else if (net_protocol == RARP) {
			std::cout << "Sintaxis erronea" << std::endl;
			exit(EXIT_FAILURE);
		} else {
		}
	}

	/*Valido que net ip6 no tenga choques: 
	 - IPV6 no puede ir con las opciones -S */	
	if ((net_pos != -1) && (src_ip_pos != -1)) {
		if (net_protocol == IPV6) {
			std::cout << "Sintaxis erronea" << std::endl;
			exit(EXIT_FAILURE);
		}	
	}


	/*Valido que net ip6 no tenga choques: 
	 - IPV6 no puede ir con las opciones -D */	
	if ((net_pos != -1) && (dst_ip_pos != -1)) {
		if (net_protocol == IPV6) {
			std::cout << "Sintaxis erronea" << std::endl;
			exit(EXIT_FAILURE);
		}	
	}
}


int polv_filter(const u_char* packet, int len, int argc, char** argv)
{
	
	int ether_pos,net_pos, proto_pos,
		src_ip_pos, dst_ip_pos, src_port_pos,
		dst_port_pos;
	
	ether_pos = search_terms(polv_ether,argc,argv);
	
	net_pos = search_terms(polv_net,argc,argv);
	proto_pos = search_terms(polv_proto,argc,argv);
	
	src_ip_pos = search_terms(polv_src_ip,argc,argv);
	dst_ip_pos = search_terms(polv_dst_ip,argc,argv);
	
	src_port_pos = search_terms(polv_src_port,argc,argv);
	dst_port_pos = search_terms(polv_dst_port,argc,argv);
	
	enum polv_ethertype ethertype;

	ethertype = polv_ether_ver(packet);
	
	/* Checa que la version de ethernet sea la que se pide*/
	if (ether_pos != -1) {
		if (strcmp(polv_v802,argv[ether_pos + 1]) == 0) {
		    if (ethertype != V802) {
				return FALSE;
			}
			
		} else if (strcmp(polv_vII,argv[ether_pos + 1]) == 0) {
			if (ethertype != VII) {
				return FALSE;
				
			}
		} else {
		}
	}
	
	enum polv_net_protocol net_protocol;
	const u_char* network_protocol;
	
	network_protocol = polv_ethertype(packet,ethertype);
	net_protocol = polv_network_protocol(network_protocol);
	free((u_char*)network_protocol);
	
	/* Checa que la version de protocolo de red  sea la que se pide*/
	
	if (net_pos != -1) {
		if (ethertype == UNKNOWN_LINK) {
			return FALSE;
		}
		switch (net_protocol) {
		case ARP:
			if (strcmp(polv_arp,argv[net_pos + 1]) == 0) {
				return TRUE;
			} else {
				return FALSE;
			}
		case RARP:
			if (strcmp(polv_rarp,argv[net_pos + 1]) == 0) {
				return TRUE;
			} else {
				return FALSE;
			}
		case IPV4:
			if (strcmp(polv_ip4,argv[net_pos + 1]) != 0) { 
				if (strcmp(polv_icmp,argv[net_pos + 1]) != 0) {
					return FALSE;
				}
			}
			break;
		case IPV6:
			if (strcmp(polv_ip6,argv[net_pos + 1]) != 0) {
				if (strcmp(polv_icmp,argv[net_pos + 1]) != 0) {
					return FALSE;
				}
			}
			break;
		case UNKNOWN_NET:
			return FALSE;
		}
	}

	/* Obtenemos la capa de red para las banderas -S y -D para ip 4*/
	struct polv_next_layer* next_layer;
	next_layer = polv_next_layer_init();

	polv_network_packet(packet,next_layer,ethertype,len);
	
	/* Comprobamos que sea ipv4 y  arp, ademas tenga la ip fuente solicitada */
	if (src_ip_pos != -1) {
		if (!((net_protocol == IPV4) || (net_protocol == ARP))) {
				polv_next_layer_destroy(next_layer);
			return FALSE;
		} else {
			const u_char* ip_src;
			if (net_protocol == IPV4) {
				ip_src = polv_ip_v4_src_addr(next_layer->packet);
				if (!(compare_ips(ip_src,argv[src_ip_pos + 1]))) {
					polv_next_layer_destroy(next_layer);
					free((u_char*)ip_src);
					return FALSE;
				}
				free((u_char*)ip_src);
			}
			if (net_protocol == ARP) {
				ip_src = polv_arp_spa(next_layer->packet);
				if (!(compare_ips(ip_src,argv[src_ip_pos + 1]))) {
					polv_next_layer_destroy(next_layer);
					free((u_char*)ip_src);
					return FALSE;
				}
				free((u_char*)ip_src);
			}
		}
	}

	/* Comprobamos que sea ipv4 y  arp, ademas tenga la ip destino solicitada */
	if (dst_ip_pos != -1) {
		if (!((net_protocol == IPV4) || (net_protocol == ARP))) {
				polv_next_layer_destroy(next_layer);
			return FALSE;
		} else {
			const u_char* ip_dst;
			if (net_protocol == IPV4) {
				ip_dst = polv_ip_v4_dst_addr(next_layer->packet);
				if (!(compare_ips(ip_dst,argv[dst_ip_pos + 1]))) {
					polv_next_layer_destroy(next_layer);
					free((u_char*)ip_dst);
					return FALSE;
				}
				free((u_char*)ip_dst);
			}
			if (net_protocol == ARP) {
				ip_dst = polv_arp_tha(next_layer->packet);
				if (!(compare_ips(ip_dst,argv[dst_ip_pos + 1]))) {
					polv_next_layer_destroy(next_layer);
					free((u_char*)ip_dst);
					return FALSE;
				}
				free((u_char*)ip_dst);
			}
		}
	}
	
	const u_char* raw_transport_protocol;
	enum polv_trans_protocol transport_protocol;
	
	
	const u_char* ip_protocol;
	if (net_protocol == IPV4) {
		ip_protocol = polv_ip_v4_protocol(next_layer->packet);
		transport_protocol = polv_transport_protocol(ip_protocol);
		free((u_char*)ip_protocol);
	} else if (net_protocol == IPV6){
		ip_protocol = polv_ip_v6_next_header(next_layer->packet);	
		transport_protocol = polv_transport_protocol(ip_protocol);
		free((u_char*)ip_protocol);
	} else {

		polv_next_layer_destroy(next_layer);
		return FALSE;
	}

	
	/* Verifica que sea el protocolo de transporte  se solicito */
	if (proto_pos != -1) {
		if (ethertype == UNKNOWN_LINK) {

			polv_next_layer_destroy(next_layer);
			return FALSE;
		}
		if (!((net_protocol == IPV4) || (net_protocol == IPV6))) {

			polv_next_layer_destroy(next_layer);
			return FALSE;
		}

		switch (transport_protocol) {
		case UDP:
			if (!(strcmp(polv_udp,argv[proto_pos + 1]) == 0)) {
				polv_next_layer_destroy(next_layer);
				return FALSE;	
			}
			break;
		case TCP:
			if (!(strcmp(polv_tcp,argv[proto_pos + 1]) == 0)) {

				polv_next_layer_destroy(next_layer);
				return FALSE;	
			}
			break;
		case ICMP:
			polv_next_layer_destroy(next_layer);
			return FALSE;
			break;
		case UNKNOWN_TRANS:

			polv_next_layer_destroy(next_layer);
			return FALSE;
		}
	}	
   
	if (net_pos != -1) {
		if ((strcmp(polv_icmp,argv[net_pos + 1]) == 0)) {
			if (transport_protocol == ICMP) {
	    
				polv_next_layer_destroy(next_layer);
				return TRUE;
			} else {
	    
				polv_next_layer_destroy(next_layer);
				return FALSE;	 
			}
		}
	}

	polv_transport_packet(next_layer,net_protocol);

	if (src_port_pos != -1) {
		if (ethertype == UNKNOWN_LINK) {

			polv_next_layer_destroy(next_layer);
			return FALSE;
		}
		if (net_protocol == UNKNOWN_NET) {

			polv_next_layer_destroy(next_layer);
			return FALSE;
		}
		
		if (transport_protocol == UNKNOWN_TRANS) {

			polv_next_layer_destroy(next_layer);
			return FALSE;
		} else if (transport_protocol == ICMP) {

			polv_next_layer_destroy(next_layer);
			return FALSE;
		} else if (transport_protocol == UDP){
			const u_char* udp_src_port;
			udp_src_port = polv_udp_src_port(next_layer->packet);
			if (!(compare_port(udp_src_port,argv[src_port_pos + 1]))) {

				polv_next_layer_destroy(next_layer);
				free((u_char*)udp_src_port);
				return FALSE;
			}
		} else if (transport_protocol == TCP) {
			const u_char* tcp_src_port;
			tcp_src_port = polv_tcp_src_port(next_layer->packet);
			if (!(compare_port(tcp_src_port,argv[src_port_pos + 1]))) {
		    
				polv_next_layer_destroy(next_layer);
				free((u_char*)tcp_src_port);
				return FALSE;
			}
		}
	}	

	if (dst_port_pos != -1) {
		if (ethertype == UNKNOWN_LINK) {

			polv_next_layer_destroy(next_layer);
			return FALSE;
		}
		if (net_protocol == UNKNOWN_NET) {
    
			polv_next_layer_destroy(next_layer);
			return FALSE;
		}
		
		if (transport_protocol == UNKNOWN_TRANS) {
	    
			polv_next_layer_destroy(next_layer);
			return FALSE;
		} else if (transport_protocol == ICMP) {

			polv_next_layer_destroy(next_layer);
			return FALSE;
		} else if (transport_protocol == UDP){
			const u_char* udp_dst_port;
			udp_dst_port = polv_udp_dst_port(next_layer->packet);
			if (!(compare_port(udp_dst_port,argv[dst_port_pos + 1]))) {
		    
				polv_next_layer_destroy(next_layer);
				free((u_char*)udp_dst_port);
				return FALSE;
			}
		} else if (transport_protocol == TCP) {
			const u_char* tcp_dst_port;
			tcp_dst_port = polv_tcp_dst_port(next_layer->packet);
			if (!(compare_port(tcp_dst_port,argv[dst_port_pos + 1]))) {

				polv_next_layer_destroy(next_layer);
				free((u_char*)tcp_dst_port);
				return FALSE;
			}
		}
	}
	

	polv_next_layer_destroy(next_layer);
	return TRUE;
}
	
void validate_ip(const char* ip)
{
	int i,j;
	int count_points = 0;
	int count_numbers;
	int original_number;
	
	char* number = (char*) malloc(sizeof(char) * 4);
	number[0] = '\0';
	number[1] = '\0';
	number[2] = '\0';
	number[3] = '\0';
	
	for(i = 0,j = 0; i < 4;i++, count_points++) {
		if (count_points == 4) {
			std::cout << "Sintaxis erronea" << std::endl;
			exit(EXIT_FAILURE);	
		}
		count_numbers = 0;
		while((ip[j] != '.') && (ip[j] != '\0')) {
			if (count_numbers == 3) {
				std::cout << "Sintaxis erronea" << std::endl;
				exit(EXIT_FAILURE);	
			}
			
			char* raw_number = (char*) malloc(sizeof(char)*2);
			raw_number[0] = ip[j];
			raw_number[1] = '\0';
		    char* only_numbers = (char*) strstr("0123456789",raw_number);
			if (only_numbers == NULL) {
				std::cout << "Sintaxis erronea" << std::endl;
				exit(EXIT_FAILURE);
			}
			number[count_numbers] = ip[j];
			count_numbers++;
			j++;
			free(raw_number);
		}
		j++;
		original_number = atoi(number);
		if (number[0] == '\0') {
			std::cout << "Sintaxis erronea" << std::endl;
			exit(EXIT_FAILURE);
		}
		if ((original_number < 0) || (original_number > 255)) {
			std::cout << "Sintaxis erronea" << std::endl;
			exit(EXIT_FAILURE);
		}

		number[0] = '\0';
		number[1] = '\0';
		number[2] = '\0';
		number[3] = '\0';
	}
	free(number);
}

void validate_port(const char* port)
{
	int j;
	for(j = 0; port[j] != '\0'; j++) {

		char* raw_number = (char*) malloc(sizeof(char)*2);
		raw_number[0] = port[j];
		raw_number[1] = '\0';
		char* only_numbers = (char*) strstr("0123456789",raw_number);
		if (only_numbers == NULL) {
			std::cout << "Sintaxis erronea" << std::endl;
			exit(EXIT_FAILURE);
		}
		free(raw_number);
	}

	int number;
	number = atoi((char*)port);

	if (number > 65535 || number < 1) {
		std::cout << "Sintaxis erronea" << std::endl;
		exit(EXIT_FAILURE);
	}
}

int compare_ips(const u_char* ip_packet, char* ip_arg) {
	int* ip_numbers = (int*) malloc(sizeof(int) * 4);
	int* ip_numbers_arg = (int*) malloc(sizeof(int) * 4);
	
	ip_numbers[0] = (u_char) ip_packet[0];
	ip_numbers[1] = (u_char) ip_packet[1];
	ip_numbers[2] = (u_char) ip_packet[2];
	ip_numbers[3] = (u_char) ip_packet[3];
	
	ip_numbers_arg[0] = -1;
	ip_numbers_arg[1] = -1;
	ip_numbers_arg[2] = -1;
	ip_numbers_arg[3] = -1;

	int i,j;
	int count_points = 0;
	int count_numbers;
	int original_number;
	
	char* number = (char*) malloc(sizeof(char) * 4);
	number[0] = '\0';
	number[1] = '\0';
	number[2] = '\0';
	number[3] = '\0';
	
	for(i = 0,j = 0; i < 4;i++, count_points++) {
		count_numbers = 0;
		while((ip_arg[j] != '.') && (ip_arg[j] != '\0')) {
			number[count_numbers] = ip_arg[j];
			count_numbers++;
			j++;
		}
		j++;
		original_number = atoi(number);
		
		int k;
		for (k = 0; k < 4; k++) {
			if (ip_numbers_arg[k] == -1) {
				ip_numbers_arg[k] = original_number;
				break;
			}
		}

		number[0] = '\0';
		number[1] = '\0';
		number[2] = '\0';
		number[3] = '\0';
	}
	free(number);

	for (i = 0; i < 4; i++) {
		if (ip_numbers_arg[i] != ip_numbers[i])
			return FALSE;
	}
	return TRUE;
}

int compare_port(const u_char* original,char* filter) {
	
	int original_number;
	original_number = original[0]*16 + original[1];
	
	int number;
	number = atoi((char*)filter);
	
	return (original_number == number);
}
 
int search_terms(const char* first,int argc,char *argv[])
{
	int i;
	for(i = 0; i < argc; i++)
		if (strcmp(first,(const char*)argv[i]) == 0)
			return i;

	return -1;
}
