# Handy Python Privacy Scripts - Makefile
# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c99 -g
CPPFLAGS := -I./include

# Directories
BUILD_DIR := build
BIN_DIR := bin
OBJ_DIR := $(BUILD_DIR)/obj

# Main executable
TARGET := $(BIN_DIR)/main

# Source files
SOURCES := main.c \
           src/Core/Credential_Generator/Credential_Generator.c \
           src/Core/Timezone_Manager/Timezone_Manager.c \
           src/Core/Webpage_Downloader/Webpage_Downloader.c \
           src/Core/Writing_Anonymiser/Writing_Anonymiser.c \
           src/Modules/random.c

# Object files
OBJECTS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SOURCES))

# Default target
.PHONY: all
all: $(TARGET)

# Create directories
$(BUILD_DIR) $(BIN_DIR) $(OBJ_DIR):
	@mkdir -p $@

# Build subdirectories in OBJ_DIR
$(OBJ_DIR)/src $(OBJ_DIR)/src/Core $(OBJ_DIR)/src/Core/Credential_Generator $(OBJ_DIR)/src/Core/Timezone_Manager $(OBJ_DIR)/src/Core/Webpage_Downloader $(OBJ_DIR)/src/Core/Writing_Anonymiser $(OBJ_DIR)/src/Modules: | $(OBJ_DIR)
	@mkdir -p $@

# Compile source files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)/src $(OBJ_DIR)/src/Core $(OBJ_DIR)/src/Core/Credential_Generator $(OBJ_DIR)/src/Core/Timezone_Manager $(OBJ_DIR)/src/Core/Webpage_Downloader $(OBJ_DIR)/src/Core/Writing_Anonymiser $(OBJ_DIR)/src/Modules
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Link executable
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@
	@echo "✓ Build complete: $@"

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

# Help
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  make all       - Build the project (default)"
	@echo "  make clean     - Remove build artifacts"
	@echo "  make rebuild   - Clean and rebuild"
	@echo "  make run       - Build and run the executable"
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
