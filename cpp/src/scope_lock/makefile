
#made by shelly


TARGET = $(notdir $(shell pwd))
SHAREDLIB = lib$(TARGET).so
SHAREDLIB_REL = lib$(TARGET)_rel.so

TEST_TARGET = $(TARGET)_test
TARGET_RELEASE = $(TEST_TARGET)_rel



SRC = .
LIB = ../../lib
TEST = ../../test
INC = ../../include 
INC_SHAPE = ../../include/shape
BIN = ../../bin

OBJ = ../../obj
OBJ_REL = ../../obj_rel
CC = g++
CFLAGS = -std=c++98 -pedantic-errors -Wall -Wextra -g -I$(INC)  -I$(INC_SHAPE)
RELEASE_FLAGS =  -std=c++98 -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) -I$(INC_SHAPE) 

OBJECTS = $(OBJ)/$(TARGET)/$(TARGET).o 
OBJECTS_TEST = ../../test_o/$(TARGET)_test.o 
OBJECTS_REL = ../../test_o/$(TARGET_RELEASE).o

# ************************* source & test sourec files *************************
TEST_SOURCE = $(TEST)/$(TEST_TARGET).cpp
SOURCE = $(SRC)/$(TARGET).cpp 


FILE  = $(shell find ../../../tools/. -type f -regex ".*\.c")
TEST_OBJ = $(patsubst *.c, *.o, $(notdir $(FILE:.c=.o)))
TEST_OBJs = $(patsubst %.o, $(OBJ)/tests_lib/%.o,  $(TEST_OBJ))

# ***************************** share object flags ***************************** 
SOFLAG_FIRST = -c -fpic 
SOFLAG_SECOND = -shared

LDFLAGS = -L$(LIB) -Wl,-rpath=$(LIB)  -lpthread
LDFLAGS_REL = -L$(LIB) -Wl,-rpath=$(LIB)  -lpthread

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

$(BIN)/$(TARGET): $(TEST_SOURCE) 
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@ -lpthread


#----------------release rules------------------#


$(BIN)/$(TARGET_RELEASE): $(TEST_SOURCE)  
	$(CC) $(RELEASE_FLAGS) $(LDFLAGS_REL) $< -o $@ -lpthread


#----------------	shered librery	------------------#
$(OBJ)/tests_lib/%.o: ../../../tools/%.c
	@mkdir -p $(OBJ)/tests_lib 
	$(CC) $(CFLAGS) $(SOFLAG_FIRST) $^ -o $@ 



libtests: $(TEST_OBJs)
#----------------	PHONYs	------------------#

.PHONY :build silent_test nw_test nmw_test test vlgT hlgT shared_obj 
		update_debug clean_d
		release silent_test_release nw_test_release nmw_test_release test_release  
		hlgT_release vlgT_release release_so update_release clean_r
		shared_lib clean  

#----------------DEBUG------------------#

build:
	@make libtests
	@make shared_obj
	@make $(BIN)/$(TARGET)


silent_test:
	@make -s CFLAGS='-std=c++98 -g -I$(INC) -I$(INC_SHAPE)' build
	@./$(BIN)/$(TARGET)

nw_test:
	@make CFLAGS='-std=c++98 -g -I$(INC) -I$(INC_SHAPE)' build
	@./$(BIN)/$(TARGET)

nmw_test:
	@make -s build
	@./$(BIN)/$(TEST_SOURCE)

test:
	@make  build
	@./$(BIN)/$(TARGET)

vlgT:
	@make  build
	@$(VLG) ./$(BIN)/$(TARGET)

hlgT:
	@make  build
	@$(HLG) ./$(BIN)/$(TARGET)

shared_obj:
	@mkdir -p ../../test_o/$(TARGET) 
	@mkdir -p $(LIB)/  
	@mkdir -p $(BIN)/  


update_debug:
	@make clean_d
	@make build


clean_d :
	@rm -f -r  $(BIN)/$(TARGET)
	@rm -f -r $(LIB)/$(SHAREDLIB) 
	@rm -f -r $(LIB)/libcla.so 
	@rm -f -r $(OBJ)/$(TARGET) 
	@rm -f -r ../../test_o/ 



#----------------RELEASE------------------#

release: CFLAGS = $(RELEASE_FLAGS) 
release: 
	@make libtests
	@make release_so
	@make $(BIN)/$(TARGET_RELEASE)

silent_test_release:
	@make -s RELEASE_FLAGS='-std=c++98 -DNDEBUG -O3 -I$(INC) -I$(INC_SHAPE)' release
	@./$(BIN)/$(TARGET_RELEASE)

nw_test_release:
	@make RELEASE_FLAGS='-std=c++98 -DNDEBUG -O3 -I$(INC) -I$(INC_SHAPE)' release
	@./$(BIN)/$(TARGET_RELEASE)


nmw_test_release:
	@make -s release
	@./$(BIN)/$(TARGET_RELEASE)


test_release:
	@make release
	@./$(BIN)/$(TARGET_RELEASE)

vlgT_release:
	@make release
	@$(VLG) ./$(BIN)/$(TARGET_RELEASE)

hlgT_release:
	@make release
	@$(HLG) ./$(BIN)/$(TARGET_RELEASE)


release_so:
	@mkdir -p ../../test_o/$(TARGET_RELEASE) 
	@mkdir -p $(LIB)/  
	@mkdir -p $(BIN)/ 



update_release:
	@make clean_r
	@make release


clean_r :
	@rm -f -r $(BIN)/$(TARGET_RELEASE)
	@rm -f -r $(LIB)/$(SHAREDLIB_REL)  
	@rm -f -r  $(LIB)/libcla_rel.so
	@rm -f -r  $(OBJ_REL)/$(TARGET_RELEASE) 
	@rm -f -r ../../test_o/ 


#----------------GENERAL------------------#


shared_lib:
	@make $(LIB)/libcla_rel.so
	@make $(LIB)/libcla.so


clean :
	@make clean_r
	@make clean_d




