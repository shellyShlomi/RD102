
TARGET = uid

INC = ../../include
BIN = ../../bin
LIB = ../../lib

OBJ = ../../obj
CC = gcc
CFLAGS =  -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)

OBJECTS =  $(OBJ)/$(TARGET)/$(TARGET).o  $(OBJ)/$(TARGET)/uid_test.o
SOURCE = ./uid.c ../../test/uid_test.c 




$(BIN)/$(TARGET): $(SOURCE) $(OBJ)/$(TARGET) $(OBJECTS) 
	$(CC) $(CFLAGS)  $(SOURCE) -o $(BIN)/$(TARGET)


$(OBJ)/$(TARGET)/uid.o: $(OBJ)/$(TARGET) $(INC)/$(TARGET).h
	$(CC) $(CFLAGS) ./uid.c -c -o $(OBJ)/$(TARGET)/uid.o
	
$(OBJ)/$(TARGET)/uid_test.o: $(OBJ)/$(TARGET) $(INC)/$(TARGET).h
		$(CC) $(CFLAGS) ../../test/uid_test.c -c -o $(OBJ)/$(TARGET)/uid_test.o

$(OBJ)/uid:
	@mkdir -p $(OBJ)/$(TARGET)  


.PHONY :

release:
	$(CC) -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC)  $(SOURCE) -o $(BIN)/$(TARGET)

run:
	./$(BIN)/$(TARGET)
	
clean:
	rm -f -r $(OBJECTS) $(BIN)/$(TARGET) $(OBJ)/$(TARGET) $(OBJ)/$(TARGET)/uid_test.o
	
