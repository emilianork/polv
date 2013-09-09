CC=g++
CFLAGS=-I.
PCAP=$(CFLAGS)
PCAP+=-lpcap
DEPS = polv_packet.h polv_data_link.h polv_queue.h polv_types.h polv_boolean.h  polv_network.h polv_transport.h polv_tools.h polv_ip_v4.h polv_ip_v6.h polv_arp.h
OBJ = main.o polv_packet.o polv_data_link.o polv_network.o polv_transport.o polv_queue.o polv_tools.o polv_ip_v4.o polv_ip_v6.o polv_arp.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(PCAP)

clean:
	rm $(OBJ) ./main
