CC=g++

all: main 
	valgrind --tool=memcheck --leak-check=yes ./main
	rm -rf *.o main
main: test.o parser.o
	$(CC) -o main parser.o test.o
test: test.cpp
	$(CC) -o test.o
parser.o: parser.cpp parser.hpp
	$(CC) -c parser.cpp