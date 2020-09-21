all: main

run: main
	./main

main: main.o findRoot.o
	gcc -o main main.o findRoot.o

main.o: findRoot.h
findRoot.o: findRoot.h

clean:
	rm -f *.o main