



TARGET = $(notdir $(shell pwd))
SHAREDLIB = lib$(notdir $(shell pwd)).so
SHAREDLIB_REL = lib$(TARGET)_r

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
RELEASE_FLAGS =   -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 

OBJECTS = $(OBJ)/$(TARGET)/$(TARGET).o 
OBJECTS_REL = $(OBJ)/$(TARGET)/$(TARGET)_r.o 
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

$(OBJECTS): $(SOURCE)
	$(CC) $(CFLAGS) $(SOFLAG_FIRST) $< -o $@ 

$(LIB)/$(SHAREDLIB): $(OBJECTS)  
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) $^ -o $@ 

$(BIN)/$(TARGET_SINGLE): $(TEST_SOURCE) $(LIB)/$(SHAREDLIB)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ -lpthread

$(BIN)/$(TARGET): $(TEST_SOURCE) $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@ $(LIB)/libds.so -lm -lpthread




$(OBJECTS_REL): $(SOURCE)
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_FIRST) $< -o $@ 

$(LIB)/$(SHAREDLIB_REL).so: $(OBJECTS_REL)  
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_SECOND) $^ -o $@ 

$(BIN)/$(TARGET)_r: $(TEST_SOURCE) 
	$(CC) $(RELEASE_FLAGS) $(LDFLAGS) $< -o $@ $(LIB)/libds.so -lm




.PHONY :build test shared_obj shared_lib release release_single 
		update_debug update_release clean 

build:
	@mkdir -p $(OBJ)/$(TARGET)  
	@make shared_obj
	@make $(BIN)/$(TARGET)

build_single:
	@mkdir -p $(OBJ)/$(TARGET)  
	@make $(BIN)/$(TARGET_SINGLE)

test:
	@./$(BIN)/$(TARGET)

test_release:
	@./$(BIN)/$(TARGET)_r

release_so:
	@mkdir -p $(OBJ)/$(TARGET)
	@make $(LIB)/$(SHAREDLIB_REL).so

release:
	@mkdir -p $(OBJ)/$(TARGET)
	@make release_so
	@make $(BIN)/$(TARGET)_r

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
	@rm -f -r $(OBJECTS) $(BIN)/$(TARGET) $(BIN)/$(TARGET)_r $(BIN)/$(TARGET_SINGLE)
	@rm -f -r $(LIB)/$(SHAREDLIB) $(LIB)/$(SHAREDLIB_REL).so  $(OBJ)/$(TARGET)  $(OBJECTS_REL)

#$(TEST_OBJECTS).o: $(TEST_SOURCE) $(INC)/$(TARGET).h
#		$(CC) $(CFLAGS) $< -c -o $(OBJ)/$(TARGET)/$@
