#include <cstdlib>
#include <pcap.h>
#include <iostream>

#include "io/polv_io.h"
#include "packet/polv_packet.h"

#define DEVICE_MODIFIER "-i\0"

void callback (u_char*, const struct pcap_pkthdr*, const u_char*);

int main(int argc, char *argv[]) {

  char *dev;                       // Nombre de la interfaz de la que se capturaran los paquetes
  char errbuf[PCAP_ERRBUF_SIZE];   // Texto de error de libpcap
  pcap_t *handler;                 // Manejador de sesion de libpcap
  int count_pack;                  // Numero de paquetes que seran capturados
  
  int offline;                     // Leer de archivo
  char *fileName;                  // Nombre de archivo donde se escribira
  pcap_dumper_t *pcap_file;        // Archivo donde se guardaran las capturas

  dev = argv[1];
  count_pack = atoi(argv[2]);
  if(argc >= 4) {
    if(argc == 4) {
      fileName = argv[3];
      offline = 0;
    } else {
      offline = 1;
      fileName = argv[4];
    }
  } else {
    fileName = NULL;
  }

  if(offline) {
    printf("Archivo: %s\n", fileName);
    handler = pcap_open_offline(fileName, errbuf);
  } else {
    printf("Interfaz de red: %s\n", dev);
    handler = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf); // Abrimos la interfaz de red para capturar
  }

  if(handler == NULL) {
    if(offline) {
      fprintf(stderr, "No se pudo abrir el archivo %s: %s\n", fileName, errbuf);
    } else {
      fprintf(stderr, "No se pudo abrir la interfaz de red %s: %s\n", dev, errbuf);
    }
    return(2);
  }

  if(fileName == NULL) {
    printf("Se capturaran %d paquetes\n\n\n", count_pack);
    pcap_loop(handler, count_pack, callback, NULL);  // Capturamos count_pack paquetes
  } else {
    if(offline) {
      pcap_loop(handler, -1, callback, NULL);  // Capturamos count_pack paquetes
    } else {
      pcap_file = pcap_dump_open(handler, fileName);
      if(pcap_file == NULL) {
        fprintf(stderr,"\nError opening output file\n");
        return(2);
      }
  
      printf("Se capturaran %d paquetes y se guardaran en %s\n\n\n", count_pack, fileName);
      pcap_loop(handler, count_pack, callback, (u_char*) pcap_file);  // Capturamos count_pack paquetes
    }
  }
  
  printf("\n\nFINALIZANDO\n");
  pcap_close(handler);  // Cerramos la sesion  

  return EXIT_SUCCESS;
}

void callback(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
  // Se aplica el filtro
  
  // Se parsea el paquete si paso el filtro
	struct polv_packet* polv_p;	
	polv_p = polv_packet_create(packet, header->len);

  // Imprime en archivo o en stdout
  if(args == NULL) {
    write_packet(polv_p);
  } else {
    pcap_dump(args, header, packet);   
  }
}
