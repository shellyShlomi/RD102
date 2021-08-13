

SUBDIRS := $(wildcard */.)

LIB = /home/shelly/git/ds/lib

INC = ../include
BIN = ../bin

OBJ = ../obj
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I$(INC) 
RELEASE_FLAGS =  -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 

#----------------shared object flags------------------#

SOFLAG_SECOND = -shared 
LDFLAGS = -L$(LIB) -Wl,-rpath=$(LIB) -lds -lpthread
#----------------------------------------------------#


.PHONY: libds build_single build test shared_obj_debug release release_single
		change clean 
test: 
	@make -f ./.make/run

libds:
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) $(shell find $(OBJ)/*/. -type f -regex ".*\.o")  -o $(LIB)/libds.so


build_single:
	@make -f ./.make/build_single

build:
	@make shared_obj_debug
	@make libds
	@make -f ./.make/build


test_release:

	@make -f ./.make/run_rel

shared_obj_debug:
	@mkdir -p $(OBJ)/tests_for_sorts 
#	@mkdir -p $(OBJ)/trie 
	$(CC) $(CFLAGS) ./tests_for_sorts.c -c -fpic -o $(OBJ)/tests_for_sorts/tests_for_sorts.o 
#	$(CC) $(CFLAGS) ./trie.c -c -fpic -o $(OBJ)/trie/trie.o 
	@make -f ./.make/shared_obj

release:
	@mkdir -p $(OBJ)/tests_for_sorts
#	@mkdir -p $(OBJ)/extra_avl 
	$(CC) $(RELEASE_FLAGS) ./tests_for_sorts.c -c -fpic -o $(OBJ)/tests_for_sorts/tests_for_sorts.o 
#	$(CC) $(RELEASE_FLAGS)  ./avl/extra_func.c -c -fpic -o $(OBJ)/extra_avl/extra_avl.o 
	@make -f ./.make/releass1
	@make libds
	@make -f ./.make/releass2_build

release_so:
	@make -f ./.make/releass1

change:
	@make -f ./.make/change

clean:
	@make -f ./.make/clean
	@rm -r -f $(LIB)/libds.so
	@rm -r -f $(OBJ)/tests_for_sorts
	@rm -r -f ./*.o




#all:
#	@make so
#	$(CC) $(CFLAGS) $(RELEASE_FLAGS) $(shell find $(OBJ)_rel/*/. -maxdepth 1 -type f -regex ".*\.o")  -o $(LIB)/libds_rel.so
#	@make -f ./.make/makefile3
