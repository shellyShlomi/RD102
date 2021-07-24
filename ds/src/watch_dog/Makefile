



TARGET = watch_dog
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
TEST_OBJECTS = $(OBJ)/user_app/user_app.o 
USER_OBJECTS = $(OBJ)/WD_file_for_user/WD_file_for_user.o 
OBJECTS_REL = $(OBJ)/$(TARGET)/$(TARGET)_r.o 

#--------------source & test sourec files-------------#
TEST_SOURCE =  $(SRC)/user_app.c
SOURCE = $(SRC)/$(TARGET).c 
USER_SOURCE =  $(SRC)/WD_file_for_user.c

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

$(BIN)/$(TARGET_SINGLE): $(LIB)/$(SHAREDLIB) $(USER_SOURCE)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ -lpthread

$(BIN)/WD_file_for_user: $(USER_SOURCE) 
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@ $(LIB)/libds.so -lm -lpthread

$(BIN)/user_app: $(TEST_SOURCE)  
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@ $(LIB)/libds.so -lm -lpthread

$(SRC)/$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIB)/libds.so -lm -lpthread

$(TEST_OBJECTS): $(TEST_SOURCE)
	$(CC) $(CFLAGS) $(SOFLAG_FIRST) $< -o $@ 

$(USER_OBJECTS): $(USER_SOURCE)
	$(CC) $(CFLAGS) $(SOFLAG_FIRST) $< -o $@ 



$(OBJECTS_REL): $(SOURCE)
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_FIRST) $< -o $@ 

$(LIB)/$(SHAREDLIB_REL).so: $(OBJECTS_REL)  
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_SECOND) $^ -o $@ 

$(BIN)/$(TARGET)_r: $(TEST_SOURCE) 
	$(CC) $(RELEASE_FLAGS) $(LDFLAGS) $< -o $@ $(LIB)/libds.so -lm -lpthread




.PHONY :build test shared_obj shared_lib release release_single 
		update_debug update_release clean 

build:
	@mkdir -p $(OBJ)/$(TARGET)  
	@make shared_obj
	@make $(BIN)/user_app
	@make $(BIN)/WD_file_for_user 

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

libds:
	
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) $(shell find $(OBJ)/*/. -type f -regex ".*\.o")  -o $(LIB)/libds.so


clean :
	@rm -f -r $(OBJECTS) $(BIN)/$(TARGET) $(BIN)/$(TARGET)_r $(BIN)/$(TARGET_SINGLE)
	@rm -f -r $(LIB)/$(SHAREDLIB) $(LIB)/$(SHAREDLIB_REL).so  $(OBJ)/$(TARGET)  

