

SUBDIRS := $(wildcard */.)

LIB = ../lib

INC = ../include
BIN = ../bin

OBJ = ../obj
CC = g++
CFLAGS = -std=c++98 -pedantic-errors -Wall -Wextra -g -I$(INC) 
RELEASE_FLAGS =  -std=c++98 -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 

#----------------shared object flags------------------#

SOFLAG_SECOND = -shared 

LDFLAGS = -L$(LIB) -Wl,-rpath=$(LIB) -lcla 
LDFLAGS_REL = -L$(LIB) -Wl,-rpath=$(LIB) -lcla_rel 

#-------shared object flags whit thread-------#

LDFLAGS_MT = -L$(LIB) -Wl,-rpath=$(LIB) -lcla -lpthread
LDFLAGS_REL_MT = -L$(LIB) -Wl,-rpath=$(LIB) -lcla_rel -lpthread

#----------------------------------------------------#
.PHONY :build test vlgT hlgT shared_obj update_debug
		release test_release vlgT_release hlgT_release release_so update_release
		shared_lib clean 



.PHONY: libcla  build test vlgT hlgT shared_obj_debug release release_single
		change clean build_single 



test: 
	@make -f ./.make/run

vlgT: 
	@make -f ./.make/runV

hlgT: 
	@make -f ./.make/runH

 libcla:
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) $(shell find $(OBJ)/*/. -type f -regex ".*\.o")  -o $(LIB)/libcla.so

 reless_lib:
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_SECOND) $(shell find $(OBJ)/*/. -type f -regex ".*\.o")  -o $(LIB)/libcla_rel.so


build_single:
	@make -f ./.make/build_single

build:
	@make shared_obj_debug
	@make libcla
	@make -f ./.make/build


test_release:
	@make -f ./.make/run_rel

shared_obj_debug:
	@make -f ./.make/shared_obj

release:

	@make -f ./.make/releass1
	@make libcla
	@make -f ./.make/releass2_build

release_so:
	@make -f ./.make/releass1

change:
	@make -f ./.make/change

clean:
	@make -f ./.make/clean
	@rm -r -f $(LIB)/libcla.so
	@rm -r -f	$(LIB)/libcla_rel.so
	@rm -r -f ./*.o
	@rm -r -f ./*.so



