TARGET 	= WD_file_for_user

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
CFLAGS	= -ansi -pedantic-errors -Wall -Wextra -g -I$(INCLUDE) -I$(SRC) -fPIC

WD_FILES	= ./iner_files

HEADERS	= $(SRC)/watch_dog.h $(WD_FILES)/watchdog_iner.h $(INCLUDE)/sorted_ll.h $(INCLUDE)/dll.h \
		  $(INCLUDE)/priority_queue.h $(INCLUDE)/uid.h $(INCLUDE)/task.h \
		  $(INCLUDE)/scheduler.h
			
SOURCES_WATCHDOG = $(UID)/uid.c $(TASK)/task.c $(PRIORITY_QUEUE)/priority_queue.c \
		    	   $(SCHEDULER)/scheduler.c $(WD_FILES)/watch_dog.c $(WD_FILES)/$(TARGET).c
		    	   
		  
SOURCES_USER = $(UID)/uid.c $(TASK)/task.c $(PRIORITY_QUEUE)/priority_queue.c \
		    	   $(SCHEDULER)/scheduler.c $(WD_FILES)/watch_dog.c $(WD_FILES)/$(TARGET).c

OBJECT_WATCHDOG	= $(OBJ)/dll.o $(OBJ)/sorted_ll.o \
		 		  $(OBJ)/priority_queue.o $(OBJ)/uid.o $(OBJ)/task.o \
				  $(OBJ)/scheduler.o $(OBJ)/$(TARGET).o $(OBJ)/watch_dog.o

$(BIN)/user_app : $(OBJ)/user_app.o libwatchdog.so $(HEADERS) 
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

$(OBJ)/%.o : $(WD_FILES)/%.c 
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@
	
$(OBJ)/%.o : $(SCHEDULER)/%.c 
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@
	


.PHONY: clean run 

run :
	./user_app shelly 

clean : 
	rm -f $(BIN)/$(TARGET)
	rm -f $(BIN)/user_app
	rm -f $(OBJ)/*.o
	rm -r $(OBJ)
	rm -f libwatchdog.so

all: $(BIN)/user_app $(BIN)/$(TARGET)

release: CFLAGS = -ansi -pedantic-errors -Wall -Wextra -I$(INCLUDE) -I$(SRC) -fPIC -DNDEBUG
release: all
