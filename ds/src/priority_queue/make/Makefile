
TARGET = dll

INC = ../../include
BIN = ../../bin
LIB = ../../lib

OBJ = ../../obj
CC = gcc
CFLAGS =  -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)

OBJECTS = $(OBJ)/$(TARGET)/dll.o $(OBJ)/$(TARGET)/dll_test.o
SOURCE = ./dll.c ../../test/dll_test.c 


$(BIN)/$(TARGET): $(SOURCE) $(OBJ)/$(TARGET)  $(OBJECTS) 
	$(CC) $(CFLAGS)  $(SOURCE)  -o $(BIN)/$(TARGET)
	
$(OBJ)/$(TARGET)/dll.o: $(OBJ)/$(TARGET) $(INC)/$(TARGET).h
	$(CC) $(CFLAGS) ./dll.c -c -o $(OBJ)/$(TARGET)/dll.o
	
$(OBJ)/$(TARGET)/dll_test.o: $(OBJ)/$(TARGET) $(INC)/$(TARGET).h
		$(CC) $(CFLAGS) ../../test/dll_test.c -c -o $(OBJ)/$(TARGET)/dll_test.o


$(OBJ)/dll :
	@mkdir -p $(OBJ)/$(TARGET)  
	

.PHONY : 
run:
	./$(BIN)/$(TARGET)
clean :
	rm -f -r $(OBJECTS) $(BIN)/$(TARGET) $(OBJ)/$(TARGET)
	
