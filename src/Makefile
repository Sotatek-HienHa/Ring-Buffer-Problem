CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2

LIBNAME = ringbuffer.a
SRC = ringbuffer.c
OBJ = $(SRC:.c=.o)

all: $(LIBNAME)

$(LIBNAME): $(OBJ)
	ar rcs $(LIBNAME) $(OBJ)

%.o: %.c ringbuffer.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(LIBNAME)