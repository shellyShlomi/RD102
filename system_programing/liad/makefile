
CC = gcc
INCLUDE = ../../include/
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I
TARGET = fooer.out
OBJECTS = queue.o ../src/sll/sll.o 

$(TARGET) : $(OBJECTS) $(INCLUDE)sll.h $(INCLUDE)queue.h
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)   

$(OBJECTS) : ../../include/sll.h ../../include/queue.h

.PHONY : clean
clean :
	rm -f $(OBJECTS) $(TARGET) 
