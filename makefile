#
# File       : makefile
# Licence    : see LICENCE
# Maintainer : <your name here>
#

# Shell program used.
SHELL = /bin/sh

# Binaries directory.
BIN_DIR := bin

# Other directories.
SRC_DIR := src
OBJ_DIR := build
TEST_SRC_DIR := test

# File extensions.
SRC_EXT := cpp
OBJ_EXT := o

# Compiler and options.
CC = g++
CDEBUG = -g
OS := $(shell uname)
ifeq ($(OS), Linux)
    INC := -Isrc/
    LIBS := 
else ifeq ($(OS), Darwin)
    INC := -Isrc/
    LIBS := 
endif
CFLAGS = -lSDL2 -std=c++11 -Wall -O $(CDEBUG) $(INC)
LDFLAGS = -g

# Find all source file names.
SRC_FILES := $(wildcard $(SRC_DIR)/*.$(SRC_EXT))
# Generate object file names from source file names.
OBJ_FILES := $(patsubst $(SRC_DIR)/%.$(SRC_EXT), $(OBJ_DIR)/%.$(OBJ_EXT), $(SRC_FILES))
# Find all test source file names.
TEST_SRC_FILES := $(wildcard $(TEST_SRC_DIR)/*.$(SRC_EXT))
# Generate test object file names from test source file names.
TEST_OBJ_FILES := $(patsubst $(TEST_SRC_DIR)/%.$(SRC_EXT), $(OBJ_DIR)/%.$(OBJ_EXT), $(TEST_SRC_FILES))
# Generate test binary file names from test source file names.
TEST_BIN_FILES := $(patsubst $(TEST_SRC_DIR)/%.$(SRC_EXT), $(BIN_DIR)/%, $(TEST_SRC_FILES))


SRC_DIR_MIN := src/minwin/src
OBJ_DIR_MIN := src/minwin/build
TEST_SRC_DIR_MIN := src/minwin/test


SRC_FILES_MIN := $(wildcard $(SRC_DIR_MIN)/*.$(SRC_EXT))
# Generate object file names from source file names.
OBJ_FILES_MIN  := $(patsubst $(SRC_DIR_MIN)/%.$(SRC_EXT), $(OBJ_DIR_MIN)/%.$(OBJ_EXT), $(SRC_FILES_MIN))
# Find all test source file names.
TEST_SRC_FILES_MIN  := $(wildcard $(TEST_SRC_DIR_MIN)/*.$(SRC_EXT))
# Generate test object file names from test source file names.
TEST_OBJ_FILES_MIN  := $(patsubst $(TEST_SRC_DIR_MIN)/%.$(SRC_EXT), $(OBJ_DIR_MIN)/%.$(OBJ_EXT), $(TEST_SRC_FILES))
# Generate test binary file names from test source file names.
TEST_BIN_FILES_MIN := $(patsubst $(TEST_SRC_DIR_MIN)/%.$(SRC_EXT), $(BIN_DIR)/%, $(TEST_SRC_FILES))

$(OBJ_FILES): $(OBJ_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.$(SRC_EXT)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

# Generate executable test files.
.PHONY: all2
all: $(TEST_BIN_FILES_MIN)
$(BIN_DIR)/test_minwin: $(OBJ_DIR)/test_minwin.o
	mkdir -p $(BIN_DIR)
	$(CC) $^ $(LDFLAGS) -o $@


$(TEST_OBJ_FILES_MIN): $(OBJ_DIR)/%.$(OBJ_EXT): $(TEST_SRC_DIR)/%.$(SRC_EXT) 
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: all
all: $(TEST_BIN_FILES)

# Create test_vector
$(BIN_DIR)/test_vector: $(OBJ_DIR)/test_vector.o
	mkdir -p $(BIN_DIR)
	$(CC) $^ $(LDFLAGS) -o $@

# Create test_matrix
$(BIN_DIR)/test_matrix: $(OBJ_DIR)/test_matrix.o
	mkdir -p $(BIN_DIR)
	$(CC) $^ $(LDFLAGS) -o $@

$(BIN_DIR)/my_test: $(OBJ_DIR)/my_test.o
	mkdir -p $(BIN_DIR)
	$(CC) $^ $(LDFLAGS) -o $@



$(TEST_OBJ_FILES): $(OBJ_DIR)/%.$(OBJ_EXT): $(TEST_SRC_DIR)/%.$(SRC_EXT) 
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

# Cleaning.
.PHONY: clean
clean:
	$(RM) $(BIN_FILE)
	$(RM) $(OBJ_FILES)
	$(RM) $(TEST_BIN_FILES)
	$(RM) $(TEST_OBJ_FILES)

