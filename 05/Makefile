CC=g++

all: main 
	valgrind --tool=memcheck --leak-check=yes   ./main
	rm -rf *.o main
main: test.o BigInt.o
	$(CC) -o main BigInt.o test.o
test: test.cpp
	$(CC) -o test.o
BigInt.o: BigInt.cpp BigInt.hpp
	$(CC) -c BigInt.cpp