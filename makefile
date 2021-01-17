CFLAGS = -std=c99 -Wall -pedantic D-DLIST  
CC =gcc

all: list.o


array.o: list.c
	$(CC) $(CFLAGS) -c list.c -o $@
	

clean: 
	rm -i  list.o 
