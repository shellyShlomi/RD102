#*****************************************************************************#
#-------- PHONYs command and there meaning to test the foledr's files --------#
#-----------------------------------------------------------------------------#
#------------------------------- made by shelly ------------------------------#
# ****************************************************************************#


TARGET = $(notdir $(shell pwd))
TARGET_C = $(notdir $(shell pwd))_c
TARGET_CPP = $(notdir $(shell pwd))_cpp


SHAREDLIB = lib$(TARGET).so


SRC = .
LIB = ../../lib
TEST = ../../test
INC = ../../include 
BIN = ../../bin
OBJ = ../../obj
FILE = $(SRC)/file

CPP = g++
CC = gcc

CFLAGS =  -std=c99 -pedantic-errors -Wall -Wextra -g -I$(INC) 
CPPFLAGS = -std=c++98 -pedantic-errors -Wall -Wextra -g -I$(INC) 

OBJECTS = $(OBJ)/$(TARGET)/$(TARGET_C)/$(TARGET_C).o 
OBJECTS_CPP = $(OBJ)/$(TARGET)/$(TARGET_CPP)/$(TARGET)_cpp.o 

# ************************* source & test sourec files *************************
SOURCE = $(SRC)/$(TARGET).c
SOURCE_CPP = $(SRC)/$(TARGET).cpp

# ***************************** share object flags ***************************** 
SOFLAG_FIRST = -c -fpic 
SOFLAG_SECOND = -shared

LDFLAGS = -L$(LIB) -Wl,-rpath=$(LIB) -lcla -lpthread
LDFLAGS_CPP = -L$(LIB) -Wl,-rpath=$(LIB) -lcla_cpp -lpthread

#					-------shared object flags whit thread-------					

LDFLAGS_MT = -L$(LIB) -Wl,-rpath=$(LIB) -lcla -lpthread

# ********************************** debuging **********************************

VLG		= valgrind --leak-check=yes --track-origins=yes
HLG		= valgrind --tool=helgrind --history-level=approx
CGDB	= cgdb

#*******************************************************************************
#************************************ RULES ************************************
#*******************************************************************************


#----------------debug C rules------------------#

$(OBJECTS): $(SOURCE) 
	$(CC) $(CFLAGS) $(SOFLAG_FIRST) $< -o $@ 

$(BIN)/$(TARGET_C): $(SOURCE) $(OBJECTS) $(LIB)/libcla.so
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@ $(LIB)/libcla.so 

#----------------debug CPP rules------------------#


$(OBJECTS_CPP): $(SOURCE_CPP)
	$(CPP) $(CPPFLAGS) $(SOFLAG_FIRST) $< -o $@ 

$(BIN)/$(TARGET_CPP): $(SOURCE_CPP) $(OBJECTS_CPP) $(LIB)/libcla_cpp.so
	$(CPP) $(CPPFLAGS) $(LDFLAGS_CPP) $< -o $@ $(LIB)/libcla_cpp.so 

#----------------	shered librery (C & CPP)	------------------#

$(LIB)/libcla.so: $(OBJECTS)
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) $(shell find $(OBJ)/$(TARGET)/$(TARGET_C)/. -type f -regex ".*\.o")  -o $(LIB)/libcla.so


$(LIB)/libcla_cpp.so: $(OBJECTS_CPP)
	$(CPP) $(CPPFLAGS) $(SOFLAG_SECOND) $(shell find $(OBJ)/$(TARGET)/$(TARGET_CPP)/. -type f -regex ".*\.o")  -o $(LIB)/libcla_cpp.so

#----------------	PHONYs	------------------#
#	first -  comparison of c and cpp output files, secound -  C, third -  CPP,
#	fourth -  general

.PHONY :test_cmp for_test cpp_to_file c_to_file \
\
		build silent_test nw_test nmw_test test vlgT hlgT shared_obj \
		update_debug clean_d \
\
		build_cpp silent_test_cpp nw_test_cpp nmw_test_cpp test_cpp vlgT_cpp \
		hlgT_cpp shared_obj_cpp update_debug_cpp clean_d_cpp \
\
		shared_lib  clean  
#----------------Comparison Of C & CPP Outפut Files------------------#

test_cmp:
	$(shell echo diff $(FILE)/$(TARGET_CPP).txt $(FILE)/$(TARGET_C).txt)

for_test:
	@mkdir -p $(FILE)  
	@make -s cpp_to_file
	@make -s c_to_file

cpp_to_file:
	@make CPPFLAGS='-std=c++98 -g -I$(INC)'  -s build_cpp
	@./$(BIN)/$(TARGET_CPP) > $(FILE)/$(TARGET_CPP).txt

c_to_file:
	@make CFLAGS='-std=c99 -pedantic-errors -Wall -Wextra -g -I$(INC)' -s build
	@./$(BIN)/$(TARGET_C) > $(FILE)/$(TARGET_C).txt

#----------------DEBUG C------------------#

build:
	@make shared_obj
	@make $(BIN)/$(TARGET_C)

silent_test:
	@make -s CFLAGS='-std=c99 -g -I$(INC) ' build
	@./$(BIN)/$(TARGET_C)

nw_test:
	@make CFLAGS='-std=c99 -g -I$(INC) ' build
	@./$(BIN)/$(TARGET_C)

nmw_test:
	@make -s build
	@./$(BIN)/$(TARGET_C)

test:
	@make  build
	@./$(BIN)/$(TARGET_C)

vlgT:
	@make  build
	@$(VLG) ./$(BIN)/$(TARGET_C)

hlgT:
	@make  build
	@$(HLG) ./$(BIN)/$(TARGET_C)

