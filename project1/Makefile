# Makefile for first project
CC = gcc
LFLAGS = -lm
CFLAGS =

test_my_math :	test_my_math.c my_math.o
	$(CC) $(CFLAGS) $(LFLAGS) my_math.o -o test_my_math test_my_math.c

clean :
	rm -rf *~ *.o test_my_math

# Inference rules
% : %.c
	$(CC) $(CFLAGS) -$(LFLAGS) -o $@ $^
