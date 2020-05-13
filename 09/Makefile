CC=g++
all: main
	valgrind --tool=memcheck --leak-check=yes ./sort
main: sort.o  
	$(CC) -pthread sort.o -o sort

sort.o: sort.cpp
	$(CC) -c sort.cpp

clean:
	rm -rf *.o sort