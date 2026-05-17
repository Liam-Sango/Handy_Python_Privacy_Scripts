# Credential Generator - Makefile
# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c99 -g
CPPFLAGS := -I./include
LDFLAGS := -lssl -lcrypto -licuuc -licudata -licuio

# Directories
BUILD_DIR := build
BIN_DIR := bin
OBJ_DIR := $(BUILD_DIR)/obj

# Main executable
TARGET := $(BIN_DIR)/main

# Source files
SOURCES := main.c \
           src/Core/Credential_Generator/Credential_Generator.c \
           src/Core/Credential_Generator/random/random.c \
           src/Core/Credential_Generator/file/file.c

# Object files
OBJECTS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SOURCES))

# Test sources and targets
TEST_SOURCES := tests/test_random_utf8.c
TEST_OBJECTS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(TEST_SOURCES))
TEST_RANDOM_OBJECT := $(OBJ_DIR)/src/Core/Credential_Generator/random/random.o
TEST_BINARY := $(BIN_DIR)/test_random_utf8
TEST_LDFLAGS := $(LDFLAGS)

# Default target
.PHONY: all
all: $(TARGET)

# Create directories
$(BUILD_DIR) $(BIN_DIR) $(OBJ_DIR):
	@mkdir -p $@

# Build subdirectories in OBJ_DIR
$(OBJ_DIR)/src $(OBJ_DIR)/src/Core $(OBJ_DIR)/src/Core/Credential_Generator $(OBJ_DIR)/src/Core/Credential_Generator/random $(OBJ_DIR)/src/Core/Credential_Generator/file $(OBJ_DIR)/tests: | $(OBJ_DIR)
	@mkdir -p $@

# Compile source files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)/src $(OBJ_DIR)/src/Core $(OBJ_DIR)/src/Core/Credential_Generator $(OBJ_DIR)/src/Core/Credential_Generator/random $(OBJ_DIR)/src/Core/Credential_Generator/file $(OBJ_DIR)/tests
	$(CC) $(CPPFLAGS) $(CFLAGS) -I. -c $< -o $@

# Link executable
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "✓ Build complete: $@"

# Link test binary
$(TEST_BINARY): $(TEST_OBJECTS) $(TEST_RANDOM_OBJECT) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(TEST_LDFLAGS)
	@echo "✓ Test build complete: $@"

# Clean build artifacts
.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "✓ Clean complete"

# Rebuild
.PHONY: rebuild
rebuild: clean all

# Run the executable
.PHONY: run
run: $(TARGET)
	@./$(TARGET)

# Build and run tests
.PHONY: test
test: $(TEST_BINARY)
	@./$(TEST_BINARY)
	@echo ""

# Help
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  make all       - Build the project (default)"
	@echo "  make clean     - Remove build artifacts"
	@echo "  make rebuild   - Clean and rebuild"
	@echo "  make run       - Build and run the executable"
	@echo "  make test      - Build and run tests"
	@echo "  make help      - Show this help message"

# Debug target - print variables
.PHONY: debug
debug:
	@echo "CC: $(CC)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "CPPFLAGS: $(CPPFLAGS)"
	@echo "TARGET: $(TARGET)"
	@echo "SOURCES: $(SOURCES)"
	@echo "OBJECTS: $(OBJECTS)"
