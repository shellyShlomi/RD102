NAME = $(notdir ${PWD})
LIB = ../../lib
TEST = ../test
OBJ = ../../obj
INC = ../../include
SRC = .
BIN = ../bin
SRCS := $(NAME)/$(wildcard $(SRC)/*.cpp)

VLG	= valgrind --leak-check=yes --track-origins=yes

export EXES_SRC := $(TEST)/$(NAME:.cpp=_test.cpp)
export EXES := $(BIN)/$(NAME:=_test)

all:	
	$(MAKE) all -C../ -e

debug:
	$(MAKE) debug -C../ -e

release:
	$(MAKE) release -C../ -e

test:
	$(MAKE) test -C../ -e

.PHONY: clean all release debug test run gdb vlg

gdb:
	@cd ../ && cgdb $(BIN)/$(NAME)_test
run:
	@cd ../ && $(BIN)/$(NAME)_test

vlg :
	@cd ../ && $(VLG) ./$(BIN)/$(NAME)_test

help:
	$(MAKE) help -C../ -e
clean:
	$(MAKE) clean -C../ -e
