/*
  José Emiliano Cabrera Blancas
  Diego Andrés Gómez Montesinos 
  
  Encabezado con funciones exclusivas la lectura y escritura de los paquetes.
*/

#ifndef POLV_IO_H_
#define POLV_IO_H_

#include <stdio.h>

#include "packet/polv_packet.h"
#include "data_link/polv_data_link.h"
#include "network/polv_network.h"
#include "network/polv_ip_v4.h"
#include "network/polv_ip_v6.h"
#include "network/polv_arp.h"

/* Macros para las funciones */
#define WRITE_TO_FILE 0
#define WRITE_TO_STDOUT 1
#define BYTES_PER_LINE 16


/* Funciones de escritura*/

void write_packet(struct polv_packet*);
void write_data_link(struct polv_data_link*);
void write_network(struct polv_network*);
void write_ipv4(struct polv_ip_v4*);
void write_ipv6(struct polv_ip_v6*);
void write_arp(struct polv_arp*);
void write_transport(struct polv_transport*);
void write_udp(struct polv_udp*);
void write_icmp(struct polv_icmp*);
void write_tcp(struct polv_tcp*);
void write_raw_data(const u_char*, int);

/* Funciones de lectura */
void read_file(FILE*);

/*Funciones auxiliares */
void write_hex(const u_char*, const char*, int);
void write_int(const u_char*, const char*, int);
int read_ascii(char*, const u_char*, int, int);
int read_hex(char*, const u_char*, int, int);

#endif POLV_IO_H_
