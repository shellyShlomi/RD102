

TARGET = tcp_local_ping_pong
SHAREDLIB = lib$(TARGET).so
SHAREDLIB_REL = lib$(TARGET)_rel.so

TEST_TARGET = $(TARGET)
TARGET_RELEASE = $(TARGET)_rel



SRC = .
LIB = ../lib
TEST = .
INC = ../include 
SHARE = ../sheard_tcp 
BIN = ../bin

OBJ = ../obj/ex2
OBJ_REL = ../obj_rel/ex2
CC = gcc
CFLAGS = -std=c99 -pedantic-errors -Wall -Wextra -g -I$(INC) 
RELEASE_FLAGS = -std=c99 -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC)

OBJECTS = $(OBJ)/ 
OBJECTS_REL = $(OBJ_REL)/$(TARGET_RELEASE)/$(TARGET_RELEASE).o

# ************************* source & test sourec files *************************
TEST_SOURCE_1 = ./$(TEST_TARGET)_1.c
TEST_SOURCE_2 = ./$(TEST_TARGET)_2.c

FILE  = $(shell find ../sheard_tcp/. -type f -regex ".*\.c")
LIB_OBJ = $(patsubst *.c, *.o, $(notdir $(FILE:.c=.o)))
LIB_OBJs = $(patsubst %.o, $(OBJ)/%.o,  $(LIB_OBJ))


# ***************************** share object flags ***************************** 
SOFLAG_FIRST = -c -fpic 
SOFLAG_SECOND = -shared

LDFLAGS = -L$(LIB) -Wl,-rpath=$(LIB) -ltcp
LDFLAGS_REL = -L$(LIB) -Wl,-rpath=$(LIB) -ltcp_rel 

#					-------shared object flags whit thread-------					

LDFLAGS_MT = -L$(LIB) -Wl,-rpath=$(LIB) -ltcp -lpthread
LDFLAGS_REL_MT = -L$(LIB) -Wl,-rpath=$(LIB) -ltcp_rel -lpthread

# ********************************** debuging **********************************

VLG		= valgrind --leak-check=yes --track-origins=yes
HLG		= valgrind --tool=helgrind --history-level=approx
CGDB	= cgdb

#*******************************************************************************
#************************************ RULES ************************************
#*******************************************************************************


#----------------debug rules------------------#
$(OBJ)/%.o: ../sheard_tcp/%.c
	$(CC) $(CFLAGS) $(SOFLAG_FIRST) $^ -o $@ 

$(BIN)/tcp_client: $(TEST_SOURCE_1) $(LIB)/libtcp.so 
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ 

$(BIN)/tcp_server: $(TEST_SOURCE_2) $(LIB)/libtcp.so 
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@  

#----------------release rules------------------#

$(OBJECTS_REL)/%.o: ../sheard_tcp/%.c
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_FIRST) $^ -o $@ 

$(LIB)/$(SHAREDLIB_REL):$(OBJECTS_REL)  
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_SECOND) $^ -o $@ 


$(BIN)/$(TARGET_RELEASE): $(TEST_SOURCE) $(OBJECTS_REL) 
	$(CC) $(RELEASE_FLAGS) $(LDFLAGS_REL) $< -o $@ $(LIB)/libtcp_rel.so  


#----------------	shered librery	------------------#
$(LIB)/libtcp.so: $(OBJECTS)
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) $(shell find $(OBJ)/. -type f -regex ".*\.o")  -o $@ 

$(LIB)/libtcp_rel.so: $(OBJECTS_REL)
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_SECOND)	$(shell find $(OBJ_REL)/. -type f -regex ".*\.o") -o $@ 

#----------------	PHONYs	------------------#

.PHONY :build silent_build nw_build nmw_build test vlgT hlgT shared_obj 
		update_debug clean_d
		release silent_build_release nw_build_release nmw_build_release test_release  
		hlgT_release vlgT_release release_so update_release clean_r
		shared_lib clean  

moveobj: 
	@mv $(shell find ./. -type f -regex ".*\.o") $(OBJ)/

#----------------DEBUG------------------#

build:
	@make shared_obj
	@make $(BIN)/tcp_client
	@make $(BIN)/tcp_server


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
	@make $(LIB_OBJs)
	@make $(LIB)/libtcp.so  


update_debug:
	@make clean_d
	@make build


clean_d :
	@rm -f -r  $(BIN)/$(TARGET)
	@rm -f -r $(LIB)/ 
	@rm -f -r $(LIB)/libtasts.so 
	@rm -f -r $(OBJ)/ 


#----------------RELEASE------------------#

# release: CFLAGS = $(RELEASE_FLAGS) 
release: 
	@make RELEASE_FLAGS='-std=c++98 -DNDEBUG -O3 -I$(INC)' libtcp
	@make RELEASE_FLAGS='-std=c++98 -DNDEBUG -O3 -I$(INC)' release_so
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
	@make $(LIB)/libtcp_rel.so



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



