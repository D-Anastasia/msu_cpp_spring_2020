CC=g++

all: main 
	valgrind --tool=memcheck --leak-check=yes ./main
	rm -rf *.o main
main: test.cpp
	$(CC) -o main test.cpp