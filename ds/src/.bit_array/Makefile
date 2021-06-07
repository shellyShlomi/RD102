
TARGET = $(notdir $(shell pwd))
SHAREDLIB = lib$(notdir $(shell pwd)).so
TEST_TARGET = $(TARGET)_test

SRC = .
INC = ../../include
BIN = ../../bin
LIB = /home/shelly/git/ds/lib
TEST = ../../test

OBJ = ../../obj
CC = gcc
CFLAGS =  -ansi -pedantic-errors -Wall -Wextra -g -I$(INC) 
RELEASE_FLAGS =  -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 

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

$(BIN)/$(TARGET): $(TEST_SOURCE) $(LIB)/libds.so
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ 
	
$(TEST_OBJECTS).o: $(TEST_SOURCE) $(INC)/$(TARGET).h
		$(CC) $(CFLAGS) $< -c -o $(OBJ)/$(TARGET)/$@
		
$(BIN)/$(TARGET)_rel: $(TEST_SOURCE) $(LIB)/lib$(TARGET).so
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ 

$(OBJ)/$(TARGET)/$(TARGET)_rel.o: $(SOURCE) $(INC)/$(TARGET).h
	$(CC) $(CFLAGS) $(SOFLAG_FIRST) $< -o $@

$(LIB)/$(SHAREDLIB)_rel.so: $(OBJECTS) $(SOURCE) 
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) $^ -o $@

.PHONY : build test so clean release

build:
	@mkdir -p $(OBJ)/$(TARGET)  
	@make $(BIN)/$(TARGET)

test:
	@./$(BIN)/$(TARGET)

release:
CFLAGS = $(RELEASE_FLAGS)

$(OBJ)/$(TARGET)/$(TARGET)_rel.o: $(SOURCE) $(INC)/$(TARGET).h
	$(CC) $(CFLAGS) $(SOFLAG_FIRST) $< -o $@

$(LIB)/$(SHAREDLIB)_rel.so: $(OBJECTS) $(SOURCE) 
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) $^ -o $@

$(BIN)/$(TARGET)_rel: $(TEST_SOURCE) $(LIB)/lib$(TARGET).so
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ 

so:
	@mkdir -p $(OBJ)/$(TARGET)  
	@make $(LIB)/$(SHAREDLIB)

clean :
	rm -f -r $(OBJECTS) $(BIN)/$(TARGET) $(LIB)/$(SHAREDLIB) $(OBJ)/$(TARGET) $(LIB)/libds.so $(BIN)/$(TARGET)_rel $(OBJ)/$(TARGET)/$(TARGET)_rel.o $(LIB)/$(SHAREDLIB)_rel

