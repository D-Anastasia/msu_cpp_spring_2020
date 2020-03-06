CC=g++

all: main 
	valgrind --tool=memcheck --leak-check=yes ./main
	rm -rf *.o main
main: test.o allocator.o
	$(CC) -o main allocator.o test.o
test: test.cpp
	$(CC) -o test.o
allocator.o: allocator.cpp allocator.hpp
	$(CC) -c allocator.cpp
