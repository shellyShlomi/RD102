

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
SOFLAG_FIRST = -c -fpic 
SOFLAG_SECOND = -shared 
FILE  = $(shell find ../../tools/ -type f -regex ".*\.c")
TEST_OBJ = $(patsubst *.c, *.o, $(notdir $(FILE:.c=.o)))
TEST_OBJs = $(patsubst %.o, $(OBJ)/tests_lib/%.o,  $(TEST_OBJ))

#----------------	PHONYs	------------------#
.PHONY:	silent_test nw_test nmw_test test build vlgT hlgT so_debug
		update_debug clean_d libcla 

		silent_test_release nw_test_release nmw_test_release 
		test_release release vlgT_release vlgh_release so_release 
		update_release clean_r reless_lib
		
		change clean libtests libtests_r 

#----------------DEBUG------------------#

silent_test: 
	@make -s libtests
	@make -s -f ./.make/run_silent

nw_test: libtests
	@make -f ./.make/run_NW

nmw_test: 
	@make -s libtests
	@make -s -f ./.make/run_no_make_worning

test: 
	@make libtests
	@make -f ./.make/run

build: libtests
	@make -f ./.make/build

so_debug: libtests
	@make -f ./.make/shared_obj_debug

vlgT: libtests
	@make -f ./.make/runV

hlgT: libtests
	@make -f ./.make/runH

update_debug: libtests
	@make -f ./.make/update_debug

#----------------RELEASE------------------#
	
	
silent_test_release: 
	@make -s libtests_r
	@make -s -f ./.make/run_rel_silent

nw_test_release: libtests_r
	@make -f ./.make/run_rel_NW

nmw_test_release: 
	@make -s libtests_r
	@make -s -f ./.make/run_rel_no_make_worning

test_release: libtests_r
	@make -f ./.make/run_rel

release: libtests_r
	@make -f ./.make/releass

so_release: libtests_r
	@make -f ./.make/shared_obj_release

vlgT_release: libtests_r
	@make -f ./.make/runV_rel

hlgT_release: libtests_r
	@make -f ./.make/runH_rel

update_release: libtests_r
	@make -f ./.make/update_release

#----------------GENERAL------------------#
$(OBJ)/tests_lib/%.o: ../../tools/%.c
	@mkdir -p $(OBJ)/tests_lib 
	$(CC) $(CFLAGS) $(SOFLAG_FIRST) $^ -o $@ 

libcla: 
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) $(shell find $(OBJ)/*/. -type f -regex ".*\.o")  -o $(LIB)/libcla.so

reless_lib:  
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_SECOND)  $(shell find $(OBJ_REL)/*/. -type f -regex ".*\.o")  -o $(LIB)/libcla.so


libtests: $(TEST_OBJs)

libtests_r: CFLAGS = $(RELEASE_FLAGS)
libtests_r: libtests

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