NAME = cpp
LIB = ../lib
TEST = ../test
OBJ = ../obj
INC = ../include
SRC = ../src
BIN = ../bin
SRCS = $(wildcard $(SRC)/*/*.cpp)

OBJS_DEBUG = $(addprefix $(OBJ)/,$(patsubst %.cpp,%_DEBUG.o,$(notdir $(SRCS))))
OBJS_RELEASE = $(addprefix $(OBJ)/,$(patsubst %.cpp,%_RELEASE.o,$(notdir $(SRCS))))
DEBUG = -g
RELEASE = -DNDEBUG -O3
EXES_SRC = $(wildcard $(TEST)/*.cpp)
EXES = $(patsubst %,$(BIN)/%,$(notdir $(EXES_SRC:.cpp=)))

CC = g++ -ansi -pedantic-errors -Wall -Wextra -I$(INC) -fPIC	
CFLAGS = -g
LDFLAGS = -Wl,-rpath=$(LIB) -L$(LIB) -l_$(NAME)_DEBUG -lpthread -l_test
LDFLAGS_RELEASE = -Wl,-rpath=$(LIB) -L$(LIB) -l_$(NAME)_RELEASE -lpthread -l_test

deps := $(patsubst %.o,%.d,$(OBJS_DEBUG)) 
DEPFLAGS = -MMD -MF $(@:.o=.d)

FILE  = $(shell find ../../../tools/. -type f -regex ".*\.c")
TEST_OBJ = $(patsubst *.c, *.o, $(notdir $(FILE:.c=.o)))
TEST_OBJs = $(patsubst %.o, $(OBJ)/%.o,  $(TEST_OBJ))

# default which creates both debug and release version
all: mkdirs debug release  	

test: mkdirs libtests $(EXES)

$(BIN)/%: $(TEST)/%.cpp $(LIB)/lib_$(NAME)_DEBUG.so $(LIB)/lib_test.so #$(OBJ)/lib_test
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) -lm 

$(OBJ)/lib_test: 
	@mkdir -p $(OBJ)/tests_lib
	for files in $(shell find ../../tools/ -type f -regex ".*\.c"); do	\
		$(CC) $(CFLAGS) -c $$files -o $(OBJ)/tests_lib/lib_test.o;	\
		$(CC) $(CFLAGS) -shared $$files -o $(LIB)/lib_test.so;	\
	done

debug: $(LIB)/lib_$(NAME)_DEBUG.so

$(LIB)/lib_$(NAME)_DEBUG.so: $(OBJS_DEBUG)
	$(CC) -shared -o $@ $(OBJS_DEBUG)

$(OBJ)/%_DEBUG.o: $(SRC)/*/%.cpp
	$(CC) -c $(DEBUG) $< -o $@ $(DEPFLAGS)	

release: CFLAGS=$(RELEASE)
release: $(LIB)/lib_$(NAME)_RELEASE.so
release: libtests

$(LIB)/lib_$(NAME)_RELEASE.so: $(OBJS_RELEASE)
	$(CC) -shared -o $@ $(OBJS_RELEASE)
	
$(OBJ)/%_RELEASE.o: $(SRC)/*/%.cpp
	$(CC) -c $(RELEASE) $< -o $@ $(DEPFLAGS)	

$(OBJ)/%.o: ../../../tools/%.c
	@mkdir -p $(OBJ)/
	$(CC) $(CFLAGS) -c -fpic $^ -o $@ 


.PHONY: clean all release debug test mkdirs libtests #$(OBJ)/lib_test

libtests: $(TEST_OBJs)

mkdirs:
	@mkdir -p $(OBJ)/
	@mkdir -p $(LIB)/
	@mkdir -p $(BIN)/

help:
	@echo $(SRCS)
	@echo $(deps)
	@echo $(EXES)
	@echo $(OBJS_DEBUG)
	@echo $(addprefix $(TEST)/, $(notdir $(EXES:=.cpp)))

clean:
	rm $(EXES) $(OBJ)/*.o $(OBJ)/*/*.o $(LIB)/*.so 

-include $(deps)