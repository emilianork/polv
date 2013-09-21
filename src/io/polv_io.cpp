#include "io/polv_io.h"

#include <cstdlib>
#include <cstring>
#include <time.h>

void write_packet(struct polv_packet* p) {
  printf("\n>>>>>>>>>>>>>>>>>>>> PAQUETE <<<<<<<<<<<<<<<<<<<<\n");
  
  write_data_link(p->data_link);
  write_network(p->network);
  write_transport(p->transport);
    
  if (p->raw_data != NULL) {
    write_raw_data(p->raw_data, p->raw_data_len);
  } else {
    printf("\nPaquete sin datos.\n");
  }
}

void write_data_link(struct polv_data_link* data_link) {
  printf("::::: ENLACE\n");
  if (data_link == NULL) {
    printf("Protocolo de enlace no reconocido\n");
    return;
	}
	
	// Imprime el protocolo y sus datos
	switch (data_link->type) {
	  case V802:
	    printf("Version Ethernet: %s | ", "802");
	    
	    printf("Longitud: ");
	    write_hex(data_link->ethertype, "", TYPE_LEN);
	    
	    printf(" | DSAP: ");
	    write_hex(data_link->dsap, "", DSAP_LEN);
	    printf(" | SSAP: ");
	    write_hex(data_link->ssap, "", SSAP_LEN);
	    printf(" | CONTROL: ");
	    write_hex(data_link->control, "", CONTROL_LEN);
	    printf(" | ORG_CODE: ");
	    write_hex(data_link->org_code, "", ORG_CODE);
	    break;
	  case VII:
	    printf("Version Ethernet: %s | ", "Ethernet II");
	    printf("Tipo: ");
	    write_hex(data_link->ethertype, "", TYPE_LEN);
	    break;
	}
	
	// Imprime las MAC
	printf("\nMAC ADDRESS: ");
  write_hex(data_link->src, ":", MAC_ADDRESS - 1);
  printf("%02x%s", data_link->src[MAC_ADDRESS - 1], "");  // MAC source
  printf(" > ");
  write_hex(data_link->dst, ":", MAC_ADDRESS - 1);
  printf("%02x%s", data_link->src[MAC_ADDRESS - 1], ""); // MAC dest
  
  printf("\n");
  return;
}

void write_network(struct polv_network* network) {
  printf("\n::::: RED <");
  
  if (network == NULL) {
    printf("Protocolo de red no reconocido\n");
    return;
	}
	
	switch(network->protocol) {
	  case IPV4:
	  write_ipv4((struct polv_ip_v4*) network->header);
		break;
	case IPV6:
	  write_ipv6((struct polv_ip_v6*) network->header);
	  break;
	case ARP:
	  write_arp((struct polv_arp*) network->header);
	  break;
	}
	
  printf("\n");
	return;
}

void write_ipv4(struct polv_ip_v4* ip) {
  printf("IPv4>\n");
  
  // Imprimiendo las IPs
 	write_int(ip->src_addr, ".", SRC_ADDR_LEN - 1);
  printf("%d%s", ip->src_addr[SRC_ADDR_LEN - 1], "");
	printf(" > ");
 	write_int(ip->dst_addr, ".", DST_ADDR_LEN - 1);
  printf("%d%s", ip->dst_addr[DST_ADDR_LEN - 1], "");
	
	// Imprimiendo el contenido de la cabecera
  printf("\nIHL: ");
	write_int(ip->ihl, "", IHL_LEN);

	printf(" | Type service: ");
	write_int(ip->type_service, "", TYPE_SERVICE);
	
	printf(" | Len: ");
	write_int(ip->len, "", LEN_LEN);

	printf(" | Identificacion: ");
	write_int(ip->identification, "", IDENTIFICATION_LEN);

	printf(" | Flags: ");
	write_int(ip->flags, "", FLAGS_LEN);

	printf(" | Offset: ");
	write_int(ip->fragment_offset, "", FRAGMENT_OFFSET_LEN);

	printf(" | Time to live: ");
	write_int(ip->time_to_live, "", TIME_TO_LIVE_LEN);
	
	printf(" | Protocol: ");
	write_int(ip->protocol, "", PROTOCOL_LEN);

	printf(" | Header Check: ");
	write_int(ip->header_check, "", HEADER_CHECK_LEN);

	return;
}

