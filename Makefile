#
#	Jaidev Bormann
#


SDL3_DIR = dependencies/SDL3
SDL3_INC = $(SDL3_DIR)/include
SDL3_LIB = $(SDL3_DIR)/lib

GLAD_DIR = dependencies/glad
GLAD_INC = $(GLAD_DIR)/include


SRC = src
OBJ = obj
BIN = bin

CC = gcc # replace with your compiler of choice I used gcc.
CFLAGS = -Wall -Wextra -I$(SDL3_INC) -I$(GLAD_INC)
LDFLAGS = -L$(SDL3_LIB) -llibSDL3


SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(SRCS:$(SRC)/%.c=$(OBJ)/%.o)
EXEC = $(BIN)/OhmGameAPI


all: $(EXEC)


$(EXEC): $(OBJS)
	$(CC) -o $(EXEC) $(OBJS) $(LDFLAGS)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@


run:
	./$(EXEC)


clean:
	rm -rf $(OBJ)/*.o $(EXEC)


.PHONY: all clean run
