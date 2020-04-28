#include <iostream>
#include"vector.hpp"
#include <cassert>
#include <sstream>
int main(){
	Vector<int> v;
	for (size_t i = 0; i < 5; ++i) {
		v.push_back(int(i));
	}
	for (auto p = v.begin(); p != v.end(); ++p) {
		cout << *p << " ";
	}
	cout << endl;
	v.pop_back();
	for (auto p = v.rbegin(); p != v.rend(); ++p) {
		cout << *p  << " ";
	}
	cout << endl;
	assert(!v.empty());
	assert(v.size() == 4);
	cout << endl;
	cout << "v[3]=" << v[3] << endl;
	v.clear();
	assert(v.empty());
}