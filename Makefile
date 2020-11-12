PROGRAM=tp
CC=g++
CFLAGS=-Wall -pedantic -g


all:$(PROGRAM)

$(PROGRAM): main.o tnx.o input.o output.o cmdline.o
	$(CC) $(CFLAGS) -o $(PROGRAM) main.o tnx.o input.o output.o cmdline.o  $(LDFLAGS) 

main.o: main.cpp tnx.h input.h output.h
	$(CC) $(CFLAGS) -c main.cpp

tnx.o: tnx.cpp input.h output.h
	$(CC) $(CFLAGS) -c tnx.cpp

input.o: input.cpp input.h utils.h
	$(CC) $(CFLAGS) -c input.cpp

output.o: output.cpp output.h
	$(CC) $(CFLAGS) -c output.cpp

cmdline.o: cmdline.cc cmdline.h
	$(CC) $(CFLAGS) -c cmdline.cc

clean:
	rm -vf  *.o $(PROGRAM)