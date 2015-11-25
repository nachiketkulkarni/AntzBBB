CC = gcc
CFLAGS = -I../../../include/ -g
DEPS = lcd.h
OBJ = test_lcd.o lcd.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test_lcd: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.o test_lcd
