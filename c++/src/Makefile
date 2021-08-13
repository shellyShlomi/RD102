

SUBDIRS := $(wildcard */.)

LIB = ../lib

INC = ../include
BIN = ../bin

OBJ = ../obj
OBJ_REL = ../obj_rel

CC = g++
CFLAGS = -std=c++98 -pedantic-errors -Wall -Wextra -g -I$(INC) 
RELEASE_FLAGS =  -std=c++98 -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 

#----------------shared object flags------------------#

SOFLAG_SECOND = -shared 

#----------------	PHONYs	------------------#

.PHONY:	NTD test build vlgT hlgT so_debug update_debug
		NTR test_release release vlgT_release vlgh_release so_release update_release
		change clean clean_d clean_r libcla reless_lib

#----------------DEBUG------------------#


NTD: 
	@make -s -f ./.make/run_n

test: 
	@make -f ./.make/run

build:
	@make -f ./.make/build

so_debug:
	@make -f ./.make/shared_obj_debug

vlgT: 
	@make -f ./.make/runV

hlgT: 
	@make -f ./.make/runH

update_debug: 
	@make -f ./.make/update_debug

#----------------RELEASE------------------#

NTR:
	@make -s -f ./.make/run_rel_n

test_release:
	@make -f ./.make/run_rel

release:
	@make -f ./.make/releass

so_release:
	@make -f ./.make/shared_obj_release

vlgT_release: 
	@make -f ./.make/runV_rel

hlgT_release: 
	@make -f ./.make/runH_rel

update_release: 
	@make -f ./.make/update_release



#----------------GENERAL------------------#

libcla:
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) $(shell find $(OBJ)/*/. -type f -regex ".*\.o")  -o $(LIB)/libcla.so

reless_lib:
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_SECOND) $(shell find $(OBJ)/*/. -type f -regex ".*\.o")  -o $(LIB)/libcla_rel.so


change:
	@make -f ./.make/change


clean :
	@make -f ./.make/clean



clean_d :
	@rm -f -r $(OBJ)
	@make -f ./.make/clean_d


clean_r :
	@rm -f -r $(OBJ_REL)
	@make -f ./.make/clean_r