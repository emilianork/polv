CC=g++
CFLAGS=-I.
PCAP=$(CFLAGS)
PCAP+=-lpcap
DEPS = packet/polv_packet.h data_link/polv_data_link.h queue/polv_queue.h tools/polv_types.h tools/polv_boolean.h network/polv_network.h transport/polv_transport.h tools/polv_tools.h network/polv_ip_v4.h network/polv_ip_v6.h network/polv_arp.h tools/polv_next_layer.h transport/polv_udp.h transport/polv_tcp.h transport/polv_icmp.h
OBJ = main.o packet/polv_packet.o data_link/polv_data_link.o network/polv_network.o transport/polv_transport.o queue/polv_queue.o tools/polv_tools.o tools/polv_next_layer.o network/polv_ip_v4.o network/polv_ip_v6.o network/polv_arp.o transport/polv_udp.o transport/polv_tcp.o transport/polv_icmp.o

%.o: %.cpp $(DEPS)
	$(CC) -c -g -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -g -o $@ $^ $(PCAP)

clean:
	rm $(OBJ) ./main
