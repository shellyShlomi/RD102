
SRC_LIB = ..
LIB = ./lib
TEST = .
INC = ../include 
SHARE_t = ./sheard_tcp 
SHARE_u = ./sheard_udp 
BIN = ./bin

OBJ = ./obj

OBJ_udp = ./obj/udp
OBJ_tcp = ./obj/tcp
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I$(INC) 
# RELEASE_FLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC)

FILE_general  = $(OBJ_tcp)/ping_pong.o

FILE_udp  = $(shell find ./sheard_udp/. -type f -regex ".*\.c")
LIB_OBJ_udp = $(patsubst *.c, *.o, $(notdir $(FILE_udp:.c=.o))) 
LIB_OBJs_udp = $(patsubst %.o, $(OBJ_udp)/%.o,  $(LIB_OBJ_udp)) 

FILE_tcp  = $(shell find ./sheard_tcp/. -type f -regex ".*\.c")
LIB_OBJ_tcp = $(patsubst *.c, *.o, $(notdir $(FILE_tcp:.c=.o)))
LIB_OBJs_tcp = $(patsubst %.o, $(OBJ_tcp)/%.o,  $(LIB_OBJ_tcp)) 


# ***************************** share object flags ***************************** 
SOFLAG_FIRST = -c -fpic 
SOFLAG_SECOND = -shared

# ********************************** debuging **********************************

VLG		= valgrind --leak-check=yes --track-origins=yes
HLG		= valgrind --tool=helgrind --history-level=approx
CGDB	= cgdb

#*******************************************************************************
#************************************ RULES ************************************
#*******************************************************************************


#----------------debug rules------------------#
$(OBJ_tcp)/%.o: ./sheard_tcp/%.c
	$(CC) $(CFLAGS) $(SOFLAG_FIRST) $^ -o $@ 

$(OBJ_udp)/%.o: ./sheard_udp/%.c
	$(CC) $(CFLAGS) $(SOFLAG_FIRST) $^ -o $@ 



$(OBJ_udp)/%.o: $(SHARE_t)/$(FILE_general).c
	$(CC) $(CFLAGS) $(SOFLAG_FIRST) $^ -o $@ 
#----------------release rules------------------#

# $(OBJECTS_REL)/%.o: $(SHARE_t)/%.c
# 	$(CC) $(RELEASE_FLAGS) $(SOFLAG_FIRST) $^ -o $@ 


#----------------	shered librery	------------------#
$(LIB)/libtcp.so: $(LIB_OBJs_tcp)
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) $(shell find $(OBJ_tcp)/. -type f -regex ".*\.o")  -o $@ 


$(LIB)/libudp.so: $(LIB_OBJs_udp) 
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) $(FILE_general)  $(shell find $(OBJ_udp)/. -type f -regex ".*\.o")  -o $@ 


$(LIB)/libserver.so: $(LIB_OBJs_udp) $(LIB_OBJs_tcp)
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) \
	$(shell find $(OBJ_tcp)/. -type f -regex ".*\.o") \
	$(shell find $(OBJ_udp)/. -type f -regex ".*\.o")  -o $@ 


# $(LIB)/libtcp_rel.so: $(OBJ_tcp)
# 	$(CC) $(RELEASE_FLAGS) $(SOFLAG_SECOND)	$(shell find $(OBJ_REL)/. -type f -regex ".*\.o") -o $@ 

# $(LIB)/libudp_rel.so: $(LIB_OBJs_udp)
# 	$(CC) $(RELEASE_FLAGS) $(SOFLAG_SECOND)	$(shell find $(OBJ_REL)/. -type f -regex ".*\.o") -o $@ 

#----------------	PHONYs	------------------#

.PHONY :build nmw_build test vlgT hlgT shared_obj update_debug clean_d shared_lib clean 
# release silent_build_release nw_build_release nmw_build_release test_release  
# hlgT_release vlgT_release release_so update_release clean_r
		 

#----------------DEBUG------------------#

build:
	@make shared_obj 
	@make $(LIB)/libserver.so 
	@rm -f -r $(SRC_LIB)/lib
	@mv $(LIB) $(SRC_LIB)


nmw_build:
	@make -s build


shared_obj:
	@mkdir -p $(OBJ_udp)/ 
	@mkdir -p $(OBJ_tcp)/ 
	@mkdir -p $(LIB)/  
	@make $(LIB)/libtcp.so
	@make $(LIB)/libudp.so


update_debug:
	@make clean_d
	@make build


clean_d :
	@rm -f -r  $(BIN)/$(TARGET)
	@rm -f -r $(LIB)/ 
	@rm -f -r $(OBJ)/ 


#----------------RELEASE------------------#

# release: CFLAGS = $(RELEASE_FLAGS) 
# release: 
# 	@make RELEASE_FLAGS='-std=c++98 -DNDEBUG -O3 -I$(INC)' libtcp
# 	@make RELEASE_FLAGS='-std=c++98 -DNDEBUG -O3 -I$(INC)' release_so
# 	@make $(BIN)/$(TARGET_RELEASE)

# silent_build_release:
# 	@make -s RELEASE_FLAGS='-std=c++98 -DNDEBUG -O3 -I$(INC)' release

# nw_build_release:
# 	@make RELEASE_FLAGS='-std=c++98 -DNDEBUG -O3 -I$(INC)' release


# nmw_build_release:
# 	@make -s release


# build_release:
# 	@make release

# release_so:
# 	@mkdir -p $(OBJ_REL)/$(TARGET_RELEASE)
# 	@mkdir -p $(LIB)/  
# 	@mkdir -p $(BIN)/  
# 	@make $(LIB)/libtcp_rel.so



# update_release:
# 	@make clean_r
# 	@make release


# clean_r :
# 	@rm -f -r $(BIN)/$(TARGET_RELEASE)
# 	@rm -f -r $(LIB)/$(SHAREDLIB_REL)  
# 	@rm -f -r  $(LIB)/libtasts_rel.so
# 	@rm -f -r  $(OBJ_REL)/$(TARGET_RELEASE) 


#----------------GENERAL------------------#


shared_lib:
	@make $(LIB)/libtasts_rel.so
	@make $(LIB)/libtasts.so


clean :
	@rm -f -r $(LIB)/
	@rm -f -r $(OBJ)/



