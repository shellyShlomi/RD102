
TARGET = find_num_in_array


CC = gcc
CFLAGS =  -ansi -pedantic-errors -Wall -Wextra -g 

SOURCE = ./find_num_in_array.c  


./$(TARGET): $(SOURCE) 
	$(CC) $(CFLAGS)  $(SOURCE) -o ./$(TARGET)



.PHONY :

release:
	$(CC) -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 $(SOURCE) -o ./$(TARGET)


run:
	./$(TARGET)
	
clean:
	rm -f -r ./$(TARGET)
	
