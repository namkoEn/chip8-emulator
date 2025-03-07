# Compiler and Flags
CC = clang
CFLAGS = -Wall -Wextra -O2 -std=c11

# Source Files
SRC = src/main.c src/chip8.c src/display.c
TEST_SRC = src/test.c src/chip8.c src/display.c

# Object Files
OBJ = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

# Binaries
TARGET = chip8
TEST_TARGET = test_chip8

# Default target (build emulator)
all: $(TARGET)

# Build the CHIP-8 emulator
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Build the test binary
$(TEST_TARGET): $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) -o $(TEST_TARGET)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run unit tests
test: $(TEST_TARGET)
	./$(TEST_TARGET) roms/test.rom

# Clean up object files and binaries
clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TEST_TARGET)