
TARGET = fsa

INC = ../../include
BIN = ../../bin
LIB = ../../lib

OBJ = ../../obj
CC = gcc
CFLAGS =  -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)

OBJECTS = $(OBJ)/$(TARGET)/fsa.o $(OBJ)/$(TARGET)/fsa_test.o
SOURCE = ./fsa.c ../../test/fsa_test.c 


$(BIN)/$(TARGET): $(SOURCE) $(OBJ)/$(TARGET)  $(OBJECTS) 
	$(CC) $(CFLAGS)  $(SOURCE)  -o $(BIN)/$(TARGET)
	
$(OBJ)/$(TARGET)/fsa.o: $(OBJ)/$(TARGET) $(INC)/$(TARGET).h
	$(CC) $(CFLAGS) ./fsa.c -c -o $(OBJ)/$(TARGET)/fsa.o
	
$(OBJ)/$(TARGET)/fsa_test.o: $(OBJ)/$(TARGET) $(INC)/$(TARGET).h
		$(CC) $(CFLAGS) ../../test/fsa_test.c -c -o $(OBJ)/$(TARGET)/fsa_test.o


$(OBJ)/fsa :
	@mkdir -p $(OBJ)/$(TARGET)  

.PHONY : 
arc:
	ar -vr $(LIB)/fsa.a $(OBJECTS)
run:
	./$(BIN)/$(TARGET)

aclean :
	rm -f -r $(LIB)/fsa.a

clean :
	rm -f -r $(OBJECTS) $(BIN)/$(TARGET) $(OBJ)/$(TARGET)

