CC=g++
CFLAGS=-I.
PCAP=$(CFLAGS)
PCAP+=-lpcap

PACKET_DEPS = packet/polv_packet.h
PACKET_OBJ = packet/polv_packet.o

DATA_LINK_DEPS = data_link/polv_data_link.h 
DATA_LINK_OBJ = data_link/polv_data_link.o 

NETWORK_DEPS = network/polv_network.h network/polv_ip_v4.h network/polv_ip_v6.h network/polv_arp.h
NETWORK_OBJ = network/polv_network.o network/polv_ip_v4.o network/polv_ip_v6.o network/polv_arp.o

TRANSPORT_DEPS = transport/polv_transport.h transport/polv_udp.h transport/polv_tcp.h transport/polv_icmp.h
TRANSPORT_OBJ = transport/polv_transport.o transport/polv_udp.o transport/polv_tcp.o transport/polv_icmp.o

IO_DEPS = io/polv_io.h
IO_OBJ = io/polv_io.o

FILTER_DEPS = filter/polv_filter.h
FILTER_OBJ = filter/polv_filter.o

TOOLS_DEPS = tools/polv_types.h tools/polv_boolean.h  tools/polv_tools.h tools/polv_next_layer.h
TOOLS_OBJ =  tools/polv_tools.o tools/polv_next_layer.o

QUEUE_DEPS =  queue/polv_queue.h
QUEUE_OBJ =  queue/polv_queue.o

POLV_OBJ = polv.o

BIN_PATH = bin/

DEPS = $(PACKET_DEPS) $(DATA_LINK_DEPS) $(NETWORK_DEPS) $(TRANSPORT_DEPS) $(IO_DEPS) $(FILTER_DEPS) $(TOOLS_DEPS)

OBJ = $(POLV_OBJ) $(PACKET_OBJ) $(DATA_LINK_OBJ) $(NETWORK_OBJ) $(TRANSPORT_OBJ) $(IO_OBJ) $(FILTER_OBJ) $(TOOLS_OBJ)

%.o: %.cpp $(DEPS)
	$(CC) -c -w  -o $@ $< $(CFLAGS)	

polv: $(OBJ)
	$(CC) -w -o $@ $^ $(PCAP)

clean:
	rm $(OBJ)
