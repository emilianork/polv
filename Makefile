BIN_PATH = bin/

polv:
	mkdir $(BIN_PATH)
	make -C src polv
	mv src/polv bin/polv

clean:
	make -C src clean
	rm -r $(BIN_PATH)
