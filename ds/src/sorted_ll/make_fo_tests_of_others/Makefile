
TARGET = sorted_ll

INC = ../../include
BIN = ../../bin
LIB = ../../lib

OBJ = ../../obj
CC = gcc
CFLAGS =  -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)

OBJECTS =  $(OBJ)/$(TARGET)/$(TARGET).o $(OBJ)/$(TARGET)/sorted_ll.o 
SOURCE = ./sorted_ll.c ../../test/sorted_ll_testo.c $(OBJ)/dll/dll.o 




$(BIN)/$(TARGET): $(SOURCE) $(OBJ)/$(TARGET) $(OBJECTS) $(OBJ)/dll/dll.o 
	$(CC) $(CFLAGS)  $(SOURCE) -o $(BIN)/$(TARGET)


$(OBJ)/$(TARGET)/sorted_ll.o: $(OBJ)/$(TARGET) $(INC)/$(TARGET).h
	$(CC) $(CFLAGS) ./sorted_ll.c -c -o $(OBJ)/$(TARGET)/sorted_ll.o
	
$(OBJ)/$(TARGET)/sorted_ll_testo.o: $(OBJ)/$(TARGET) $(INC)/$(TARGET).h
		$(CC) $(CFLAGS) ../../test/sorted_ll_testo.c -c -o $(OBJ)/$(TARGET)/sorted_ll_testo.o

$(OBJ)/sorted_ll:
	@mkdir -p $(OBJ)/$(TARGET)  

$(OBJ)/dll:
	@mkdir -p $(OBJ)/dll 

.PHONY : 
run:
	./$(BIN)/$(TARGET)
clean :
	rm -f -r $(OBJECTS) $(BIN)/$(TARGET) $(OBJ)/$(TARGET)
	
