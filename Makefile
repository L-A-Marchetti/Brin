CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -fstack-protector-strong
TARGET = brin
SRC = $(wildcard *.c)

.PHONY: all clean valgrind

all: format $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) -DBRIN_LITE -o $@ $(SRC)
	$(TARGET).exe

format:
	@astyle --recursive --max-code-length=70 --suffix=none --style=allman *.c

clean:
	del /Q *.o $(TARGET).exe 2>nul || rm -f *.o $(TARGET)