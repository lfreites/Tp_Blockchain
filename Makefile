PROGRAM=tp
CC=g++
CFLAGS=-Wall -pedantic -g


all:$(PROGRAM)

$(PROGRAM): main.o tnx.o input.o output.o cmdline.o sha256.o
	$(CC) $(CFLAGS) -o $(PROGRAM) main.o tnx.o input.o output.o cmdline.o sha256.o  $(LDFLAGS) 

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

sha256.o: sha256.cpp sha256.h
	$(CC) $(CFLAGS) -c sha256.cpp

clean:
	rm -vf  *.o $(PROGRAM)