void write_ipv6(struct polv_ip_v6* ip) {
  printf("IPv6>\n");
  
  // Imprimiendo las IPs
 	write_int(ip->src_addr, ".", SRC_ADDR_V6_LEN - 1);
  printf("%d%s", ip->src_addr[SRC_ADDR_V6_LEN - 1], "");
	printf(" > ");
 	write_int(ip->dst_addr, ".", DST_ADDR_V6_LEN - 1);
  printf("%d%s", ip->dst_addr[DST_ADDR_V6_LEN - 1], "");
	
	// Imprimiendo los demas valores de la cabecera
	printf("\nTraffic Class: ");
	write_int(ip->traffic_class, "", TRAFFIC_CLASS_LEN);

	printf(" | Flow Label: ");
	write_int(ip->flow_label, "", FLOW_LABEL_LEN);
	
	printf(" | Payload_len: ");
	write_int(ip->payload_len, "", PAYLOAD_LEN_LEN);
	
	printf(" | Next header: ");
	write_int(ip->next_header, "", NEXT_HEADER_LEN);

	printf(" | Hop Limit: ");
	write_int(ip->hop_limit, "", HOP_LIMIT_LEN);
}

void write_arp(struct polv_arp* arp) {
  printf("ARP>\n");
  	
	printf(" HTYPE: ");
	write_int(arp->htype, "", HTYPE_LEN);

	printf(" | PTYPE: ");
	write_int(arp->ptype, "", PTYPE_LEN);

	printf(" | HLEN: ");
	write_int(arp->hlen, "", HLEN_LEN);
	
	printf(" | PLEN: ");
	write_int(arp->plen, "", PLEN_LEN);

	printf(" | OPER: ");
	write_int(arp->oper, "", OPER_LEN);
	
	printf(" | SHA: ");
	write_int(arp->sha, "", SHA_LEN);
	
	printf(" | SPA: ");
	write_int(arp->spa, "", SPA_LEN);

	printf(" | THA: ");
	write_int(arp->tha, "", THA_LEN);

	printf(" | TPA: ");
	write_int(arp->tpa, "", TPA_LEN);
	
	return;
}

void write_transport(struct polv_transport* transport) {
  printf("\n::::: TRANSPORTE <");
  
  if (transport == NULL) {
    printf("Protocolo de transporte no reconocido\n");
    return;
	}
	
	switch(transport->protocol) {
	  case UDP:
	    write_udp((struct polv_udp*) transport->header);
	    break;
	  case ICMP:
	    write_icmp((struct polv_icmp*) transport->header);
	    break;
	  case TCP:
	    write_tcp((struct polv_tcp*) transport->header);
	    break;
	}
	
	printf("\n");
	return;
}

void write_udp(struct polv_udp* udp) {
  printf("UDP>\n");
  
  printf(" Source Port: ");
	write_int(udp->src_port, "", SRC_PORT_UDP_LEN);

	printf(" | Dest Port: ");
	write_int(udp->dst_port, "", DST_PORT_UDP_LEN);

	printf(" | Length: ");
	write_int(udp->len, "",LEN_UDP_LEN);

	printf(" | Checksum: ");
	write_int(udp->checksum, "", CHECKSUM_UDP_LEN); 
  
  return;
}

void write_icmp(struct polv_icmp* icmp) {
  printf("ICMP\n");
  
  printf("Type: ");
	write_int(icmp->type, "", TYPE_ICMP_LEN);

	printf(" | Code: ");
	write_int(icmp->code, "", CODE_ICMP_LEN);

	printf(" | Checksum: ");
	write_int(icmp->checksum, "", CHECKSUM_ICMP_LEN);
  
  return;
}

