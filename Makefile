$(CC) = gcc
CPPFLAGS = -I./include
CFLAGS += -g

files := simcard-em.o filesystem.o simfs.o

simcad-em: $(files)
	$(CC) $(files) -o simcard-em

simfs.o: simfs.c MF translatefs.py
	./translatefs.py
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

%.o : %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm -f *.o
