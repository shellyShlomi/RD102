
TARGET = scheduler

INC = ../../include
BIN = ../../bin
LIB = ../../lib

OBJ = ../../obj
CC = gcc
CFLAGS =  -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)

OBJECTS =  $(OBJ)/$(TARGET)/$(TARGET).o  $(OBJ)/$(TARGET)/scheduler_test.o

# $(OBJ)/uid/uid.o $(OBJ)/priority_queue/priority_queue.o 
SOURCE = ./scheduler.c ../../test/scheduler_test.c ../$(PQ)/$(PQ).c ../uid/uid.c  ../task/task.c  ../sorted_ll/sorted_ll.c ../dll/dll.c



PQ = priority_queue



$(BIN)/$(TARGET): $(SOURCE) $(OBJ)/$(TARGET) $(OBJECTS) 
	$(CC) $(CFLAGS)  $(SOURCE) -o $(BIN)/$(TARGET)


$(OBJ)/$(TARGET)/scheduler.o: $(OBJ)/$(TARGET) $(INC)/$(TARGET).h
	$(CC) $(CFLAGS) ./scheduler.c -c -o $(OBJ)/$(TARGET)/scheduler.o
	
$(OBJ)/$(TARGET)/scheduler_test.o: $(OBJ)/$(TARGET) $(INC)/$(TARGET).h
		$(CC) $(CFLAGS) ../../test/scheduler_test.c -c -o $(OBJ)/$(TARGET)/scheduler_test.o

$(OBJ)/uid/uid.o: ../uid/uid.o $(INC)/uid.h
	$(CC) $(CFLAGS) ../uid/uid.c -c -o $(OBJ)/uid/uid.o


$(OBJ)/$(PQ)/$(PQ).o : ../$(PQ)/$(PQ).o $(INC)/$(PQ).h
	$(CC) $(CFLAGS) ../$(PQ)/$(PQ).c -c -o $(OBJ)/$(PQ)/$(PQ).o

$(OBJ)/scheduler:
	@mkdir -p $(OBJ)/$(TARGET)  

.PHONY :

release:
	$(CC) -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC)  $(SOURCE) -o $(BIN)/$(TARGET)

run:
	./$(BIN)/$(TARGET)
	
clean:
	rm -f -r $(OBJECTS) $(BIN)/$(TARGET) $(OBJ)/$(TARGET) $(OBJ)/$(TARGET)/scheduler_test.o
	
