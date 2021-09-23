

TARGET = udp_client
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

Obj = ../obj
OBJ_U = ../obj/udp
OBJ_T = ../obj/tcp
OBJ_REL = ../obj_rel/udp
CC = gcc
CFLAGS = -std=c99 -pedantic-errors -Wall -Wextra -g -I$(INC) 
RELEASE_FLAGS = -std=c99 -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC)

OBJECTS = $(OBJ)/ 
OBJECTS_REL = $(OBJ_REL)/$(TARGET_RELEASE)/$(TARGET_RELEASE).o

# ************************* source & test sourec files *************************
TEST_SOURCE_1 = ./$(TEST_TARGET).c
TEST_SOURCE_2 = ./tcp_client.c
TEST_SOURCE_3  = tcp_udp_server.c

# ***************************** share object flags ***************************** 
SOFLAG_FIRST = -c -fpic 
SOFLAG_SECOND = -shared

LDFLAGS_U = -L$(LIB) -Wl,-rpath=$(LIB) -ludp
LDFLAGS_L = -L$(LIB) -Wl,-rpath=$(LIB)  -ltcp
LDFLAGS_REL = -L$(LIB) -Wl,-rpath=$(LIB) -ludp_rel 

#					-------shared object flags whit thread-------					

LDFLAGS_MT = -L$(LIB) -Wl,-rpath=$(LIB) -ludp -ltcp -lpthread
LDFLAGS_REL_MT = -L$(LIB) -Wl,-rpath=$(LIB) -ludp_rel -lpthread

# ********************************** debuging **********************************

VLG		= valgrind --leak-check=yes --track-origins=yes
HLG		= valgrind --tool=helgrind --history-level=approx
CGDB	= cgdb

#*******************************************************************************
#************************************ RULES ************************************
#*******************************************************************************


#----------------debug rules------------------#

$(BIN)/udp_client: $(TEST_SOURCE_1) $(LIB)/libudp.so 
	$(CC) $(CFLAGS) $(LDFLAGS_U) $^ -o $@ 
$(BIN)/tcp_client: $(TEST_SOURCE_2) $(LIB)/libtcp.so 
	$(CC) $(CFLAGS) $(LDFLAGS_L) $^ -o $@ 

$(BIN)/server: $(TEST_SOURCE_3) $(LIB)/libtcp.so   $(LIB)/libudp.so 
	$(CC) $(CFLAGS) $(LDFLAGS_U) -ltcp $^ -o $@ 
#----------------release rules------------------#


$(LIB)/$(SHAREDLIB_REL):$(OBJECTS_REL)  
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_SECOND) $^ -o $@ 


$(BIN)/$(TARGET_RELEASE): $(TEST_SOURCE) $(OBJECTS_REL) 
	$(CC) $(RELEASE_FLAGS) $(LDFLAGS_REL) $< -o $@ $(LIB)/ludp_rel.so  


#----------------	PHONYs	------------------#

.PHONY :build tserv tclie t_serv_s t_clie_s silent_build nw_build nmw_build test vlgT hlgT shared_obj 
		update_debug clean_d
		release silent_build_release nw_build_release nmw_build_release test_release  
		hlgT_release vlgT_release release_so update_release clean_r
		shared_lib clean  

#----------------DEBUG------------------#

build:
	@make build_u
	@make build_t
	@make build_s

build_s:
	@make $(BIN)/server

build_u:
	@mkdir -p $(LIB)/  
	@mkdir -p $(BIN)/  
	@make $(BIN)/udp_client

build_t:
	@mkdir -p $(LIB)/  
	@mkdir -p $(BIN)/	
	@make $(BIN)/tcp_client

tserv:
	@make build_s
	@./$(BIN)/udp_server


tclie:
	@make build_c
	@./$(BIN)/udp_client

t_serv_s:
	@make -s build_s	
	@./$(BIN)/udp_server


t_clie_s:
	@make -s build_c
	@./$(BIN)/udp_client

vlgT_c:
	@make  build_c
	@$(VLG) ./$(BIN)/udp_client



vlgT_s:
	@make  build_s
	@$(VLG) ./$(BIN)/udp_server


silent_build:
	@make -s CFLAGS='-std=c99 -g -I$(INC)' build

nw_build:
	@make CFLAGS='-std=c99 -g -I$(INC) ' build

nmw_build:
	@make -s build


shared_obj:
	@mkdir -p $(OBJ)/ 
	@mkdir -p $(OBJ_T)/ 
	@mkdir -p $(LIB)/  
	@mkdir -p $(BIN)/  
	@make $(LIB)/libtcp.so
	@make $(LIB)/libudp.so 


update_debug:
	@make clean_d
	@make build


clean_d :
	@rm -f -r  $(BIN)/$(TARGET)
	@rm -f -r $(LIB)/ 
	@rm -f -r $(LIB)/libudp.so 
	@rm -f -r $(OBJ)/ 


#----------------RELEASE------------------#

# release: CFLAGS = $(RELEASE_FLAGS) 
release: 
	@make RELEASE_FLAGS='-std=c99 -DNDEBUG -O3 -I$(INC)' release_so
	@make $(BIN)/$(TARGET_RELEASE)

silent_build_release:
	@make -s RELEASE_FLAGS='-std=c99 -DNDEBUG -O3 -I$(INC)' release

nw_build_release:
	@make RELEASE_FLAGS='-std=c++98 -DNDEBUG -O3 -I$(INC)' release


nmw_build_release:
	@make -s release


build_release:
	@make release

release_so:
	@mkdir -p $(OBJ_REL)/$(TARGET_RELEASE)
	@mkdir -p $(BIN)/  
	@make $(LIB)/libudp_rel.so



update_release:
	@make clean_r
	@make release


clean_r :
	@rm -f -r $(BIN)/$(TARGET_RELEASE)
	@rm -f -r  $(OBJ_REL)/$(TARGET_RELEASE) 


#----------------GENERAL------------------#


shared_lib:
	@make $(LIB)/libudp_rel.so
	@make $(LIB)/libudp.so


clean :
	@rm -f -r  $(BIN)
	@rm -f -r $(OBJ_REL)
	@rm -f -r $(Obj)



