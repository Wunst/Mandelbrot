CC = gcc
CCFLAGS = -c -ggdb -I"include"

LD = gcc
LDFLAGS = -lm -ldl -lglfw

build: compile link
	rm $(shell find src -name "*.o")

compile:
	for f in $(shell find src -name "*.c") ; do \
		$(CC) -o $$f.o $$f $(CCFLAGS) ; \
	done

link:
	$(LD) -o Mandelbrot $(shell find src -name "*.o") $(LDFLAGS)
