PROD_DIR := ./product
BUILD_DIR :=./build

PROD_EXEC = main
PROD_DIRS := $(PROD_DIR)
PROD_FILES := $(wildcard $(patsubst %,%/*.cpp, $(PROD_DIRS)))
HEADER_PROD_FILES := $(wildcard $(patsubst %,%/*.h, $(PROD_DIRS)))
PROD_INC_DIRS=-I$(PROD_DIR)

CC=g++
SYMBOLS=-Wall -Werror -g -pedantic -O0 -pthread

.PHONY: clean

all: $(PROD_EXEC)

$(PROD_EXEC): Makefile $(PROD_FILES)  $(HEADER_FILES)
	@$(CC) $(PROD_INC_DIRS) $(SYMBOLS) $(PROD_FILES) -o $(BUILD_DIR)/$(PROD_EXEC)

run: $(PROD_EXEC)
	@./$(BUILD_DIR)/$(PROD_EXEC) 217.105.47.86

local: $(PROD_EXEC)
	@./$(BUILD_DIR)/$(PROD_EXEC) 127.0.0.1

clean:
	rm -rf $(BUILD_DIR)/$(PROD_EXEC)*
