#include <cstdio>
#include <iostream>
#include <cstring>
#include "allocator.hpp"
using namespace std;
Allocator::Allocator(){
	memory = NULL;
}
void Allocator::makeAllocator(size_t maxSize){
	char* memory1 = new char[maxSize];
	memory = memory1;
	max_size = maxSize;
	allocated = 0;
}

char* Allocator::alloc(size_t size){
	if(allocated + size > max_size){
		return NULL;
	} else {
		allocated += size;
		return (char*)memory+allocated;
	}
}

void Allocator::reset(){
	allocated = 0;
}

Allocator::~Allocator(){
	if (memory != NULL){
		delete[] memory;
		memory = NULL;
	}
}