CC = gcc
CFLAGS = -I../../../include/
DEPS = bluetooth.h
OBJ = test_bluetooth.o bluetooth.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test_bluetooth: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.o test_bluetooth
