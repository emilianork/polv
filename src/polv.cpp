#include <cstdlib>
#include <pcap.h>
#include <iostream>

#include "io/polv_io.h"
#include "packet/polv_packet.h"
#include "filter/polv_filter.h"

const char* device_term = "-i\0";
const char* readFile_term = "-r\0";
const char* count_term = "-c\0";
const char* writeFile_term = "-w\0";

void callback (u_char*, const struct pcap_pkthdr*, const u_char*);

char** extern_argv;
int extern_argc;

int main(int argc, char *argv[]) {

	extern_argv = argv;
	extern_argc = argc;
	
	polv_validate_filter(argc,argv);
	
  char errbuf[PCAP_ERRBUF_SIZE];   // Texto de error de libpcap
  char *dev;                       // Nombre de la interfaz de la que se capturaran los paquetes
  char *readFileName;              // Nombre de archivo donde se leera
  char *writeFileName;             // Nombre de archivo donde se escribira
  pcap_dumper_t *pcap_file;        // Archivo donde se guardaran las capturas
  pcap_t *handler;                 // Manejador de sesion de libpcap
  int count_pack;                  // Numero de paquetes que seran capturados

  // Buscamos los primeros modificadores
  int index_device_term = search_terms(device_term, argc, argv);
  int index_readFile_term = search_terms(readFile_term, argc, argv);
  
  if(index_device_term != -1 && index_readFile_term != -1) {
    fprintf(stderr, "Solo se debe de especificar una fuente de paquetes (interfaz o archivo)\n");
    return(2);
  }
  
  // Determinando de donde sacaremos los paquetes
  if(index_device_term != -1) {
    // Se guarda la interfaz especificada por el usuario
    dev = argv[index_device_term + 1];
    readFileName = NULL;
    
  } else if(index_readFile_term != -1) {
    // Se especifico un archivo para leer
    readFileName = argv[index_readFile_term + 1];
    
  } else {
    // El usuario no indico una interfaz ni un archivo para leer entonces se intenta asignar una
    dev = pcap_lookupdev(errbuf);
    if(dev == NULL) {
      fprintf(stderr, "No se encontro una interfaz de red disponible: %s\n", errbuf);
      return(2);
    }
    readFileName = NULL;
  }
  
  int index_writeFile_term = search_terms(writeFile_term, argc, argv);
  if(index_writeFile_term != -1) {
    writeFileName = argv[index_writeFile_term + 1];
  } else {
    writeFileName = NULL;
  }
  
  int index_count_term = search_terms(count_term, argc, argv);
  if(index_count_term != -1) {
    count_pack = atoi(argv[index_count_term + 1]);
  } else {
    count_pack = -1;
  }
  
  // Iniciando el programa
  
  // Abrimos nuestra fuente de paquetes
  if(readFileName != NULL) {
    printf("\nArchivo: %s\n", readFileName);
    handler = pcap_open_offline(readFileName, errbuf);
  } else {
    printf("\nInterfaz de red: %s\n", dev);
    handler = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
  }
    
  // Caso de que no se haya podido abrir la fuente de paquetes
  if(handler == NULL) {
    if(readFileName != NULL) {
      fprintf(stderr, "No se pudo abrir el archivo %s: %s\n", readFileName, errbuf);
    } else {
      fprintf(stderr, "No se pudo abrir la interfaz de red %s: %s\n", dev, errbuf);
    }
    return(2);
  }
  
  // Abrimos archivo para escribir si se requirio
  if(writeFileName != NULL) {
    pcap_file = pcap_dump_open(handler, writeFileName);
    
    if(pcap_file == NULL) {
      fprintf(stderr, "No se puede escribir en el archivo %s: %s\n", writeFileName, errbuf);
      return(2);
    }
  }
  
  // Comienzan las capturas
  if(readFileName != NULL) {
    if(writeFileName != NULL) {
      pcap_loop(handler, -1, callback, (u_char*) pcap_file);
    } else {
      pcap_loop(handler, -1, callback, NULL);
    }
  } else {
    if(writeFileName != NULL) {
      pcap_loop(handler, count_pack, callback, (u_char*) pcap_file);
    } else {
      pcap_loop(handler, count_pack, callback, NULL);
    }
  }
  
  printf("\n.: ADIOS :.\n");
  pcap_close(handler);  // Cerramos la sesion  

  return EXIT_SUCCESS;
}

void callback(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
	struct polv_packet* p;	
	if (polv_filter(packet,header->len,extern_argc,extern_argv)) {
		p = polv_packet_create(packet, header->len);
		
		// Imprime en archivo o en stdout
		if(args == NULL) {
			write_packet(p);
		} else {
			pcap_dump(args, header, packet);   
		}
		polv_packet_destroy(p);
	}
}
