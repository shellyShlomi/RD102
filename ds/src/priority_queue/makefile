
TARGET = priority_queue

INC = ../../include
BIN = ../../bin
LIB = ../../lib

OBJ = ../../obj
CC = gcc
CFLAGS =  -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)

OBJECTS =  $(OBJ)/$(TARGET)/$(TARGET).o  $(OBJ)/$(TARGET)/priority_queue_test.o
SOURCE =    ./priority_queue.c ../../test/priority_queue_test.c 





$(BIN)/$(TARGET): $(SOURCE) $(OBJ)/$(TARGET) $(OBJECTS) 
	$(CC) $(CFLAGS)  $(SOURCE) -o $(BIN)/$(TARGET)


$(OBJ)/$(TARGET)/priority_queue.o: $(OBJ)/$(TARGET) $(INC)/$(TARGET).h
	$(CC) $(CFLAGS) ./priority_queue.c -c -o $(OBJ)/$(TARGET)/priority_queue.o
	
$(OBJ)/$(TARGET)/priority_queue_test.o: $(OBJ)/$(TARGET) $(INC)/$(TARGET).h
		$(CC) $(CFLAGS) ../../test/priority_queue_test.c -c -o $(OBJ)/$(TARGET)/priority_queue_test.o


$(OBJ)/priority_queue:
	@mkdir -p $(OBJ)/$(TARGET)  


.PHONY :

mkexd:
	$(CC) $(CFLAGS)  $(SOURCE) -o $(BIN)/$(TARGET)
	
mkexr:
	$(CC) -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC)

arc:
	ar -vr $(LIB)/priority_queue.a $(OBJ)/$(TARGET)/$(TARGET).o $(OBJ)/sorted_ll/sorted_ll.o $(OBJ)/dll/dll.o
	

release:
	$(CC) -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC)  $(SOURCE) -o $(BIN)/$(TARGET)

aclean :
	rm -f -r $(LIB)/priority_queue.a


run:
	./$(BIN)/$(TARGET)
	
clean:
	rm -f -r $(OBJECTS) $(BIN)/$(TARGET) $(OBJ)/$(TARGET) $(OBJ)/$(TARGET)/priority_queue_test.o
	
