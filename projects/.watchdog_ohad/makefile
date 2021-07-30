TARGET 	= watchdog

SRC		= .
INCLUDE	= ../../ds/include
TEST	= .
OBJ 	= ./obj
BIN		= .
DLL     = ../../ds/src/dll
SORTED_LL = ../../ds/src/sorted_ll
PRIORITY_QUEUE = ../../ds/src/priority_queue
UID = ../../ds/src/uid
TASK = ../../ds/src/task
SCHEDULER = ../../ds/src/scheduler
LDFLAGS = -Wl,-rpath=./ -L./ -lwatchdog -lpthread

CC 		= gcc
CFLAGS	= -ansi -pedantic-errors -Wall -Wextra -g -I$(INCLUDE) -fPIC


HEADERS	= $(TARGET).h inner_watchdog.h $(INCLUDE)/sorted_ll.h $(INCLUDE)/dll.h \
		  $(INCLUDE)/priority_queue.h $(INCLUDE)/uid.h $(INCLUDE)/task.h \
		  $(INCLUDE)/scheduler.h
			
SOURCES_WATCHDOG = $(UID)/uid.c $(TASK)/task.c $(PRIORITY_QUEUE)/priority_queue.c \
		    	   $(SCHEDULER)/scheduler.c $(TARGET)_def.c $(TARGET).c
		  
SOURCES_USER = $(UID)/uid.c $(TASK)/task.c $(PRIORITY_QUEUE)/priority_queue.c \
		       $(SCHEDULER)/scheduler.c $(TARGET)_def.c $(TARGET)_test.c

OBJECT_WATCHDOG	= $(OBJ)/dll.o $(OBJ)/sorted_ll.o \
		 		  $(OBJ)/priority_queue.o $(OBJ)/uid.o $(OBJ)/task.o \
				  $(OBJ)/scheduler.o $(OBJ)/$(TARGET).o $(OBJ)/$(TARGET)_def.o

$(BIN)/$(TARGET)_test: $(OBJ)/$(TARGET)_test.o libwatchdog.so $(HEADERS) 
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)
	
$(BIN)/$(TARGET): libwatchdog.so $(HEADERS) 
	$(CC) $(CFLAGS) $(OBJECT_WATCHDOG) -o $@ $(LDFLAGS)
	
libwatchdog.so: $(OBJECT_WATCHDOG)
	$(CC) -shared -o $@ $^

$(OBJ)/%.o : $(SRC)/%.c
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJ)/%.o : $(DLL)/%.c 
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@
	
$(OBJ)/%.o : $(SORTED_LL)/%.c 
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@
	
$(OBJ)/%.o : $(PRIORITY_QUEUE)/%.c 
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@
	
$(OBJ)/%.o : $(UID)/%.c 
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@
	
$(OBJ)/%.o : $(TASK)/%.c 
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@
	
$(OBJ)/%.o : $(TEST)/%.c 
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@
	
$(OBJ)/%.o : $(SCHEDULER)/%.c 
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@
	


.PHONY: clean run 

run :
	$(BIN)/$(TARGET)_test ohad

clean : 
	rm -f $(BIN)/$(TARGET)
	rm -f $(BIN)/$(TARGET)_test
	rm -f $(OBJ)/*.o
	rm -r $(OBJ)
	rm -f libwatchdog.so

all: $(BIN)/$(TARGET)_test $(BIN)/$(TARGET)

release: CFLAGS = -ansi -pedantic-errors -Wall -Wextra -I$(INCLUDE) -fPIC -DNDEBUG
release: all
