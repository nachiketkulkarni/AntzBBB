CC = gcc
CFLAGS = -I../../../include/
DEPS = motor.h
OBJ = driver.o motor.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test_motor: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.o test_motor
