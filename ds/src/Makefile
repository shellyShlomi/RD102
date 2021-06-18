

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
LDFLAGS = -L$(LIB) -Wl,-rpath=$(LIB) -lds
#----------------------------------------------------#


.PHONY: libds build_single build test shared_obj_debug release release_single
		change clean 

libds:
	
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) $(shell find $(OBJ)/*/. -type f -regex ".*\.o")  -o $(LIB)/libds.so


build_single:
	@make -f ./.make/build_single

build:
	@make libds
	@make -f ./.make/build

test:
	@make -f ./.make/run

test_release:

	@make -f ./.make/run_rel

shared_obj_debug:
	@mkdir -p $(OBJ)/tests_for_sorts
	$(CC) $(CFLAGS) ./tests_for_sorts.c -c -fpic -o $(OBJ)/tests_for_sorts/tests_for_sorts.o 
	@make -f ./.make/shared_obj

release:
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
	




#all:
#	@make so
#	$(CC) $(CFLAGS) $(RELEASE_FLAGS) $(shell find $(OBJ)_rel/*/. -maxdepth 1 -type f -regex ".*\.o")  -o $(LIB)/libds_rel.so
#	@make -f ./.make/makefile3
