AFL_PATH = /home/m/mounlaur/AFL/afl-2.52b
ifdef USE_AFL
CC = $(AFL_PATH)/afl-gcc
else
CC = gcc
endif
CFLAGS = -g -Wall -Iinclude -fPIC $(OPTGCOV) -O2
SRC_DIR=src
INC_DIR=include
OBJ_DIR=obj
BIN_DIR=bin
LIB_DIR=lib
LD_FLAGS=-lm $(OPTGCOV)
OPTGCOV = -fprofile-arcs -ftest-coverage

# Options pour AddressSanitizer (ASan)
ifdef USE_ASAN
CFLAGS += -fsanitize=address
LD_FLAGS += -fsanitize=address
endif

# Options pour UndefinedBehaviorSanitizer (UBSan)
ifdef USE_UBSAN
CFLAGS += -fsanitize=undefined
LD_FLAGS += -fsanitize=undefined
endif

# Options pour JSON
ifdef FICJSON
CFLAGS += -DFICJSON
endif

# Options pour GCOV
ifdef USE_GCOV
OPTGCOV = -fprofile-arcs -ftest-coverage
else
OPTGCOV = 
endif

#options pour AFL
ifdef USE_AFL
CFLAGS += -fsanitize=address -fsanitize=undefined -O0
endif

SRCS = $(wildcard $(SRC_DIR)/*.c)   
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o,$(SRCS))

STATIC_LIB = $(LIB_DIR)/libdico.a 
SHARED_LIB = $(LIB_DIR)/libdico.so

TARGET = analyseur

all: $(BIN_DIR)/$(TARGET)

# Options pour créer la bibliothèque statique et dynamique
$(STATIC_LIB): $(OBJS)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^

$(SHARED_LIB): $(OBJS)
	@mkdir -p $(LIB_DIR)
	$(CC) $(CFLAGS) -shared -o $@ $^ -lgcov

# Compilation avec option
ifdef USE_STATIC
$(BIN_DIR)/$(TARGET): $(STATIC_LIB) $(SRC_DIR)/main.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/main.c -L$(LIB_DIR) -ldico $(LD_FLAGS)
else
$(BIN_DIR)/$(TARGET): $(SHARED_LIB) $(SRC_DIR)/main.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/main.c -L$(LIB_DIR) -ldico $(LD_FLAGS)
endif

ifdef USE_AFL
	AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1 AFL_SKIP_CPUFREQ=1 /home/m/mounlaur/AFL/afl-2.52b/afl-fuzz -m none -i in/ -o out/ ./bin/analyseur @@
endif

# Génération des objets
$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@mkdir -p obj
	$(CC) -c $(CFLAGS)  $< -o $@

clean:
	rm -f $(OBJS) $(BIN_DIR)/$(TARGET)


#AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1 AFL_SKIP_CPUFREQ=1 /home/m/mounlaur/AFL/afl-2.52b/afl-fuzz -m none -i in/ -o out/ ./bin/analyseur @@