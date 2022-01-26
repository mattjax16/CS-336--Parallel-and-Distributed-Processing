# Makefile for first project
CC = gcc
LFLAGS = -lm
CFLAGS =
SRC = src/
BIN = bin/

test_my_math :	src/test_my_math.c $(SRC)my_math.o
	$(CC) $(CFLAGS)  $(SRC)my_math.o -o $(BIN)test_my_math $(SRC)test_my_math.c $(LFLAGS)
	./$(BIN)test_my_math

clean :
	rm -rf *~ *.o test_my_math

# Inference rules
% : %.c
	$(CC) $(CFLAGS) -$(LFLAGS) -o $@ $^
