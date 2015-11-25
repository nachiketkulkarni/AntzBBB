CC = gcc
CFLAGS = -I../../../include/
DEPS = xbee.h
LDLIBS = -lm
OBJ = test_xbee.o xbee.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test_xbee: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LDLIBS)

.PHONY: clean
clean:
	rm -rf *.o test_xbee