shared_obj:
	@mkdir -p $(OBJ)/$(TARGET)/$(TARGET_C)  
	@mkdir -p $(LIB)/  
	@mkdir -p $(BIN)/  
	@make $(LIB)/libcla.so


update_debug:
	@make clean_d
	@make build


clean_d :
	@rm -f -r  $(BIN)/$(TARGET_C)
	@rm -f -r $(LIB)/$(SHAREDLIB) 
	@rm -f -r $(LIB)/libcla.so 
	@rm -f -r $(OBJ)/$(TARGET_C) 

#----------------DEBUG CPP------------------#

build_cpp:
	@make shared_obj_cpp 
	@make $(BIN)/$(TARGET_CPP)


test_cpp:
	@make  build_cpp
	@./$(BIN)/$(TARGET_CPP)

silent_test_cpp:
	@make -s CPPFLAGS='-std=c++98 -g -I$(INC)' build_cpp
	@./$(BIN)/$(TARGET_CPP)

nw_test_cpp:
	@make CPPFLAGS='-std=c++98 -g -I$(INC)' build_cpp
	@./$(BIN)/$(TARGET_CPP)

nmw_test_cpp:
	@make -s build_cpp
	@./$(BIN)/$(TARGET_CPP)

vlgT_cpp:
	@make  build_cpp
	@$(VLG) ./$(BIN)/$(TARGET_CPP)

hlgT_cpp:
	@make  build_cpp
	@$(HLG) ./$(BIN)/$(TARGET_CPP)

shared_obj_cpp:
	@mkdir -p $(OBJ)/$(TARGET)/$(TARGET_CPP)  
	@mkdir -p $(LIB)/  
	@mkdir -p $(BIN)/  
	@make $(LIB)/libcla_cpp.so


update_debug_cpp:
	@make clean_d_cpp
	@make build_cpp


clean_d_cpp:
	@rm -f -r  $(BIN)/$(TARGET_CPP)
	@rm -f -r $(LIB)/libcla_cpp.so 
	@rm -f -r $(OBJ)/$(TARGET_CPP) 



#----------------GENERAL------------------#


shared_lib:
	@make $(LIB)/libcla_rel.so
	@make $(LIB)/libcla.so
	@make $(LIB)/libcla_cpp.so


clean :
	@rm -f -r  $(BIN)
	@rm -f -r $(LIB)
	@rm -f -r $(OBJ_REL)
	@rm -f -r $(OBJ)
	@rm -f -r $(FILE)



#******************************** release flags ******************************** 
#						-------not used in this make-------					

SHAREDLIB_REL = lib$(TARGET)_rel.so

TARGET_RELEASE = $(TARGET)_rel

OBJ_REL = ../../obj_rel
OBJECTS_REL = $(OBJ_REL)/$(TARGET_RELEASE)/$(TARGET_RELEASE).o
RELEASE_FLAGS =  -std=c++98 -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_REL = -L$(LIB) -Wl,-rpath=$(LIB) -lcla_rel 
LDFLAGS_REL_MT = -L$(LIB) -Wl,-rpath=$(LIB) -lcla_rel -lpthread


#----------------RELEASE PHONYs------------------#

#	release silent_test_release nw_test_release nmw_test_release test_release  
#	hlgT_release vlgT_release release_so update_release clean_r


#----------------release rules------------------#

$(OBJECTS_REL): $(SOURCE)
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_FIRST) $< -o $@ 

$(LIB)/$(SHAREDLIB_REL):$(OBJECTS_REL)  
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_SECOND) $^ -o $@ 


$(BIN)/$(TARGET_RELEASE): $(OBJECTS_REL) $(LIB)/libcla_rel.so
	$(CC) $(RELEASE_FLAGS) $(LDFLAGS_REL) $< -o $@ $(LIB)/libcla_rel.so  

$(LIB)/libcla_rel.so: $(OBJECTS_REL)
	$(CC) $(RELEASE_FLAGS) $(SOFLAG_SECOND) \
	$(shell find $(OBJ_REL)/*/. -type f -regex ".*\.o") -o $(LIB)/libcla_rel.so


#----------------RELEASE------------------#

release: CFLAGS = $(RELEASE_FLAGS) 
release: 
	@make release_so
	@make $(BIN)/$(TARGET_RELEASE)

silent_test_release:
	@make -s RELEASE_FLAGS='-std=c++98 -DNDEBUG -O3 -I$(INC) ' release
	@./$(BIN)/$(TARGET_RELEASE)

nw_test_release:
	@make RELEASE_FLAGS='-std=c++98 -DNDEBUG -O3 -I$(INC) ' release
	@./$(BIN)/$(TARGET_RELEASE)


nmw_test_release:
	@make -s release
	@./$(BIN)/$(TARGET_RELEASE)


test_release:
	@make release
	@./$(BIN)/$(TARGET_RELEASE)

vlgT_release:
	@make release
	@$(VLG) ./$(BIN)/$(TARGET_RELEASE)

hlgT_release:
	@make release
	@$(HLG) ./$(BIN)/$(TARGET_RELEASE)


release_so:
	@mkdir -p $(OBJ_REL)/$(TARGET_RELEASE)
	@mkdir -p $(LIB)/  
	@mkdir -p $(BIN)/  
	@make $(LIB)/libcla_rel.so
	@make $(LIB)/$(SHAREDLIB_REL)



update_release:
	@make clean_r
	@make release


clean_r :
	@rm -f -r $(BIN)/$(TARGET_RELEASE)
	@rm -f -r $(LIB)/$(SHAREDLIB_REL)  
	@rm -f -r  $(LIB)/libcla_rel.so
	@rm -f -r  $(OBJ_REL)/$(TARGET_RELEASE) 


