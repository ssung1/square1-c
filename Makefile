CC := cc
CFLAGS := -Wall -Wextra -Wpedantic -std=c11
TARGET := square1
SRC := main.c block.c block-color.c shape.c cube-face.c
UNIT_TEST_SRC := unit-test.c block.c block-color.c shape.c cube-face.c

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

unit-test: $(UNIT_TEST_SRC)
	$(CC) $(CFLAGS) -o unit-test $(UNIT_TEST_SRC)

test: unit-test
	./unit-test

clean:
	rm -f $(TARGET) unit-test
