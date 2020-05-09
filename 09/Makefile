CC=g++
all: main
	./sort 

main: sort.o  
	$(CC) -pthread sort.o -o sort

sort.o: sort.cpp
	$(CC) -c sort.cpp

clean:
	rm -rf *.o sort