CC=g++
CFLAGS=-I.
DEPS = polv_packet.h polv_data_link.h polv_queue.h polv_types.h polv_boolean.h  polv_network.h polv_transport.h
OBJ = main.o polv_packet.o polv_data_link.o polv_network.o polv_transport.o polv_queue.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm $(OBJ) ./main
