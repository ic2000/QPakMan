CC=gcc
MY_CFLAGS=-c -I./include -std=gnu11 -Wall -Wextra -Wno-unused-variable -Wno-missing-field-initializers

OBJECTS=qpakman.o argparse.o

qpakman: $(OBJECTS)
	$(CC) -Wall -Wextra -o qpakman $(OBJECTS)
	
qpakman.o: src/qpakman.c
	$(CC) $(MY_CFLAGS) src/qpakman.c

argparse.o: src/argparse.c
	$(CC) $(MY_CFLAGS) src/argparse.c
	
clean:
	rm qpakman $(OBJECTS)