
TARGET = sorts

INC = ../../include
BIN = ../../bin
LIB = ../../lib

OBJ = ../../obj
CC = gcc
CFLAGS =  -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)

OBJECTS = $(OBJ)/$(TARGET)/$(TARGET).o $(OBJ)/$(TARGET)/$(TARGET)_test.o
SOURCE = ./$(TARGET).c ../../test/$(TARGET)_test.c 


$(BIN)/$(TARGET): $(SOURCE) $(OBJ)/$(TARGET)  $(OBJECTS) 
	$(CC) $(CFLAGS)  $(SOURCE)  -o $(BIN)/$(TARGET)
	
$(OBJ)/$(TARGET)/$(TARGET).o: $(OBJ)/$(TARGET) $(INC)/$(TARGET).h
	$(CC) $(CFLAGS) ./$(TARGET).c -c -o $(OBJ)/$(TARGET)/$(TARGET).o
	
$(OBJ)/$(TARGET)/$(TARGET)_test.o: $(OBJ)/$(TARGET) $(INC)/$(TARGET).h
		$(CC) $(CFLAGS) ../../test/$(TARGET)_test.c -c -o $(OBJ)/$(TARGET)/$(TARGET)_test.o

	
$(OBJ)/$(TARGET)/$(TARGET)_test_eden.o: $(OBJ)/$(TARGET) $(INC)/$(TARGET).h
		$(CC) $(CFLAGS) ../../test/$(TARGET)_test_eden.c -c -o $(OBJ)/$(TARGET)/$(TARGET)_test_eden.o
		
$(OBJ)/$(TARGET) :
	@mkdir -p $(OBJ)/$(TARGET)  

.PHONY :
eden:
	make -f ./make/Makefile
arc:
	ar -vr $(LIB)/$(TARGET).a $(OBJECTS)

run:
	./$(BIN)/$(TARGET)

aclean :
	rm -f -r $(LIB)/$(TARGET).a

clean :
	rm -f -r $(OBJECTS) $(BIN)/$(TARGET) $(OBJ)/$(TARGET)

