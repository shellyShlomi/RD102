CFLAGS = -g
CC=gcc

all: static_main.out static_rdynamic_main.out dynamic_main.out
	echo done

f1.o: f1.c
	$(CC) $(CFLAGS) -c -fPIC f1.c -o f1.o

libf1.so: f1.c
	$(CC) $(CFLAGS) f1.o -shared -o libf1.so

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o



static_main.out: main.o f1.o
	$(CC) $(CFLAGS) main.o f1.o -ldl -o static_main.out
	
static_rdynamic_main.out: main.o f1.o
	$(CC) $(CFLAGS) main.o f1.o -ldl -o static_rdynamic_main.out -rdynamic

dynamic_main.out: main.o libf1.so
	$(CC) $(CFLAGS) -L. main.o -Wl,-rpath=. -lf1 -ldl -o dynamic_main.out



clean:
	rm *.o *.out *.so