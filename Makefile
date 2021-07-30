
TARGET = $(notdir $(shell pwd))

ALL		= ../../../*
SRC		= .
INCLUDE	= $(shell find $(ALL) -name 'include')
OBJ 	= $(shell find $(ALL) -name 'obj')/$(TARGET)
BIN		= $(shell find $(ALL) -name 'bin')
LIB		= $(shell find $(ALL) -name 'lib')


ARC_NAME= libd_s.a
ARC		= $(LIB)/$(ARC_NAME)
SH_OBJ	= $(LIB)/lib$(TARGET).so
LIBRARY	= d_s

FPIC	= -fpic
SHFLAGS	= -shared

VLG		= valgrind --leak-check=yes --track-origins=yes
CGDB	= cgdb

CC 		= gcc
DEBUG 	= -ansi -pedantic-errors -Wall -Wextra -g 
CFLAGS	= $(DEBUG) -I$(INCLUDE)
RELEASE	= -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INCLUDE)
LDFLAGS	= -L$(LIB) -Wl,-rpath=$(LIB) 

HEADER		= $(shell find $(ALL) -name '*.h'| grep "$(TARGET)")
SOURCES		= $(shell find $(ALL) -name '$(TARGET).c')
TEST		= $(shell find $(ALL) -name '$(TARGET)_test.c')
OBJECTS		= $(patsubst %.c,$(OBJ)/%.o, $(notdir $(SOURCES:.c = .o))) 
DEPEN		= .depend
ALL_DEPEN	= .
SHAR_DEPN	= .
SHARED		= .



$(SH_OBJ): $(OBJECTS) $(HEADER)
	for dir in $(ALL_DEPEN); do \
        $(MAKE) -C $$dir; \
    done
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHFLAGS) -o $@ $(OBJECTS) $(SHAR_DEPN)
	

$(OBJ)/%.o : $(SOURCES)
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) $(FPIC) -c $^ 
	mv *.o $(OBJ)
	



$(BIN)/$(TARGET): $(TEST)
	 $(CC) $(CFLAGS) $(LDFLAGS) $(TEST) -o $@ -l$(TARGET) 



.PHONY: clean test run print vlgd test depend release

depend: .depend 

.depend: $(SOURCES) 
		rm -f "$@"
		$(CC) $(CFLAGS) -M $^ -MF "$@"
include .depend
DEPEN = $(shell grep -wo "../../../ds/include/[a-z/_]*" .depend)
ALL_DEPEN = $(patsubst %, ../%/, $(filter-out $(TARGET) ,$(notdir $(DEPEN))))
SHAR_DEPN = $(patsubst %, -l%, $(filter-out $(TARGET) ,$(notdir $(DEPEN)))) 
	
	

test : $(BIN)/$(TARGET)


run : 
	@./$(BIN)/$(TARGET)


release: CFLAGS = $(RELEASE)
release: rls
release: $(BIN)/$(TARGET)

rls: $(OBJECTS) $(HEADER)
	for dir in $(ALL_DEPEN); do \
        $(MAKE) release -C $$dir; \
    done
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHFLAGS) -o $(LIB)/lib$(TARGET).so $(OBJECTS) $(SHAR_DEPN)

vlg :
	@$(VLG) ./$(BIN)/$(TARGET)
	

gdb :
	@$(CGDB) ./$(BIN)/$(TARGET)


clean : 
	rm -f $(BIN)/$(TARGET)
	rm -f $(OBJ)/*.o
	rm -f $(OBJ)/*.so
	rm -r $(OBJ)
	rm -r $(LIB)/lib$(TARGET).so
	for dir in $(ALL_DEPEN); do \
        $(MAKE) clean -C $$dir; \
    done

print :
	@echo "Sources: $(SOURCES)"
	@echo "Objects: $(OBJECTS)"
	@echo "Headers: $(HEADER)"
	@echo "Sherd_objest: $(SH_OBJ)"
	@echo "Denpendencies files: $(DEPEN)"
	
	
	
	
	
