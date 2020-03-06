#ifndef P_01
#define P_01

class Allocator{
	size_t max_size;
	char* memory;
	size_t allocated;
public:
	Allocator();
	void makeAllocator(size_t maxSize);
	char* alloc(size_t size);
	void reset();
	~Allocator();
};

#endif

