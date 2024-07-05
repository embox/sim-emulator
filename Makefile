CC = gcc
CPPFLAGS = -I./include
CFLAGS += -g
LIBS = -lssl -lcrypto

files := simcard-em.o filesystem.o simfs.o

all: simcard-em emulator architecture/eIM architecture/IoTDevice/IPAd 

simcard-em: simcard-em.o filesystem.o simfs.o
	$(CC) simcard-em.o filesystem.o simfs.o -o simcard-em

architecture/eIM: architecture/eIM.c
	$(CC) architecture/eIM.c -o architecture/eIM $(LIBS)

architecture/SM-DPPlus: architecture/SM-DPPlus.c
	$(CC) architecture/SM-DPPlus.c -o architecture/SM-DPPlus $(LIBS)

architecture/IoTDevice/IPAd: architecture/IoTDevice/IPAd.c
	$(CC) architecture/IoTDevice/IPAd.c -o architecture/IoTDevice/IPAd $(LIBS)

emulator: emulator.c
	$(CC) emulator.c -o emulator

simfs.o: simfs.c MF translatefs.py
	./translatefs.py
	$(CC) -c $(CFLAGS) $(CPPFLAGS) simfs.c -o simfs.o

%.o : %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm -f *.o simcard-em emulator architecture/eIM architecture/SM-DPPlus architecture/IoTDevice/IPAd

.PHONY: all clean

