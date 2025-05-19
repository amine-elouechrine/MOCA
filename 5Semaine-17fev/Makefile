CC = gcc
CFLAGS = -Wall -Iinclude -fPIC $(OPTGCOV) 
CFLAGS +=-g 
SRC_DIR=src
INC_DIR=include
OBJ_DIR=obj
BIN_DIR=bin
LIB_DIR=lib
LD_FLAGS=-lm $(OPTGCOV)
OPTGCOV = -fprofile-arcs -ftest-coverage

# Options pour JSON
ifdef FICJSON
CFLAGS += -DFICJSON
endif

ifdef USE_GCOV
OPTGCOV = -fprofile-arcs -ftest-coverage
else
OPTGCOV = 
endif

SRCS = $(wildcard $(SRC_DIR)/*.c)   
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o,$(SRCS))

STATIC_LIB = $(LIB_DIR)/libdico.a 
SHARED_LIB = $(LIB_DIR)/libdico.so

TARGET = analyseur

all: $(BIN_DIR)/$(TARGET)

# Options por créer la bibliothèque statique et dynamique
$(STATIC_LIB): $(OBJS)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^

$(SHARED_LIB): $(OBJS)
	@mkdir -p $(LIB_DIR)
	$(CC) -shared -o $@ $^ -lgcov

#Compilation avec option
ifdef USE_STATIC
$(BIN_DIR)/$(TARGET): $(STATIC_LIB) $(SRC_DIR)/main.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/main.c -L$(LIB_DIR) -ldico $(LD_FLAGS)
else
$(BIN_DIR)/$(TARGET): $(SHARED_LIB) $(SRC_DIR)/main.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/main.c -L$(LIB_DIR) -ldico $(LD_FLAGS)
endif

# objets 
$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@mkdir -p obj
	$(CC) -c $(CFLAGS)  $< -o $@

clean:
	rm -f $(OBJS) $(BIN_DIR)/$(TARGET)