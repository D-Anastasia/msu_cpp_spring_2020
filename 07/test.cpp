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


    Vector<int> v2(4, 7);
    for (int i = 0; i < v2.size(); i++)
        assert(v2[i] == 7);
    v2.push_back(23);
    assert(5 == v2.size());
    v2.pop_back();
    v2[0] = 3;
    assert(v2[0] == 3);

    
    Vector<int> v1(3);
    Iterator<int> t = v1.begin();
    for (int j = 0; j < v1.size();j++,++t)
        assert(v1[j] == *t);
}