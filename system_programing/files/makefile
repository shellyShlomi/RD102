
#made by shelly


TARGET = ext2
SHAREDLIB = lib$(TARGET).so
SHAREDLIB_REL = lib$(TARGET)_rel.so

TEST_TARGET = $(TARGET)_test
TARGET_RELEASE = $(TARGET)_rel
arg1= $(shell @1)
arg2= $(shell @2)


SRC = .
LIB = ./lib
TEST = .
INC = ./include 
BIN = ./bin

OBJ = ./obj
OBJ_REL = ./obj_rel
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I$(INC) 
RELEASE_FLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC)

OBJECTS = $(OBJ)/$(TARGET).o 
OBJECTS_REL = $(OBJ_REL)/$(TARGET_RELEASE).o

# ************************* source & test sourec files *************************
TEST_SOURCE = $(TEST)/$(TEST_TARGET).c
SOURCE = $(SRC)/$(TARGET).c


FILE  = $(shell find ../../tools/. -type f -regex ".*\.c")
TEST_OBJ = $(patsubst *.c, *.o, $(notdir $(FILE:.c=.o)))
TEST_OBJs = $(patsubst %.o, $(OBJ)/tests_lib/%.o,  $(TEST_OBJ))

# ***************************** share object flags ***************************** 
SOFLAG_FIRST = -c -fpic 
SOFLAG_SECOND = -shared

LDFLAGS = -L$(LIB) -Wl,-rpath=$(LIB) -ltests
LDFLAGS_REL = -L$(LIB) -Wl,-rpath=$(LIB) -ltests_rel 

#					-------shared object flags whit thread-------					

LDFLAGS_MT = -L$(LIB) -Wl,-rpath=$(LIB) -ltests -lpthread
LDFLAGS_REL_MT = -L$(LIB) -Wl,-rpath=$(LIB) -ltests_rel -lpthread

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


$(BIN)/$(TARGET): $(TEST_SOURCE) $(OBJECTS) 
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIB)/libtests.so 


#----------------release rules------------------#

$(OBJECTS_REL): $(SOURCE)
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_FIRST) $< -o $@ 

$(LIB)/$(SHAREDLIB_REL):$(OBJECTS_REL)  
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_SECOND) $^ -o $@ 


$(BIN)/$(TARGET_RELEASE): $(TEST_SOURCE) $(OBJECTS_REL) $(LIB)/libtests_rel.so
	$(CC) $(RELEASE_FLAGS) $(LDFLAGS_REL) $< -o $@ $(LIB)/libtests_rel.so  


#----------------	shered librery	------------------#
$(OBJ)/tests_lib/%.o: ../../tools/%.c
	@mkdir -p $(OBJ)/tests_lib 
	$(CC) $(CFLAGS) $(SOFLAG_FIRST) $^ -o $@ 

$(LIB)/libtasts.so: $(OBJECTS)
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) $(shell find $(OBJ)/*/. -type f -regex ".*\.o")  -o $(LIB)/libtests.so

$(LIB)/libtests_rel.so: $(OBJECTS_REL)
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_SECOND) $(shell find $(OBJ)/tests_lib/. -type f -regex ".*\.o") \
	$(shell find $(OBJ_REL)/*/. -type f -regex ".*\.o") -o $(LIB)/libtests_rel.so


libtests: $(TEST_OBJs)
#----------------	PHONYs	------------------#

.PHONY :build silent_build nw_build nmw_build test vlgT hlgT shared_obj 
		update_debug clean_d
		release silent_build_release nw_build_release nmw_build_release test_release  
		hlgT_release vlgT_release release_so update_release clean_r
		shared_lib clean  

#----------------DEBUG------------------#

build:
	@make libtests
	@make shared_obj
	@make $(BIN)/$(TARGET)


silent_build:
	@make -s CFLAGS='-std=c++98 -g -I$(INC)' build

nw_build:
	@make CFLAGS='-std=c++98 -g -I$(INC) ' build

nmw_build:
	@make -s build


shared_obj:
	@mkdir -p $(OBJ)/ 
	@mkdir -p $(LIB)/  
	@mkdir -p $(BIN)/  
	@make $(LIB)/libtasts.so
	@make $(LIB)/


update_debug:
	@make clean_d
	@make build


clean_d :
	@rm -f -r  $(BIN)/$(TARGET)
	@rm -f -r $(LIB)/ 
	@rm -f -r $(LIB)/libtasts.so 
	@rm -f -r $(OBJ)/ 


#----------------RELEASE------------------#

release: CFLAGS = $(RELEASE_FLAGS) 
release: 
	@make libtests
	@make release_so
	@make $(BIN)/$(TARGET_RELEASE)

silent_build_release:
	@make -s RELEASE_FLAGS='-std=c++98 -DNDEBUG -O3 -I$(INC)' release

nw_build_release:
	@make RELEASE_FLAGS='-std=c++98 -DNDEBUG -O3 -I$(INC)' release


nmw_build_release:
	@make -s release


build_release:
	@make release

release_so:
	@mkdir -p $(OBJ_REL)/$(TARGET_RELEASE)
	@mkdir -p $(LIB)/  
	@mkdir -p $(BIN)/  
	@make $(LIB)/libtasts_rel.so
	@make $(LIB)/$(SHAREDLIB_REL)



update_release:
	@make clean_r
	@make release


clean_r :
	@rm -f -r $(BIN)/$(TARGET_RELEASE)
	@rm -f -r $(LIB)/$(SHAREDLIB_REL)  
	@rm -f -r  $(LIB)/libtasts_rel.so
	@rm -f -r  $(OBJ_REL)/$(TARGET_RELEASE) 


#----------------GENERAL------------------#


shared_lib:
	@make $(LIB)/libtasts_rel.so
	@make $(LIB)/libtasts.so


clean :
	@rm -f -r  $(BIN)
	@rm -f -r $(LIB)
	@rm -f -r $(OBJ_REL)
	@rm -f -r $(OBJ)



