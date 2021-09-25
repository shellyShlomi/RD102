

UDP_TARGET = udp_client
TCP_TARGET = tcp_client
SERVER_TARGET = server


UDP_SHAREDLIB = libudp.so
TCP_SHAREDLIB = libtcp.so
SERVER_SHAREDLIB = libserver.so
# UDP_SHAREDLIB_REL = $(UDP_SHAREDLIB)_rel.so
# TCP_SHAREDLIB_REL = $(TCP_SHAREDLIB)_rel.so

# UDP_TARGET_RELEASE = $(UDP_TARGET)_rel
# TCP_TARGET_RELEASE = $(TCP_TARGET)_rel
# SERVER_TARGET_RELEASE = $(SERVER_TARGET)_rel


SRC = .
LIB = ../lib
TEST = .
INC = ../include 
UDP_SHARE = ../sheard_udp 
TCP_SHARE = ../sheard_tcp 
BIN = ../bin

Obj = ../obj
OBJ_UDP = ../obj/udp
OBJ_TCP = ../obj/tcp

UDP_OBJ_REL = ../obj_rel/udp
TCP_OBJ_REL = ../obj_rel/tcp
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I$(INC) 
# RELEASE_FLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC)

# ************************* source & test sourec files *************************
UDP_SOURCE = ./$(UDP_TARGET).c
TCP_SOURCE = ./$(TCP_TARGET).c
SERVER_SOURCE  = ./tcp_udp_$(SERVER_TARGET).c

SERVER_UTILITIS = $(SERVER_TARGET).c
# ***************************** share object flags ***************************** 
SOFLAG_FIRST = -c -fpic 
SOFLAG_SECOND = -shared

UDP_LDFLAG = -ludp
TCP_LDFLAG = -ltcp
SERVER_LDFLAG = -lserver
LDFLAGS = -L$(LIB) -Wl,-rpath=$(LIB) 
# UDP_LDFLAG_REL =  -ludp_rel 
# TCP_LDFLAG_REL =  -ltcp_rel 

#					-------shared object flags whit thread-------					

LDFLAGS_MT = -L$(LIB) -Wl,-rpath=$(LIB)

# LDFLAGS_REL_MT = -L$(LIB) -Wl,-rpath=$(LIB) 

# ********************************** debuging **********************************

VLG		= valgrind --leak-check=yes --track-origins=yes
HLG		= valgrind --tool=helgrind --history-level=approx
CGDB	= cgdb

#*******************************************************************************
#************************************ RULES ************************************
#*******************************************************************************


#----------------debug rules------------------#

$(BIN)/$(UDP_TARGET): $(UDP_SOURCE) $(LIB)/$(UDP_SHAREDLIB) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(UDP_LDFLAG) $^ -o $@ 
$(BIN)/$(TCP_TARGET): $(TCP_SOURCE) $(LIB)/$(TCP_SHAREDLIB) 
	$(CC) $(CFLAGS)$(LDFLAGS) $(TCP_LDFLAG) $^ -o $@ 

$(BIN)/$(SERVER_TARGET): $(SERVER_SOURCE) $(SERVER_UTILITIS) $(LIB)/$(SERVER_SHAREDLIB) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(SERVER_LDFLAG) $^ -o $@ 


#----------------release rules------------------#


# $(LIB)/$(SHAREDLIB_REL):$(OBJECTS_REL)  
# 	$(CC) $(RELEASE_FLAGS) $(SOFLAG_SECOND) $^ -o $@ 


# $(BIN)/$(TARGET_RELEASE): $(TEST_SOURCE) $(OBJECTS_REL) 
# 	$(CC) $(RELEASE_FLAGS) $(LDFLAGS_REL) $< -o $@ $(LIB)/ludp_rel.so  


#----------------	PHONYs	------------------#

.PHONY :build build_s build_u build_t ts tuc ttc TSs TTCs TUCs SvlgT UvlgT TvlgT \
		SvlgTs UvlgTs TvlgTs update_debug clean_d shared_lib clean  


# release silent_build_release nw_build_release nmw_build_release test_release  
# hlgT_release vlgT_release release_so update_release clean_r

#----------------DEBUG------------------#

build:
	@make build_u
	@make build_t
	@make build_s

build_s:
	@make $(BIN)/$(SERVER_TARGET)

build_u:
	@mkdir -p $(BIN)/  
	@make $(BIN)/$(UDP_TARGET)

build_t:
	@mkdir -p $(BIN)/	
	@make $(BIN)/$(TCP_TARGET)

ts:
	@make build_s
	@./$(BIN)/$(SERVER_TARGET)

tuc:
	@make build_u
	@./$(BIN)/$(UDP_TARGET)

ttc:
	@make build_t
	@./$(BIN)/$(TCP_TARGET)

TSs:
	@make -s build_s	
	@./$(BIN)/$(SERVER_TARGET)


TUCs:
	@make -s build_u
	@./$(BIN)/$(UDP_TARGET)
	
TTCs:
	@make -s build_t
	@./$(BIN)/$(TCP_TARGET)


SvlgT:
	@make  build_s
	@$(VLG) ./$(BIN)/$(SERVER_TARGET)

	
UvlgT:
	@make  build_u
	@$(VLG) ./$(BIN)/$(UDP_TARGET)

TvlgT:
	@make  build_t
	@$(VLG) ./$(BIN)/$(TCP_TARGET)

SvlgTs:
	@make -s build_s
	@$(VLG) ./$(BIN)/$(SERVER_TARGET)

	
UvlgTs:
	@make -s build_u
	@$(VLG) ./$(BIN)/$(UDP_TARGET)

TvlgTs:
	@make -s build_t
	@$(VLG) ./$(BIN)/$(TCP_TARGET)


shared_obj:
	@mkdir -p $(BIN)/  


update_debug:
	@make clean_d
	@make build


clean_d :
	@rm -f -r  $(BIN)
	@rm -f -r $(Obj)/ 


#----------------RELEASE------------------#

# release: CFLAGS = $(RELEASE_FLAGS) 
# release: 
# 	@make RELEASE_FLAGS='-std=c99 -DNDEBUG -O3 -I$(INC)' release_so
# 	@make $(BIN)/$(TARGET_RELEASE)

# silent_build_release:
# 	@make -s RELEASE_FLAGS='-std=c99 -DNDEBUG -O3 -I$(INC)' release

# nw_build_release:
# 	@make RELEASE_FLAGS='-std=c++98 -DNDEBUG -O3 -I$(INC)' release


# nmw_build_release:
# 	@make -s release


# build_release:
# 	@make release

# release_so:
# 	@mkdir -p $(UDP_OBJ_REL)/$(TARGET_RELEASE)
# 	@mkdir -p $(BIN)/  
# 	@make $(LIB)/libudp_rel.so



# update_release:
# 	@make clean_r
# 	@make release


# clean_r :
# 	@rm -f -r $(BIN)/$(TARGET_RELEASE)
# 	@rm -f -r  $(UDP_OBJ_REL)/$(TARGET_RELEASE) 


#----------------GENERAL------------------#


shared_lib:
	@make $(LIB)/libudp_rel.so
	@make $(LIB)/libudp.so


clean :
	@rm -f -r  $(BIN)
	@rm -f -r $(UDP_OBJ_REL)
	@rm -f -r $(Obj)



