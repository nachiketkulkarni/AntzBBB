CC = gcc
CFLAGS = -I../../../include/
DEPS = infrared.h
OBJ = test_infrared.o infrared.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test_infrared: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.o test_infrared
