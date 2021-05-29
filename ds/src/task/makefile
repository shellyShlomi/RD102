
TARGET = task

INC = ../../include
BIN = ../../bin
LIB = ../../lib

OBJ = ../../obj
CC = gcc
CFLAGS =  -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)

OBJECTS =  $(OBJ)/$(TARGET)/$(TARGET).o  $(OBJ)/$(TARGET)/task_test.o
SOURCE = ./task.c ../../test/task_test.c ../uid/uid.c




$(BIN)/$(TARGET): $(SOURCE) $(OBJ)/$(TARGET) $(OBJECTS) 
	$(CC) $(CFLAGS)  $(SOURCE) -o $(BIN)/$(TARGET)


$(OBJ)/$(TARGET)/task.o: $(OBJ)/$(TARGET) $(INC)/$(TARGET).h
	$(CC) $(CFLAGS) ./task.c -c -o $(OBJ)/$(TARGET)/task.o
	
$(OBJ)/$(TARGET)/task_test.o: $(OBJ)/$(TARGET) $(INC)/$(TARGET).h
		$(CC) $(CFLAGS) ../../test/task_test.c -c -o $(OBJ)/$(TARGET)/task_test.o

$(OBJ)/task:
	@mkdir -p $(OBJ)/$(TARGET)  


.PHONY :

release:
	$(CC) -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC)  $(SOURCE) -o $(BIN)/$(TARGET)

run:
	./$(BIN)/$(TARGET)
	
clean:
	rm -f -r $(OBJECTS) $(BIN)/$(TARGET) $(OBJ)/$(TARGET) $(OBJ)/$(TARGET)/task_test.o
	
