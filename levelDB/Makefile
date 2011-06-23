#
# SAMPLE MAKE FILE
#

TARGET = kvs
CC     = g++
CFLAGS = -I./ -I./kvs
OBJS   = kvs/kdb.o

all: $(OBJS)
	$(CC) $(CFLAGS) -lpthread kvs/$(TARGET).c -o lkvs $(OBJS) -lleveldb

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm lkvs *.o kvs/*.o