void write_tcp(struct polv_tcp* tcp) {
  printf("TCP>\n");
  
  printf("Source Port: ");
	write_int(tcp->src_port, "", SRC_PORT_TCP_LEN);

	printf(" | Dest Port: ");
	write_int(tcp->dst_port, "", DST_PORT_TCP_LEN);

	printf(" | Seq: ");
	write_int(tcp->seq, "", SEQ_TCP_LEN);

	printf(" | Ack: ");
	write_int(tcp->ack, "", ACK_TCP_LEN);

	printf(" | Offset: ");
	write_int(tcp->offset, "", OFFSET_TCP_LEN);

	printf(" | Reserved: ");
	write_int(tcp->reserved, "", RESERVED_TCP_LEN);

	printf(" | Flags: ");
	write_int(tcp->flags, "", FLAGS_TCP_LEN);

	printf(" | Window: ");
	write_int(tcp->window, "", WINDOW_TCP_LEN);

	printf(" | Checksum: ");
	write_int(tcp->checksum, "", CHECKSUM_TCP_LEN);

	printf(" | Urgent: ");
	write_int(tcp->urgent, "", URGENT_TCP_LEN);

  return;
}

void write_raw_data(const u_char* raw_data, int raw_data_len) {
  printf("\n");
  
  char* str_ascii = (char*) malloc(BYTES_PER_LINE);
  char* str_hex = (char*) malloc(BYTES_PER_LINE * 3);
  
  int i;
  for(i = 0; i < raw_data_len; i += BYTES_PER_LINE) {
    read_hex(str_hex, raw_data, i, BYTES_PER_LINE);
    read_ascii(str_ascii, raw_data, i, BYTES_PER_LINE);
    
    printf("\t0x%04x:  ", i);
    printf("%s  ", str_hex);
    printf("%s\n", str_ascii);
  }
  if((i - BYTES_PER_LINE) < raw_data_len) {
    read_hex(str_hex, raw_data, i, raw_data_len - (i - BYTES_PER_LINE));
    read_ascii(str_ascii, raw_data, i, raw_data_len - (i - BYTES_PER_LINE));
    
    printf("\t0x%04x:  ", i);
    printf("%s  ", str_hex);
    printf("%s\n", str_ascii);
  }
  
  return;
}

//////////////////////////////////////////////////////////////////////

void read_file(FILE*) {
  return;
}

/////////////////////////////////////////////////////////////////////

void write_hex(const u_char* content, const char* separator, int len) {
	int i;
	for(i = 0; i < len; i++) {
	  printf("%02x%s", content[i], separator);
	}
	
	return;
}

void write_int(const u_char* content, const char* separator, int len) {
	int i;
	for(i = 0; i < len; i++) {
	  printf("%d%s", content[i], separator);
	}
	
	return;
}

int read_ascii(char* buffer, const u_char* content, int init, int len) {
  int i;
  for(i = 0; i < len; i++) {
    if(content[init + i] >= 32 && content[init + i] <= 126) {
      buffer[i] = (char) content[init + i];
    } else {
      buffer[i] = '.';
    }
  }
  buffer[len] = '\0';
  
  return len;
}

int read_hex(char* buffer, const u_char* content, int init, int len) {
  char str_aux[3];
  
  int i;
  int j = 0;
  for(i = 0; i < len; i++) {
    sprintf(str_aux, "%02x", content[init + i]);
    
    if(i % 2 == 0 && i != 0) {
      buffer[j] = (char) 32;;
      j++;
    }
    
    buffer[j] = str_aux[0];
    buffer[j + 1] = str_aux[1];
    
    j += 2;
  }
  buffer[j + 1] = '\0';
  
  return len * 2;
}
