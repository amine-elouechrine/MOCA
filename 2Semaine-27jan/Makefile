CC = gcc
CFLAGS = -Wall -Iinclude
SRC_DIR=src
INC_DIR=include
OBJ_DIR=obj
BIN_DIR=bin
LD_FLAGS=-lm

# Options pour JSON
ifdef FICJSON
CFLAGS += -DFICJSON
endif

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o,$(SRCS))
TARGET = analyseur


all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJS)
	$(CC)  $(OBJS) -o $(BIN_DIR)/$(TARGET)  $(LD_FLAGS)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS)  $< -o $@

clean:
	rm -f $(OBJS) $(BIN_DIR)/$(TARGET)