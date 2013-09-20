#include "filter/polv_filter.h"
#include "tools/polv_boolean.h"
#include "data_link/polv_data_link.h"
#include "network/polv_network.h"
#include "transport/polv_transport.h"

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


/* Regresa la posicion donde se encuentra el termino, -1 en caso de no encontrarlo*/
int search_terms(const char*,int, char**);

/* Valida ip*/
void validate_ip(const char*);

/*Valida puerto*/
void validate_port(const char*);

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
			net_protocol = RARP;
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
	
	/*Valido que net y -S no tengan choques como: 
	  - ARP y RARP no pueden ir con -S*/
	if ((src_ip_pos != -1) && (net_pos != -1)) {
	    if (net_protocol == ARP) {
			std::cout << "Sintaxis erronea" << std::endl;
			exit(EXIT_FAILURE);
		} else if (net_protocol == RARP) {
			std::cout << "Sintaxis erronea" << std::endl;
			exit(EXIT_FAILURE);
		} else {
		}
	}

	/*Valido que net y -D no tengan choques como: 
	  -  ARP y RARP no pueden ir con -D*/
	if ((dst_ip_pos != -1) && (net_pos != -1)) {
		if (net_protocol == ARP) {
			std::cout << "Sintaxis erronea" << std::endl;
			exit(EXIT_FAILURE);
		} else if (net_protocol == RARP) {
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
		    char* only_numbers = strstr("0123456789",raw_number);
			if (only_numbers == NULL) {
				std::cout << "Sintaxis erronea" << std::endl;
				exit(EXIT_FAILURE);
			}
			number[count_numbers] = ip[j];
			count_numbers++;
			j++;
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
		char* only_numbers = strstr("0123456789",raw_number);
		if (only_numbers == NULL) {
			std::cout << "Sintaxis erronea" << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	int number;
	number = atoi((char*)port);

	if (number > 65535 || number < 1) {
		std::cout << "Sintaxis erronea" << std::endl;
		exit(EXIT_FAILURE);
	}
}

int search_terms(const char* first,int argc,char *argv[])
{
	int i;
	for(i = 0; i < argc; i++)
		if (strcmp(first,(const char*)argv[i]) == 0)
			return i;

	return -1;
}
