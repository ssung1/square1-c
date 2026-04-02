CC := cc
CFLAGS := -Wall -Wextra -Wpedantic -std=c11
TARGET := square1
UNIT_TEST_TARGET := unit-test
SRC := main.c block.c block-color.c
UNIT_TEST_SRC := unit-test.c block.c block-color.c

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

unit-test: $(UNIT_TEST_TARGET)

$(UNIT_TEST_TARGET): $(UNIT_TEST_SRC)
	$(CC) $(CFLAGS) -o $(UNIT_TEST_TARGET) $(UNIT_TEST_SRC)

test: $(UNIT_TEST_TARGET)
	./$(UNIT_TEST_TARGET)

clean:
	rm -f $(TARGET) $(UNIT_TEST_TARGET)
