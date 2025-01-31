CC = gcc
CFLAGS = -Wall

# Options pour JSON
ifdef FICJSON
CFLAGS += -DFICJSON
endif

SRCS = main.c dico.c word.c hash.c json.c
OBJS = $(SRCS:.c=.o)
TARGET = analyseur


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)