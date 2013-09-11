CC=g++
CFLAGS=-I.
PCAP=$(CFLAGS)
PCAP+=-lpcap
DEPS = polv_packet.h data_link/polv_data_link.h queue/polv_queue.h tools/polv_types.h tools/polv_boolean.h network/polv_network.h transport/polv_transport.h tools/polv_tools.h network/polv_ip_v4.h network/polv_ip_v6.h network/polv_arp.h
OBJ = main.o polv_packet.o polv_data_link.o polv_network.o polv_transport.o polv_queue.o polv_tools.o polv_ip_v4.o polv_ip_v6.o polv_arp.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(PCAP)

clean:
	rm $(OBJ) ./main
