CC=gcc
CFLAGS=-O2 -g -Wall
OPTFLAGS=-O3 -g -Wall
OBJS=driver.o baseline.o rdtsc.o

all:baseline

baseline:$(OBJS)
	$(CC) -o $@ $^

baseline.o: baseline.c
	$(CC) $(OPTFLAGS) -D NOOPT -c $< -o $@

clean:
	rm -rf $(OBJS) baseline
