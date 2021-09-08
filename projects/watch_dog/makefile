TARGET 	= WD_file_for_user

SRC		= .
INCLUDE	= ../../ds/include
TEST	= .
OBJ 	= ./obj
BIN		= .

LDFLAGS = -Wl,-rpath=./ -L./ -lwatchdog -lpthread

CC 		= gcc
CFLAGS	= -ansi -pedantic-errors -Wall -Wextra -g -I$(INCLUDE) -I$(SRC) -fPIC

WD_FILES	= ./iner_files

HEADERS	= $(SRC)/watch_dog.h $(WD_FILES)/watchdog_iner.h
			
SOURCES_WATCHDOG =  $(WD_FILES)/watch_dog.c $(WD_FILES)/$(TARGET).c
		    	   
		  
SOURCES_USER = $(WD_FILES)/watch_dog.c $(WD_FILES)/$(TARGET).c

OBJECT_WATCHDOG	=  $(OBJ)/$(TARGET).o $(OBJ)/watch_dog.o

$(BIN)/user_app : $(OBJ)/user_app.o libwatchdog.so $(HEADERS) 
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)
	
$(BIN)/$(TARGET): libwatchdog.so $(HEADERS)  
	$(CC) $(CFLAGS) $(OBJECT_WATCHDOG) -o $@ $(LDFLAGS)
	

$(OBJ)/%.o : $(TEST)/%.c 
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJ)/%.o : $(WD_FILES)/%.c 
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
