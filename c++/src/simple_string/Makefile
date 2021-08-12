



TARGET = $(notdir $(shell pwd))
SHAREDLIB = lib$(notdir $(shell pwd)).so
SHAREDLIB_REL = lib$(TARGET)_r

TEST_TARGET = $(TARGET)_test

TARGET_SINGLE = $(notdir $(shell pwd))_single


SRC = .
LIB = ../../lib
TEST = ../../test
INC = ../../include
BIN = ../../bin

OBJ = ../../obj
CC = g++
CFLAGS = -std=c++98 -pedantic-errors -Wall -Wextra -g -I$(INC) 
RELEASE_FLAGS =  -std=c++98 -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 


OBJECTS = $(OBJ)/$(TARGET)/$(TARGET).o 
OBJECTS_REL = $(OBJ)/$(TARGET)/$(TARGET)_r.o 
TEST_OBJECTS = $(OBJ)/$(TARGET)/$(TEST_TARGET).o 

#--------------source & test sourec files-------------#
TEST_SOURCE = $(TEST)/$(TEST_TARGET).cpp
SOURCE = $(SRC)/$(TARGET).cpp 

#----------------shared object flags------------------#
SOFLAG_FIRST = -c -fpic 
SOFLAG_SECOND = -shared
LDFLAGS = -L$(LIB) -Wl,-rpath=$(LIB) -lcla

#---------------- debuging ----------------------#

VLG		= valgrind --leak-check=yes --track-origins=yes
HLG		= valgrind --tool=helgrind --history-level=approx
CGDB	= cgdb

#----------------------------------------------------#

$(OBJECTS): $(SOURCE)
	$(CC) $(CFLAGS) $(SOFLAG_FIRST) $< -o $@ 

$(LIB)/$(SHAREDLIB): $(OBJECTS)  
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) $^ -o $@ 

$(BIN)/$(TARGET_SINGLE): $(TEST_SOURCE) $(LIB)/$(SHAREDLIB)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ -lpthread

$(BIN)/$(TARGET): $(TEST_SOURCE) $(OBJECTS) $(LIB)/libcla.so
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@ $(LIB)/$(SHAREDLIB)  -lm -lpthread




$(OBJECTS_REL): $(SOURCE)
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_FIRST) $< -o $@ 

$(LIB)/$(SHAREDLIB_REL).so: $(OBJECTS_REL)  
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_SECOND) $^ -o $@ 

$(BIN)/$(TARGET)_r: $(TEST_SOURCE) 
	$(CC) $(RELEASE_FLAGS) $(LDFLAGS) $< -o $@ $(LIB)/libcla.so -lm

$(LIB)/libcla.so: $(OBJECTS)
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) $(shell find $(OBJ)/*/. -type f -regex ".*\.o")  -o $(LIB)/libcla.so



.PHONY :build test vlgT hlgT shared_obj shared_lib release release_single 
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

vlgT:
	@$(VLG) ./$(BIN)/$(TARGET)

hlgT:
	@$(HLG) ./$(BIN)/$(TARGET)

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
	@make $(LIB)/libcla.so
	@make $(LIB)/$(SHAREDLIB)


update_debug:
	@make clean
	@make shared_obj



update_release:
	@make clean




clean :
	@rm -f -r $(OBJECTS) $(BIN)/$(TARGET) $(BIN)/$(TARGET)_r $(BIN)/$(TARGET_SINGLE)
	@rm -f -r $(LIB)/$(SHAREDLIB) $(LIB)/$(SHAREDLIB_REL).so  $(OBJ)/$(TARGET) 
	@rm -f -r $(LIB)/libcla.so $(OBJECTS_REL)

#$(TEST_OBJECTS).o: $(TEST_SOURCE) $(INC)/$(TARGET).h
#		$(CC) $(CFLAGS) $< -c -o $(OBJ)/$(TARGET)/$@
