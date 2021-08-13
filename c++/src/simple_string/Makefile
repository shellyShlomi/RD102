
#made by shelly


TARGET = $(notdir $(shell pwd))
SHAREDLIB = lib$(TARGET).so
SHAREDLIB_REL = lib$(TARGET)_rel.so

TEST_TARGET = $(TARGET)_test
TARGET_RELEASE = $(TARGET)_rel



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
OBJECTS_REL = $(OBJ)/$(TARGET_RELEASE)/$(TARGET_RELEASE).o

# ************************* source & test sourec files *************************
TEST_SOURCE = $(TEST)/$(TEST_TARGET).cpp
SOURCE = $(SRC)/$(TARGET).cpp 

# ***************************** share object flags ***************************** 
SOFLAG_FIRST = -c -fpic 
SOFLAG_SECOND = -shared

LDFLAGS = -L$(LIB) -Wl,-rpath=$(LIB) -lcla
LDFLAGS_REL = -L$(LIB) -Wl,-rpath=$(LIB) -lcla_rel

#					-------shared object flags whit thread-------					

LDFLAGS_MT = -L$(LIB) -Wl,-rpath=$(LIB) -lcla -lpthread
LDFLAGS_REL_MT = -L$(LIB) -Wl,-rpath=$(LIB) -lcla_rel -lpthread

# ********************************** debuging **********************************

VLG		= valgrind --leak-check=yes --track-origins=yes
HLG		= valgrind --tool=helgrind --history-level=approx
CGDB	= cgdb

#*******************************************************************************
#************************************ RULES ************************************
#*******************************************************************************


#----------------debug rules------------------#


$(OBJECTS): $(SOURCE)
	$(CC) $(CFLAGS) $(SOFLAG_FIRST) $< -o $@ 

$(LIB)/$(SHAREDLIB): $(OBJECTS)  
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) $^ -o $@ 


$(BIN)/$(TARGET): $(TEST_SOURCE) $(OBJECTS) $(LIB)/libcla.so
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@ $(LIB)/$(SHAREDLIB)  -lm -lpthrea


#----------------release rules------------------#

$(OBJECTS_REL): $(SOURCE)
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_FIRST) $< -o $@ 

$(LIB)/$(SHAREDLIB_REL):$(OBJECTS_REL)  
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_SECOND) $^ -o $@ 


$(BIN)/$(TARGET_RELEASE): $(TEST_SOURCE) $(OBJECTS_REL) $(LIB)/libcla_rel.so
	$(CC) $(RELEASE_FLAGS) $(LDFLAGS_REL) $< -o $@  -lm -lpthread


#----------------	shered librery	------------------#


$(LIB)/libcla.so: $(OBJECTS)
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) $(shell find $(OBJ)/*/. -type f -regex ".*\.o")  -o $(LIB)/libcla.so

$(LIB)/libcla_rel.so: $(OBJECTS_REL)
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_SECOND) $(shell find $(OBJ)/*/. -type f -regex ".*\.o")  -o $(LIB)/libcla_rel.so


#----------------	PHONYs	------------------#

.PHONY :build test vlgT hlgT shared_obj update_debug
		release test_release vlgT_release hlgT_release release_so update_release
		shared_lib clean 

#----------------DEBUG------------------#

build:
	@make shared_obj
	@make $(BIN)/$(TARGET)

test:
	@make build
	@./$(BIN)/$(TARGET)

vlgT:
	@$(VLG) ./$(BIN)/$(TARGET)

hlgT:
	@$(HLG) ./$(BIN)/$(TARGET)

shared_obj:
	@mkdir -p $(OBJ)/$(TARGET)  
	@make $(LIB)/libcla.so
	@make $(LIB)/$(SHAREDLIB)


update_debug:
	@make clean
	@make shared_obj


#----------------RELEASE------------------#

release:
	@make release_so
	@make $(BIN)/$(TARGET_RELEASE)

test_release:
	@make release
	@./$(BIN)/$(TARGET_RELEASE)


vlgT_release:
	@$(VLG) ./$(BIN)/$(TARGET_RELEASE)

hlgT_release:
	@$(HLG) ./$(BIN)/$(TARGET_RELEASE)


release_so:
	@mkdir -p $(OBJ)/$(TARGET_RELEASE)
	@make $(LIB)/libcla_rel.so
	@make $(LIB)/$(SHAREDLIB_REL)



update_release:
	@make clean
	@make release



#----------------GENERAL------------------#


shared_lib:
	@make $(LIB)/libcla_rel.so
	@make $(LIB)/libcla.so


clean :
	@rm -f -r  $(BIN)/$(TARGET) $(BIN)/$(TARGET_RELEASE)
	@rm -f -r $(LIB)/$(SHAREDLIB) $(LIB)/$(SHAREDLIB_REL)  
	@rm -f -r $(LIB)/libcla.so $(LIB)/libcla_rel.so
	@rm -f -r $(OBJ)/$(OBJECTS) $(OBJ)/$(OBJECTS_REL) 
