
#*****************************************************************************#
#-------- PHONYs command and there meaning to test the foledr's files --------#
#-----------------------------------------------------------------------------#
#------------------------------- made by shelly ------------------------------#
# ****************************************************************************#


TARGET = $(notdir $(shell pwd))
SHAREDLIB = lib$(TARGET).so
SHAREDLIB_REL = lib$(TARGET)_rel.so

TEST_TARGET = $(TARGET)_test
TARGET_RELEASE = $(TARGET)_rel



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
OBJECTS_REL = $(OBJ_REL)/$(TARGET_RELEASE)/$(TARGET_RELEASE).o

# ************************* source & test sourec files *************************
TEST_SOURCE = $(TEST)/$(TEST_TARGET).cpp
SOURCE = $(SRC)/$(TARGET).cpp 


FILE  = $(shell find ../../../tools/. -type f -regex ".*\.c")
TEST_OBJ = $(patsubst *.c, *.o, $(notdir $(FILE:.c=.o)))
TEST_OBJs = $(patsubst %.o, $(OBJ)/tests_lib/%.o,  $(TEST_OBJ))

# ***************************** share object flags ***************************** 
SOFLAG_FIRST = -c -fpic 
SOFLAG_SECOND = -shared

LDFLAGS = -L$(LIB) -Wl,-rpath=$(LIB) -lcla -lpthread
LDFLAGS_REL = -L$(LIB) -Wl,-rpath=$(LIB) -lcla_rel -lpthread

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
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@ $(LIB)/libcla.so 


#----------------release rules------------------#

$(OBJECTS_REL): $(SOURCE)
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_FIRST) $< -o $@ 

$(LIB)/$(SHAREDLIB_REL):$(OBJECTS_REL)  
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_SECOND) $^ -o $@ 


$(BIN)/$(TARGET_RELEASE): $(TEST_SOURCE) $(OBJECTS_REL) $(LIB)/libcla_rel.so
	$(CC) $(RELEASE_FLAGS) $(LDFLAGS_REL) $< -o $@ $(LIB)/libcla_rel.so  


#----------------	shered librery	------------------#
$(OBJ)/tests_lib/%.o: ../../../tools/%.c
	@mkdir -p $(OBJ)/tests_lib 
	$(CC) $(CFLAGS) $(SOFLAG_FIRST) $^ -o $@ 

$(LIB)/libcla.so: $(OBJECTS)
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) $(shell find $(OBJ)/*/. -type f -regex ".*\.o")  -o $(LIB)/libcla.so

$(LIB)/libcla_rel.so: $(OBJECTS_REL)
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_SECOND)	$(shell find $(OBJ_REL)/*/. -type f -regex ".*\.o") -o $(LIB)/libcla_rel.so


libtests: $(TEST_OBJs)
#----------------	PHONYs	------------------#

.PHONY :build silent_test nw_test nmw_test test s_vlgT vlgT s_hlgT hlgT shared_obj 
		update_debug clean_d
		release silent_test_release nw_test_release nmw_test_release test_release  
		hlgT_release vlgT_release release_so update_release clean_r
		shared_lib clean clean_all

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
	@./$(BIN)/$(TARGET)

test:
	@make  build
	@./$(BIN)/$(TARGET)

vlgT:
	@make  build
	@$(VLG) ./$(BIN)/$(TARGET)

s_vlgT:
	@make -s build
	@$(VLG) ./$(BIN)/$(TARGET)

hlgT:
	@make  build
	@$(HLG) ./$(BIN)/$(TARGET)

s_hlgT:
	@make -s build
	@$(HLG) ./$(BIN)/$(TARGET)


shared_obj:
	@mkdir -p $(OBJ)/$(TARGET)  
	@mkdir -p $(LIB)/  
	@mkdir -p $(BIN)/  
	@make $(LIB)/libcla.so
	@make $(LIB)/$(SHAREDLIB)


update_debug:
	@make clean_d
	@make build


clean_d :
	@rm -f -r  $(BIN)/$(TARGET)
	@rm -f -r $(LIB)/$(SHAREDLIB) 
	@rm -f -r $(LIB)/libcla.so 
	@rm -f -r $(OBJ)/$(TARGET) 



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
	@mkdir -p $(OBJ_REL)/$(TARGET_RELEASE)
	@mkdir -p $(LIB)/  
	@mkdir -p $(BIN)/  
	@make $(LIB)/libcla_rel.so
	@make $(LIB)/$(SHAREDLIB_REL)



update_release:
	@make clean_r
	@make release


clean_r :
	@rm -f -r $(BIN)/$(TARGET_RELEASE)
	@rm -f -r $(LIB)/$(SHAREDLIB_REL)  
	@rm -f -r  $(LIB)/libcla_rel.so
	@rm -f -r  $(OBJ_REL)/$(TARGET_RELEASE) 


#----------------GENERAL------------------#


shared_lib:
	@make $(LIB)/libcla_rel.so
	@make $(LIB)/libcla.so


clean :
	@make clean_r
	@make clean_d
	@rm -f -r $(BIN)/
	@rm -f -r  $(LIB)/
	@rm -f -r  $(OBJ_REL)/
	@rm -f -r  $(OBJ)/
	@rm -f -r ../../test_o/ 




