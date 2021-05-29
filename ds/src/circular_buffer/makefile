
TARGET = circular_buffer

INC = ../../include
BIN = ../../bin
LIB = ../../lib

OBJ = ../../obj
CC = gcc
CFLAGS =  -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)

OBJECTS =  $(OBJ)/$(TARGET)/$(TARGET).o $(OBJ)/$(TARGET)/circular_buffer.o
SOURCE = ./circular_buffer.c ../../test/circular_buffer_test.c 




$(BIN)/$(TARGET): $(SOURCE) $(OBJ)/$(TARGET)  $(OBJECTS) 
	$(CC) $(CFLAGS)  $(SOURCE)  -o $(BIN)/$(TARGET)


$(OBJ)/$(TARGET)/circular_buffer.o: $(OBJ)/$(TARGET) $(INC)/$(TARGET).h
	$(CC) $(CFLAGS) ./circular_buffer.c -c -o $(OBJ)/$(TARGET)/circular_buffer.o
	
$(OBJ)/$(TARGET)/circular_buffer_test.o: $(OBJ)/$(TARGET) $(INC)/$(TARGET).h
		$(CC) $(CFLAGS) ../../test/circular_buffer_test.c -c -o $(OBJ)/$(TARGET)/circular_buffer_test.o


$(OBJ)/circular_buffer:
	@mkdir -p $(OBJ)/$(TARGET)  


.PHONY : 
run:
	./$(BIN)/$(TARGET)
clean :
	rm -f -r $(OBJECTS) $(BIN)/$(TARGET) $(OBJ)/$(TARGET)
	
