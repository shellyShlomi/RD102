
TARGET = queue

INC = ../../include
BIN = ../../bin
LIB = ../../lib

OBJ = ../../obj
CC = gcc
CFLAGS =  -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)

OBJECTS = $(OBJ)/sll/sll.o $(OBJ)/$(TARGET)/queue.o $(OBJ)/$(TARGET)/queue_test.o
SOURCE = ./queue.c ../sll/sll.c ../../test/queue_test.c 




$(BIN)/$(TARGET): $(SOURCE) $(OBJ)/sll  $(OBJ)/$(TARGET)  $(OBJECTS) 
	$(CC) $(CFLAGS)  $(SOURCE)  -o $(BIN)/$(TARGET)

$(OBJ)/sll/sll.o: $(OBJ)/sll $(INC)/sll.h
	$(CC) $(CFLAGS) ../sll/sll.c  -c -o $(OBJ)/sll/sll.o
	
	
$(OBJ)/$(TARGET)/queue.o: $(OBJ)/$(TARGET) $(INC)/$(TARGET).h
	$(CC) $(CFLAGS) ./queue.c -c -o $(OBJ)/$(TARGET)/queue.o
	
$(OBJ)/$(TARGET)/queue_test.o: $(OBJ)/$(TARGET) $(INC)/$(TARGET).h
		$(CC) $(CFLAGS) ../../test/queue_test.c -c -o $(OBJ)/$(TARGET)/queue_test.o


$(OBJ)/queue :
	@mkdir -p $(OBJ)/$(TARGET)  
	
$(OBJ)/sll:
	@mkdir -p $(OBJ)/sll


.PHONY : 
run:
	./$(BIN)/$(TARGET)
clean :
	rm -f -r $(OBJECTS) $(BIN)/$(TARGET) $(OBJ)/sll $(OBJ)/$(TARGET)
	
