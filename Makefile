# Compiler
CC = gcc

# Default flags
CFLAGS = -Wall -lm

# Execution command
all: 
	$(CC) $(CFLAGS) table.c -o table

clean:
	rm table
