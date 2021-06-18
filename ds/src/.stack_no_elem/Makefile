



TARGET = $(notdir $(shell pwd))
SHAREDLIB = lib$(notdir $(shell pwd)).so
TEST_TARGET = $(TARGET)_test

TARGET_SINGLE = $(notdir $(shell pwd))_single


SRC = .
INC = ../../include
BIN = ../../bin
LIB = /home/shelly/git/ds/lib
TEST = ../../test

OBJ = ../../obj
CC = gcc
CFLAGS =  -ansi -pedantic-errors -Wall -Wextra -g -I$(INC) 
RELEASE_FLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 

OBJECTS = $(OBJ)/$(TARGET)/$(TARGET).o 
TEST_OBJECTS = $(OBJ)/$(TARGET)/$(TEST_TARGET).o 

#--------------source & test sourec files-------------#
TEST_SOURCE = $(TEST)/$(TEST_TARGET).c
SOURCE = $(SRC)/$(TARGET).c 

#----------------shared object flags------------------#
SOFLAG_FIRST = -c -fpic 
SOFLAG_SECOND = -shared
LDFLAGS = -L$(LIB) -Wl,-rpath=$(LIB) -lds

#----------------auto dependency----------------------#


#----------------------------------------------------#

$(OBJECTS).c: $(SOURCE)
	$(CC) $(CFLAGS) $(SOFLAG_FIRST) $< -o $@ 

$(LIB)/$(SHAREDLIB): $(OBJECTS)  
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) $^ -o $@ 

$(BIN)/$(TARGET_SINGLE): $(TEST_SOURCE) $(LIB)/$(SHAREDLIB)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ 



$(BIN)/$(TARGET): $(TEST_SOURCE) $(LIB)/libds.so
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ 


.PHONY :build test shared_obj shared_lib release release_single 
		update_debug update_release clean 

build:
	$(shell cd ../../ make libds) 
	@mkdir -p $(OBJ)/$(TARGET)  
	@make $(BIN)/$(TARGET)

build_single:
	@mkdir -p $(OBJ)/$(TARGET)  
	@make $(BIN)/$(TARGET_SINGLE)

test:
	@./$(BIN)/$(TARGET)

rel:
	$(CFLAGS) = $(RELEASE_FLAGS)

release:
	@mkdir -p $(OBJ)/$(TARGET)  
	@make rel
	@make $(BIN)/$(TARGET)

release_single:
	@mkdir -p $(OBJ)/$(TARGET)
	@make rel
	@make $(BIN)/$(TARGET_SINGLE)



shared_obj:
	@mkdir -p $(OBJ)/$(TARGET)  
	@cd ../../ @make libds 
	@make $(LIB)/$(SHAREDLIB)


update_debug:
	@make clean
	@make shared_obj



update_release:
	@make clean





clean :
	rm -f -r $(OBJECTS) $(BIN)/$(TARGET) $(LIB)/$(SHAREDLIB) $(OBJ)/$(TARGET) $(LIB)/libds.so 








#$(TEST_OBJECTS).o: $(TEST_SOURCE) $(INC)/$(TARGET).h
#		$(CC) $(CFLAGS) $< -c -o $(OBJ)/$(TARGET)/$@
