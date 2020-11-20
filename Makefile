CARGS  = -g -Wall
CFLAGS = -I. $(CARGS)
CC = g++

all: tp.exe

tp.exe: main.cc tnx.cpp input.cpp output.cpp cmdline.cc tnx.h input.h output.h cmdline.h utils.h proof_of_work.cpp sha256.cpp sha256.h bloque.cpp bloque.h proof_of_work.h
	$(CC) $(CFLAGS) -o tp.exe main.cc tnx.cpp input.cpp output.cpp cmdline.cc proof_of_work.cpp sha256.cpp tnx.h input.h output.h cmdline.h utils.h sha256.h bloque.cpp bloque.h proof_of_work.h

clean:
	$(RM) -vf *.o *.exe *.t *.out *.err
