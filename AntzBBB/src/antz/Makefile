CC = gcc
CFLAGS = -I. -I../include/
DEPS = ant1.h
LD_LIB_PATH = -L../libs/
LIBS = -lrobotutils -lm
OBJ = ant1.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ant1: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LD_LIB_PATH) $(LIBS)

.PHONY: clean
clean:
	rm -rf *.o ant1
