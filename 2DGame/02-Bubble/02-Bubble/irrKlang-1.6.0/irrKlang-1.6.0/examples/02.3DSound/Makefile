CPP = g++
OPTS =  -I"../../include" -L"/usr/lib" ../../bin/linux-gcc/libIrrKlang.so -pthread

all: example

example:
	$(CPP) main.cpp -m32 -o example $(OPTS)
	@echo ""
	@echo "Note: to start: This example needs mp3 playback and to find the mp3 plugin for this. Please start this example with bin/linux-gcc/ as working directory."
	@echo ""
	@echo "Alternative: run 'make run' now."

clean:
	rm example

run:	example
	cd ../../bin/linux-gcc/ && ../../examples/02.3DSound/example && cd ../../examples/02.3DSound

	

	
