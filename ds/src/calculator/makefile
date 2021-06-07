
TARGET = $(notdir $(shell pwd))
SHAREDLIB = libds.so
TEST_TARGET = $(TARGET)_test

SRC = .
INC = ../../include
BIN = ../../bin
LIB = /home/shelly/git/ds/lib
TEST = ../../test

OBJ = ../../obj
CC = gcc
CFLAGS =  -ansi -pedantic-errors -Wall -Wextra -g -I$(INC) 

OBJECTS = $(OBJ)/$(TARGET)/$(TARGET).o 
TEST_OBJECTS = $(OBJ)/$(TARGET)/$(TEST_TARGET).o 

#--------------source & test sourec files-------------#
TEST_SOURCE = $(TEST)/$(TEST_TARGET).c
SOURCE = $(SRC)/$(TARGET).c 

#----------------shared object flags------------------#
SOFLAG_FIRST = -c -fpic 
SOFLAG_SECOND = -shared -o
LDFLAGS = -L$(LIB) -Wl,-rpath=$(LIB) -l$(TARGET)
#----------------------------------------------------#


$(OBJECTS): $(SOURCE) $(INC)/$(TARGET).h
	$(CC) $(CFLAGS) $(SOFLAG_FIRST) $< -o $@

$(LIB)/$(SHAREDLIB): $(OBJECTS) $(SOURCE) 
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) $^ -o $@

$(BIN)/$(TARGET): $(TEST_SOURCE) $(LIB)/$(SHAREDLIB)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ 
	
$(TEST_OBJECTS).o: $(TEST_SOURCE) $(INC)/$(TARGET).h
		$(CC) $(CFLAGS) $< -c -o $(OBJ)/$(TARGET)/$@

.PHONY : build test so clean

build:
	@mkdir -p $(OBJ)/$(TARGET)  
	@make $(BIN)/$(TARGET)

test:
	@./$(BIN)/$(TARGET)
	
so:
	@mkdir -p $(OBJ)/$(TARGET)  
	@make $(LIB)/$(SHAREDLIB)

arc:
	ar -vr $(LIB)/libD_S.a $(OBJECTS)

clean :
	rm -f -r $(OBJECTS) $(BIN)/$(TARGET) $(LIB)/$(SHAREDLIB)

