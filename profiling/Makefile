CC=gcc
CFLAGS=-Wall -g -O2 -pg -fsanitize=address -fsanitize=undefined
all: writing mc-pi

writing: writing.c

mc-pi: mc-pi.c

clean:
	rm -f *.o writing mc-pi gmon.out
