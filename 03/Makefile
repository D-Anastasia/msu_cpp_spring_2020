CC=g++

all: main 
	valgrind --tool=memcheck --leak-check=yes ./main
	rm -rf *.o main
main: test.o matrix.o
	$(CC) -o main matrix.o test.o
test: test.cpp
	$(CC) -o test.o
matrix.o: matrix.cpp matrix.hpp
	$(CC) -c matrix.cpp