

SUBDIRS := $(wildcard */.)

LIB = /home/shelly/git/ds/lib

INC = ../include

OBJ = ../obj
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I$(INC) 
RELEASE_FLAGS =  -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 

#----------------shared object flags------------------#
SOFLAG_FIRST = SS-fpic 
SOFLAG_SECOND = -shared 
LDFLAGS = -L$(LIB) -Wl,-rpath=$(LIB) -lds
#----------------------------------------------------#



.PHONY:


libds:
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) $(shell find $(OBJ)/*/. -maxdepth 1 -type f -regex ".*\.o")  -o $(LIB)/libds.so


exdb:
	@make -f ./.make/Makefile1

test:
	@make -f ./.make/Makefile2

so:
	@make -f ./.make/Makefile

releaseb:
	@make -f ./.make/makefile3
	@make -f ./.make/Makefile3
	@make -f ./.make/makefile

releaseso:
	@make -f ./.make/makefile3
	@make -f ./.make/Makefile
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_SECOND) $(shell find $(OBJ)/*/. -maxdepth 1 -type f -regex ".*\.o")  -o $(LIB)/libds.so
	@make -f ./.make/makefile


clean:
	@make -f ./.make/clean
	

cheng:
	@make -f ./.make/makefile


#all:
#	@make so
#	$(CC) $(CFLAGS) $(RELEASE_FLAGS) $(shell find $(OBJ)_rel/*/. -maxdepth 1 -type f -regex ".*\.o")  -o $(LIB)/libds_rel.so
#	@make -f ./.make/makefile3
