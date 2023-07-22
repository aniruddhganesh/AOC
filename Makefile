CC := gcc
CFLAGS := -Wall -Werror

# Get the list of C files tracked by Git
SOURCES := $(shell git ls-files "*.c")
BIN_DIR := bin
BINARIES := $(addprefix $(BIN_DIR)/, $(SOURCES:.c=))

# Default target to build all binaries
all: $(BINARIES)

# Rule to build each binary
$(BIN_DIR)/%: %.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $@

# Create the bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean rule to remove the bin directory and all generated binaries
clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean
