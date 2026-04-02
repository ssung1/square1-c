CC := cc
CFLAGS := -Wall -Wextra -Wpedantic -std=c11
TARGET := square1
SRC := main.c block.c block-color.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
