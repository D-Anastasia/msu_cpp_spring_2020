#include "threadpool.hpp"
#include <cassert>



int func(int p) {
	return p;
}

int main() {
	ThreadPool a(8);

	auto b1 = a.exec(func, 5);
	assert(b1.get() == 5);

	char a2 = '9';
	auto b2 = a.exec([a2]() { return a2;});
	assert(b2.get() == '9');

	return 0;
}