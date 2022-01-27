# Makefile for first
CC = gcc
LFLAGS = -lm -lpthread 
CFLAGS =
SRC = src/
BIN = bin/
benford_sequential :	$(SRC)benford_sequential.c $(SRC)my_timing.o
	$(CC) $(CFLAGS) $(SRC)my_timing.o -o $(BIN)benford_sequential $(SRC)benford_sequential.c $(LFLAGS)
	./$(BIN)benford_sequential


benford_sequential_val :	$(SRC)benford_sequential.c $(SRC)my_timing.o
	$(CC) $(CFLAGS) $(SRC)my_timing.o -o $(BIN)benford_sequential $(SRC)benford_sequential.c $(LFLAGS)
	valgrind ./$(BIN)benford_sequential

clean :
	rm -rf *~ *.o benford_sequential

# Inference rules
%.o : %.c
	$(CC) $(CFLAGS)-c -o $@ $^
