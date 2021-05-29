
TARGET = queue_two_stacks

INC = ../../ds/include
BIN = ../../ds/bin
LIB = ../../ds/lib
SRC = ../../ds/src
OBJ = ./
CC = gcc
CFLAGS =  -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)

OBJECTS = $(OBJ)/$(TARGET)/$(TARGET).o 
SOURCE = ./$(TARGET).c $(SRC)/stack.c


./$(TARGET): $(SOURCE) $(OBJ)/$(TARGET)  $(OBJECTS) 
	$(CC) $(CFLAGS)  $(SOURCE)  -o $(BIN)/$(TARGET)
	
./$(TARGET).o: $(OBJ)/$(TARGET) $(INC)/$(TARGET).h
	$(CC) $(CFLAGS) $(SOURCE) -c -o $(OBJ)/$(TARGET)/$(TARGET).o


.PHONY : 

run:
	./$(TARGET)


clean :
	rm -f -r ./$(OBJECTS) ./$(TARGET) 

