
TARGET = $(notdir ${PWD})

SRC = .
BIN = ../../bin
INC = ../../include
OBJ = ../../obj/$(TARGET)
LIB = ../../lib

TEST = ../../test

CC = gcc
#gd flags
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)

SOURCE = $(wildcard $(SRC)/*.c $(TEST)/$(TARGET)*.c)
OBJECT = $(patsubst %,$(OBJ)/%, $(notdir $(SOURCE:.c=.o)))


$(BIN)/$(TARGET) : $(OBJECT) 
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ)/%.o : $(SRC)/%.c 
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/%.o : $(TEST)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJECT): |$(OBJ)

$(OBJ):
	mkdir -p $@ 
.PHONY: help run clean tree release dir
dir:
	@mkdir -p $(OBJ)
archive:
	$(AR) r $(LIB)/$(TARGET).a $(OBJECT)
tree:
	@tree ../../

release: CFLAGS=-WALL -ansi -pedantic-errors -WALL -Wextra -DNDEBUG -o3
run:
	./$(BIN)/$(TARGET)
clean:
	rm -f $(OBJECT) $(BIN)/$(TARGET)

help:
	@echo "src: $(SOURCE)"
	@echo "obj: $(OBJECT)"
	@echo "exe: $(BIN)"
	
	@echo "test: $(TEST)/$(TARGET)"
